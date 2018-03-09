#include <iostream>
#include <fstream>
#include <string>
#include <png++/png.hpp>
#include <glm/vec3.hpp>

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

    png::image<png::rgb_pixel> image(200, 100);

    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            glm::vec3 color(float(i) / float(nx), float(ny - j) / float(ny), 0.2);

            int ir = int(255.99*color[0]);
            int ig = int(255.99*color[1]);
            int ib = int(255.99*color[2]);

            file << ir << " " << ig << " " << ib << endl;
            image[j][i] = png::rgb_pixel(ir, ig, ib);
        }
    }
    file.close();
    image.write("gradient.png");


    return 0;
}
