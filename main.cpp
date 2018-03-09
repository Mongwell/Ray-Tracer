#include <fstream>
#include <string>
#include <png++/png.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "Ray.h"

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

bool hit_sphere(const vec3& center, float radius, const Ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;

    float discriminant = b * b - 4 * a * c;
    
    return discriminant > 0;
}

vec3 color(const Ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);

    vec3 unit_direction = normalize(r.direction());
    float t = 0.5 * (unit_direction[1] + 1.0);
    
    float scalar = 1.0 - t;

    //white blue blend
    return scalar * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    
    ofstream file;
    string name = "sphere";
    file.open(name + ".ppm", ios::out);
    image<rgb_pixel> image(200, 100);

    int nx = 200;
    int ny = 100;
    file << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);


    for (int j = ny - 1; j >= 0; --j) {
        for (int i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            vec3 direction = lower_left_corner + u*horizontal + v*vertical;
            Ray r(origin, direction);
            vec3 col = color(r);

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
