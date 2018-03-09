#include <fstream>
#include <string>
#include <png++/png.hpp>
#include <glm/glm.hpp>
#include "Sphere.h"
#include "Scene.h"
#include <cfloat>
#include <iostream>
using std::cout;
using std::endl;

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
//

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
    
    int nx = 200;
    int ny = 100;

    ofstream file;
    string name = "sphere";
    file.open(name + ".ppm", ios::out);
    image<rgb_pixel> image(nx, ny);

    file << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    Scene world;
    world.scene.push_back(new Sphere(vec3(0, 0, -1), 0.5));
    world.scene.push_back(new Sphere(vec3(0, -100.5, -1), 100));

    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            vec3 direction = lower_left_corner + u*horizontal + v*vertical;
            Ray r(origin, direction);

            //vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);

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
