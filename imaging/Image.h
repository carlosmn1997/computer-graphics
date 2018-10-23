//
// Created by Carlos on 22/10/2018.
//

#ifndef COMPUTER_GRAPHICS_IMAGE_H
#define COMPUTER_GRAPHICS_IMAGE_H

// #define MAX 1000

#include "RGB.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Image{
public:
    // We suppose that the file is correct
    Image(string fileName){
        ifstream file;
        file.open("../img/mpi_atrium_1.ppm");

        string word;

        // Reading P3
        file >> word;

        // Reading #MAX = ...
        file >> word; // We need parsing
        float m = 65535;

        // Reading filename
        string line;
        file >> word >> word;
        //getline(file, line);

        // Reading x y
        file >> x;
        file >> y;
        image = new RGB[x*y];

        // Reading c, colorResolution
        file >> c;

        // Reading RGB
        float coefficient = m / c;
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                int R, G, B;
                file >> R >> G >> B;
                float vR = (float)R * coefficient;
                float vG = (float)G * coefficient;
                float vB = (float)B * coefficient;
                image[(i*y)+j] = RGB(vR, vG, vB);
            }
        }

        file.close();
    }

    RGB getPixel(int x, int y){
        return image[x*this->y + y];
    }

    void writeImage(){
        ofstream file;
        file.open("salida.ppm");
        file << "P3" << endl;
        file << x << " " << y << endl;
        file << "65535" << endl;

        float coefficient = (c / 65535);
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                RGB pixel = getPixel(i, j);
                int R, G, B;
                int mucho = 10000000;
                R = pixel.getR()* coefficient;
                G = pixel.getG() * coefficient;
                B = pixel.getB() * coefficient;
                file << R << " " << G << " " << B << '\t';
            }
            file << '\n';
        }

        file.close();
    }
/*
    void setPixel(int x, int y, RGB p){
        image[x][y] = p;
    }
 */
private:
    //vector<vector<float>> image;

    // x = anchura
    // y = altura
    // c = colorResolution
    // m = maximumResolution
    int x, y, c, m;

    RGB * image;
};

#endif //COMPUTER_GRAPHICS_IMAGE_H
