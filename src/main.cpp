#define STB_IMAGE_WRITE_IMPLEMENTATION
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

int main() {
    const int image_width = 1920;
    const int image_height = 1080;
    pixelColor img_data[image_height][image_width];

    for (int i = 0; i < image_height; ++i) {
        print_progress_meter((i + 1) / static_cast<float>(image_height));
        for (int j = 0; j < image_width; ++j) {
            color pixel(double(j) / (image_width - 1),
                        double(image_height - 1 - i) / (image_height - 1),
                        0.25);
            img_data[i][j] = pixel.to_pixel_color();
        }
    }
    cerr << "\nRendering complete!\n";

    stbi_write_jpg("./main.jpg", image_width, image_height, 3, img_data, 100);
    return 0;
}
