#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ray.hpp"
#include "stb_image_write.h"
#include "vec3.hpp"
#include <iostream>
#include <string>

// Rendering [=========>         ] 50%
// progress should be a number between 0 and 1
void print_progress_meter(const float progress) {
    const int full_length = 40;

    int progress_length = progress * full_length;
    std::string meter;
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
    std::cerr << '\r' << meter
                    << static_cast<int>(progress * 100) << '%'
                    << std::flush;
}

bool hit_sphere(const point3 &center, double radius, const ray &r) {
    // check if ray hits sphere using quadratic formula discriminant
    vec3 c2o = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(c2o, r.direction());
    double c = dot(c2o, c2o) - radius * radius;
    double discriminant = b*b - 4*a*c;

    return discriminant > 0;
}

color ray_color(const ray &r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(1, 0, 0);
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
            double u = static_cast<double>(j) / (image_width - 1);
            double v = static_cast<double>(i) / (image_height - 1);
            point3 target = upper_left_corner + u * horizontal - v * vertical;
            ray r(origin, target - origin);

            color pixel = ray_color(r);
            img_data[i][j] = pixel.to_pixel_color();
        }
    }
    std::cerr << "\nRendering complete!\n";

    stbi_write_jpg("./main.jpg", image_width, image_height, 3, img_data, 100);
    return 0;
}
