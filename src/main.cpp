#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
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
    int image_width = 1920;
    int image_height = 1080;
    pixel img_data[image_height][image_width];

    for (int i = 0; i < image_height; ++i) {
        print_progress_meter((i + 1) / static_cast<float>(image_height));
        for (int j = 0; j < image_width; ++j) {
            double r = double(j) / (image_width - 1);
            double g = double(image_height - 1 - i) / (image_height - 1);
            double b = 0.25;

            char r_char = static_cast<int>(255.999 * r);
            char g_char = static_cast<int>(255.999 * g);
            char b_char = static_cast<int>(255.999 * b);

            img_data[i][j].r = r_char;
            img_data[i][j].g = g_char;
            img_data[i][j].b = b_char;
        }
    }
    cerr << "\nRendering complete!\n";

    stbi_write_jpg("./main.jpg", image_width, image_height, 3, img_data, 100);
    return 0;
}
