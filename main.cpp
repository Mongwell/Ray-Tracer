#include <fstream>
#include <string>
#include <random>
#include <png++/png.hpp>
#include <glm/glm.hpp>
#include <cfloat>
#include "Sphere.h"
#include "Triangle.h"
#include "Quadrilateral.h"
#include "Scene.h"
#include "PrspcCamera.h"
#include "OrthgCamera.h"
#include "ProgressMeter.h"

using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::ofstream;
using std::string;
using std::ios;
using namespace glm;
using png::image;
using png::rgb_pixel;

/*void writePPM(vec3** colors, unsigned width, unsigned height, ofstream file) {*/
    //file << "P3\n" << width << " " << height << "\n255\n";

//}

//void writePNG(vec3** colors, unsigned width, unsigned height, image<rgb_pixel> file) {

//}

float unitRand() {
    random_device random;
    mt19937 gen(random());
    uniform_real_distribution<float> distribution;

    return distribution(random);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0f*vec3(unitRand(), unitRand(), unitRand()) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

vec3 color(const Ray& r, const Scene& world, unsigned depth = 0) {
    hit_record rec;
    if (world.hit(r, 0.001, FLT_MAX, rec) && depth < 25) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        vec3 direction = target - rec.p;
        return 0.5f * color(Ray(rec.p, direction), world, depth+1);
    }

    vec3 unit_direction = normalize(r.direction());
    float t = 0.5 * (unit_direction[1] + 1.0);

    float scalar = 1.0 - t;
    //white blue blend
    return scalar * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    
    int nx = 900;
    int ny = 600;
    int ns = 256;

    string name = "";
    image<rgb_pixel> prspcImage(nx, ny);
    image<rgb_pixel> orthgImage(nx, ny);
    


    PrspcCamera pCam;
    OrthgCamera oCam;

    Scene world;
    world.scene.push_back(new Sphere(vec3(0, 0, -1), 0.4));
    world.scene.push_back(new Sphere(vec3(0, -100.5, -2), 100));
    world.scene.push_back(new Triangle(vec3(-1, 0, -1), vec3(-2, 0, -1), vec3(-1, 0.5, -1)));
    world.scene.push_back(new Quadrilateral(vec3(0, 0, -1), vec3(-1, 0, -1), vec3(1, 0.2, -1), vec3(1, 0.3, -1)));

    unsigned count = 0;
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i, ++count) {
            printProgress(float(count) / (nx * ny));

            vec3 pCol(0, 0, 0);
            vec3 oCol(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + unitRand()) / float(nx);
                float v = float(j + unitRand()) / float(ny);
                Ray pRay = pCam.get_ray(u, v);
                pCol += color(pRay, world);

                Ray oRay = oCam.get_ray(u, v);
                oCol += color(oRay, world);
                //vec3 p = r.point_at_parameter(2.0);
            }
            
            pCol/= float(ns);
            pCol = sqrt(pCol);
            int pir = int(255.99*pCol[0]);
            int pig = int(255.99*pCol[1]);
            int pib = int(255.99*pCol[2]);

            oCol/= float(ns);
            oCol = sqrt(oCol);
            int oir = int(255.99*oCol[0]);
            int oig = int(255.99*oCol[1]);
            int oib = int(255.99*oCol[2]);
            prspcImage[ny - 1 - j][i] = rgb_pixel(pir, pig, pib);
            orthgImage[ny - 1 - j][i] = rgb_pixel(oir, oig, oib);
        }
    }
    printProgress(1);

    prspcImage.write(name + "perspective.png");
    orthgImage.write(name + "orthographic.png");


    return 0;
}
