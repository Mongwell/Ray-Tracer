#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ray.hpp"
#include "stb_image_write.h"
#include "vec3.hpp"
#include <iostream>
#include <string>

using namespace std;

// Rendering [=========>         ] 50%
// progress should be a number between 0 and 1
void print_progress_meter(const float progress) {
    const int full_length = 40;

    int progress_length = progress * full_length;
    string meter;
    for (int i = 0; i < full_length; ++i) {
        if (i < progress_length) {
            meter += '=';
        } else if (i == progress_length) {
            meter += '>';
        } else {
            meter += ' ';
        }
    }
    meter = "Rendering [" + meter + "] ";
    cerr << '\r' << meter << static_cast<int>(progress * 100) << '%' << flush;
}

color ray_color(const ray &r) {
    const color bg_color1(0.5, 0.7, 1.0);
    const color bg_color2(1, 1, 1);
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * bg_color2 + t * bg_color1;
}

int main() {
    // Image settings
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera settings
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;
    point3 origin(0, 0, 0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    vec3 depth(0, 0, focal_length);
    point3 upper_left_corner = origin - horizontal / 2 + vertical / 2 - depth;

    pixelColor img_data[image_height][image_width];

    for (int i = 0; i < image_height; ++i) {
        print_progress_meter((i + 1) / static_cast<float>(image_height));
        for (int j = 0; j < image_width; ++j) {
            double u = double(j) / (image_width - 1);
            double v = double(i) / (image_height - 1);
            point3 target = upper_left_corner + u * horizontal - v * vertical;
            ray r(origin, target - origin);

            color pixel = ray_color(r);
            img_data[i][j] = pixel.to_pixel_color();
        }
    }
    cerr << "\nRendering complete!\n";

    stbi_write_jpg("./main.jpg", image_width, image_height, 3, img_data, 100);
    return 0;
}
