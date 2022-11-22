#include <iostream>

using namespace std;

int main() {
    const int image_width = 256;
    const int image_height = 256;

    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) {
        for (int j = 0; j < image_width; ++j) {
            double r = double(j) / (image_width - 1);
            double g = double(i) / (image_height - 1);
            double b = 0.25;

            int r_int = static_cast<int>(255.999 * r);
            int g_int = static_cast<int>(255.999 * g);
            int b_int = static_cast<int>(255.999 * b);

            cout << r_int << ' ' << g_int << ' ' << b_int << endl;
        }
    }
}
