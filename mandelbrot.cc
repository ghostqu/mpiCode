#include <cmath>
#include <iostream>
//#include <jpeglib.h>
#include <stdexcept>
#include <fstream>
#include <vector>
using namespace std;
//int mandelbrot(double, double, int);
const int MAX = 127;
const int IMAGE_WIDTH = 1000;
const int IMAGE_HEIGHT = 800;
const double xMin = -2.5;
const double xMax = 1.5;
const double yMin = -2.0;
const double yMax = 2.0;
const double pWidth = (xMax - xMin) / IMAGE_WIDTH;
const double pHeight = (yMax - yMin) / IMAGE_HEIGHT;


int mandelbrot(double startReal, double startImag) {
    double zReal = startReal;
    double zImag = startImag;

    for (int counter = 0; counter < MAX; ++counter) {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;
        if (r2 + i2 > 4.0) {
            return counter;
        }
        zImag = 2.0 * zReal * zImag + startImag;
        zReal = r2 - i2 + startReal;
    }
    return MAX;
}

vector<int> getColor(int iterations) {
    int r, g, b;

    if (iterations == -1) {
        r = 0;
        g = 0;
        b = 0;
    } else if (iterations == 0) {
        b = 255;
        g = 0;
        r = 0;
    } else {
        // colour gradient:      Red -> Blue -> Green -> Red -> Black
        // corresponding values:  0  ->  16  ->  32   -> 64  ->  127 (or -1)
        if (iterations < 16) {
            b = 16 * (16 - iterations);
            g = 0;
            r = 16 * iterations - 1;
        } else if (iterations < 32) {
            b = 0;
            r = 16 * (iterations - 16);
            g = 16 * (32 - iterations) - 1;
        } else if (iterations < 64) {
            b = 8 * (iterations - 32);
            r = 8 * (64 - iterations) - 1;
            g = 0;
        } else { // range is 64 - 127
            b = 255 - (iterations - 64) * 4;
            g = 0;
            r = 0;
        }
    }
    vector<int> v;
    v.push_back(r);
    v.push_back(g);
    v.push_back(b);
    return v;
}
int main() {
  ofstream of("mandelbrot.ppm");
  of << "P3 " << IMAGE_WIDTH << " " << IMAGE_HEIGHT << " " << 255 << " ";
  for (int y = 0; y < IMAGE_HEIGHT; y++) {
    for (int x = 0; x < IMAGE_WIDTH; x++) {
      // convert x and y to the appropriate complex number
      double real = (x - IMAGE_WIDTH / 2.0) *  pWidth   ;
      double imag = (y - IMAGE_HEIGHT / 2.0) * pHeight  ;
      int value = mandelbrot(real, imag);
      vector<int> v = getColor(value);
      //of <<  v[0]  << " " << v[1] << " " << v[2] << " ";
      //of << value << " ";
    }
  }
  
  return 0;
}

