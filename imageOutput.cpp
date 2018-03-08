#include <iostream>
#include <fstream>
#include <string>
#include <png++/png.hpp>

using namespace std;
/*void writePPM(ofstream file) {*/

//}

//void writePNG(string fileName) {

//}

int main() {
    
    ofstream file;
    file.open("gradient.ppm", ios::out);

    int nx = 200;
    int ny = 100;
    file << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            float r = float(i) / float(nx);
            float g = float(ny - j) / float(ny);
            float b = 0.2;


            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);

            file << ir << " " << ig << " " << ib << endl;
        }
    }
    file.close();



    png::image<png::rgb_pixel> image(200, 100);

    for (png::uint_32 y = 0; y < image.get_height(); ++y) {
        for(png::uint_32 x = 0; x < image.get_width(); ++x) {
            float r = float(x) / float(image.get_width());
            float g = float(image.get_height() - y) / float(image.get_height());
            float b = 0.2;

            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);

            image[y][x] = png::rgb_pixel(ir, ig, ib);

        }
    }
    image.write("gradient.png");


    return 0;
}
