#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <png++/png.hpp>
#include <glm/glm.hpp>
#include <cfloat>
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"

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

vec3 color(const Ray& r, const Scene& world) {
    hit_record rec;
    if (world.hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5f * vec3(rec.normal[0] + 1, rec.normal[1] + 1, rec.normal[2] + 1);
    }

    vec3 unit_direction = normalize(r.direction());
    float t = 0.5 * (unit_direction[1] + 1.0);

    float scalar = 1.0 - t;
    //white blue blend
    return scalar * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    
    int nx = 1000;
    int ny = 500;
    int ns = 100;

    ofstream file;
    string name = "sphere";
    file.open(name + ".ppm", ios::out);
    image<rgb_pixel> image(nx, ny);

    file << "P3\n" << nx << " " << ny << "\n255\n";

    Camera cam;
    Scene world;
    world.scene.push_back(new Sphere(vec3(0, 0, -1), 0.5));
    world.scene.push_back(new Sphere(vec3(0, -100.5, -1), 100));

    unsigned count = 0;
    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i, ++count) {
            std::cout.precision(4);
            std::cout << "\r" << 100 * float(count) / float(nx*ny) << "%\t" << "complete...   " << std::flush; 

            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + unitRand()) / float(nx);
                float v = float(j + unitRand()) / float(ny);
                Ray r = cam.get_ray(u, v);
                //vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            
            col/= float(ns);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            file << ir << " " << ig << " " << ib << std::endl;
            image[ny - 1 - j][i] = rgb_pixel(ir, ig, ib);
        }
    }
    file.close();
    image.write(name + ".png");


    return 0;
}
