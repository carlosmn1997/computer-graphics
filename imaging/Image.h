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
#include <cmath>

using namespace std;

class Image{
public:
    // We suppose that the file is correct
    Image(string fileName){
        ifstream file;
        file.open("../img/"+fileName);

        string word;

        // Reading P3
        file >> word;

        // Reading #MAX = ...
        file >> word; // We need parsing
        m = 65535;

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
        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                int R, G, B;
                file >> R >> G >> B;
                float vR = (float)R * coefficient;
                float vG = (float)G * coefficient;
                float vB = (float)B * coefficient;
                setPixel(i, j, RGB(vR, vG, vB));
                //image[(i*y)+j] = RGB(vR, vG, vB);
            }
        }

        file.close();
    }

    RGB getPixel(int i, int j){
        //cout<<x*this->y + y<<endl;
        return image[i*this->x + j];
    }

    void setPixel(int i, int j, RGB newPixel){
        image[i*this->x + j] = newPixel;
    }

    void writeImage(){
        ofstream file;
        file.open("salida.ppm");
        file << "P3" << endl;
        file << x << " " << y << endl;
        file << "65535" << endl;

        //float coefficient = (c / 65535);
        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                int R, G, B;
                int mucho = 10000000;
                R = pixel.getR(); //* coefficient;
                G = pixel.getG();// * coefficient;
                B = pixel.getB();// * coefficient;
                file << R << " " << G << " " << B << "     ";
            }
            file << '\n';
        }

        file.close();
    }

    void equalization(){
        float maxY, X,Y,Z,r,g,b;
        maxY = 0;

        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                r = pixel.getR();
                g = pixel.getG();
                b = pixel.getB();
                maxY = max(maxY, RGB_Y(r,g,b));
            }
        }

        float coefficient = (m / maxY);

        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                r = pixel.getR();
                g = pixel.getG();
                b = pixel.getB();
                X = RGB_X(r,g,b);
                Y = RGB_Y(r,g,b) * coefficient;
                Z = RGB_Z(r,g,b);
                pixel.setR(XYZ_R(X,Y,Z));
                pixel.setG(XYZ_G(X,Y,Z));
                pixel.setB(XYZ_B(X,Y,Z));
                //image[(i*y)+j] = pixel;
                setPixel(i, j, pixel);
            }
        }
    }

    //https://stackoverflow.com/questions/16521003/gamma-correction-formula-gamma-or-1-gamma
    // https://docs.opencv.org/3.4/d3/dc1/tutorial_basic_linear_transform.html al final
    void gammaCurve(){
        float factor = 2.2;
        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                float kk = pow(pixel.getR()/m, 1.0/factor);
                pixel.setR(m*pow(pixel.getR()/m, 1.0/factor));
                pixel.setG(m*pow(pixel.getG()/m, 1.0/factor));
                pixel.setB(m*pow(pixel.getB()/m, 1.0/factor));
                setPixel(i, j, pixel);
            }
        }
    }

    void clamping(){
        float X,Y,Z;
        float r,g,b;
        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                r = pixel.getR(); g = pixel.getG(); b = pixel.getB();
                X = RGB_X(r,g,b);
                Y = min(RGB_Y(r,g,b),m);
                Z = RGB_Z(r,g,b);
                r = XYZ_R(X,Y,Z); g = XYZ_G(X,Y,Z); b = XYZ_B(X,Y,Z);
                pixel.setR(r);
                pixel.setG(g);
                pixel.setB(b);
                setPixel(i, j, pixel);
            }
        }
    }

    void equalizeAndClamp(){
        float minR, minG, minB, maxR, maxG, maxB;
        minR = m;
        minG = m;
        minB = m;
        maxR = 0;
        maxG = 0;
        maxB = 0;

        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                minR = min(minR, pixel.getR());
                minG = min(minG, pixel.getG());
                minB = min(minB, pixel.getB());
                maxR = max(maxR, pixel.getR());
                maxG = max(maxG, pixel.getG());
                maxB = max(maxB, pixel.getB());
            }
        }

        maxR = maxR * 0.9;
        maxG = maxG * 0.9;
        maxB = maxB * 0.9;

        float coefficientR = (m / maxR);
        float coefficientG = (m / maxG);
        float coefficientB = (m / maxB);

        for (int i = 0; i < y; i++){
            for (int j = 0; j < x; j++){
                RGB pixel = getPixel(i, j);
                pixel.setR(min(pixel.getR() * coefficientR,m));
                pixel.setG(min(pixel.getG() * coefficientG,m));
                pixel.setB(min(pixel.getB() * coefficientB,m));
                //image[(i*y)+j] = pixel;
                setPixel(i, j, pixel);
            }
        }
    }

    float RGB_X(float r, float g, float b){
        //return 0.4887180 * r + 0.1762044 * g;
        return 0.4887180*r + 0.3106803*g + 0.2006017*b;
    }

    float RGB_Y(float r, float g, float b){
        //return 0.3106803 * r + 0.8129847 * g + 0.0102048 * b;
        return 0.1762044*r + 0.8129847*g + 0.0108109*b;
    }

    float RGB_Z(float r, float g, float b){
        //return 0.2006017 * r + 0.0108109 * g + 0.9897952 * b;
        return  0.0102048*g  + 0.9897952*b;
    }

    float XYZ_R(float x, float y, float z){
        //return 2.3706743 * x - 0.5138850 * y + 0.0052982 * z;
        return 2.3706743 * x - 0.9000405*y - 0.4706338*z;
    }

    float XYZ_G(float x, float y, float z){
        //return -0.9000405 * x + 1.4253036 * y - 0.0146949 * z;
        return -0.5138850*x + 1.4253036*y + 0.0885814*z;
    }

    float XYZ_B(float x, float y, float z){
        //return -0.4706338 * x + 0.0885814 * y + 1.0093968 * z;
        return 0.0052982*x - 0.0146949*y  + 1.0093968 *z;
    }


private:
    //vector<vector<float>> image;

    // x = anchura
    // y = altura
    // c = colorResolution
    // m = maximumResolution
    int x, y, c;
    float m;

    RGB * image;

    float parserMAX(string s){
        const char * c = s.c_str();
        s="";
        for(int i=5;i<s.length();i++){
            s+=c[i];
        }
        return stod(s);
    }

    static float min(float a, float b){
        if(a < b){
            return a;
        }
        else{
            return b;
        }
    }

    static float max(float a, float b){
        if(a > b){
            return a;
        }
        else{
            return b;
        }
    }
    // https://rosettacode.org/wiki/Gamma_function
    // Existen diferentes implementaciones de la funcion gamma
    //static float gammaFunction(float x){
    //    return sqrt(2*M_PI/x)*pow(x/)
    //}
};

#endif //COMPUTER_GRAPHICS_IMAGE_H
