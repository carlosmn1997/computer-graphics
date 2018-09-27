//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_VEC_H
#define COMPUTER_GRAPHICS_VEC_H

#include <iostream>
using namespace std;

enum type { POINT, DIRECTION };

// Vec es la clase vector, incluye la coordenada de más type,
// si es 1 es un punto y si es 0 es una dirección
class Vec
{
public:
    Vec(){}
    Vec(float i, float j, float k, type type);
    Vec(float i, float j, float k, float type);

    float getI() const;

    void setI(float i);

    float getJ() const;

    void setJ(float j);

    float getK() const;

    void setK(float k);

    float getType() const;

    void setType(float type);
    //void accelerate(float intensity);
    //void brake(float intensity);

    friend ostream& operator<<(ostream& os, const Vec& vec);

    Vec operator+ (const Vec & first) const {
        if(type != first.getType()){
            std::cout<< "Expected same types";
            std::exit(1);
        }
        return Vec(i+first.getI(), j+first.getJ(), k+first.getK(), POINT);
    }
/*
    Vec operator* (const Vec & first) const {
        return Vec(i+first.getI(), j+first.getJ(), k+first.getK(), POINT);
    }
    */
    // scalar * vec
    Vec operator* (const float& first) const {
        return Vec(i*first, j*first, k*first, type);
    }
    friend Vec operator* (const float& first, const Vec& second){
        return Vec(second.i*first, second.j*first, second.k*first, second.type);
    }
private:
    float i, j, k, type;
};


#endif //COMPUTER_GRAPHICS_VEC_H
