//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_VEC_H
#define COMPUTER_GRAPHICS_VEC_H

#include <iostream>
#include <cmath>
using namespace std;

enum type { POINT, DIRECTION };

// Vec es la clase vector, incluye la coordenada de más type,
// si es 1 es un punto y si es 0 es una dirección
class Vec
{
public:
    Vec(){}
    Vec(float x, float y, float z, type type);
    Vec(float x, float y, float z, float type);

    void setType(float type);
    //void accelerate(float intensity);
    //void brake(float intensity);

    friend ostream& operator<<(ostream& os, const Vec& vec);

    Vec operator+ (const Vec & second) const {
        if(type != second.getType()){
            std::cout<< "Expected same types vector add";
            std::exit(1);
        }
        return Vec(x+second.getX(), y+second.getY(), z+second.getZ(), type);
    }

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    float getType() const;

    static type getType(type type){
        if(type == 0){
            return DIRECTION;
        }
        else {
            return POINT;
        }
    }

    Vec operator- (const Vec & second) const {
        if(type != second.getType()){
            std::cout<< "Expected same types sub vector";
            std::exit(1);
        }
        float newType = type;
        if(type == getType(POINT) && second.getType() == getType(POINT)){
            newType = 0; // Now is a DIRECTION
        }
        return Vec(x-second.getX(), y-second.getY(), z-second.getZ(), newType);
    }

    // scalar * vec
    Vec operator* (const float& first) const {
        return Vec(x*first, y*first, z*first, type);
    }
    friend Vec operator* (const float& first, const Vec& second){
        return Vec(second.x*first, second.y*first, second.z*first, second.type);
    }

    float operator* (const Vec& first) const {
        return x*first.getX()+y*first.getY()+z*first.getZ();
    }
    /*
    friend float operator* (const Vec& first, const Vec& second){
        return first.getX()*second.getX()+first.getY()*second.getY()+first.getZ()*second.getZ();
    }
*/
    // https://www.varsitytutors.com/precalculus-help/find-the-unit-vector-in-the-same-direction-as-a-given-vector
    void getUnitVector(){
        float mod = this->modulus();
        x = x / mod;
        y = y / mod;
        z = z / mod;
    }

    bool operator==(const Vec &rhs) const;

    bool operator!=(const Vec &rhs) const;

    void changeSign(){
        x = -x;
        y = -y;
        z = -z;
    }

    float modulus(){
        // Only modulus of a direction
        if(type == getType(POINT)){
            std::cout<< "Expected a DIRECTION to do the modulus";
            std::exit(1);
        }
        return sqrt(x*x + y*y + z*z);
    }

    static Vec crossProduct(Vec d, Vec e){
        if(d.getType() != getType(DIRECTION) && e.getType() != getType(DIRECTION)){
            std::cout<< "Expected both direction in cross product";
            std::exit(1);
        }
        float auxX = d.getY()*e.getZ() - d.getZ()*e.getY();
        float auxY = d.getZ()*e.getX() - d.getX()*e.getZ();
        float auxZ = d.getX()*e.getY() - d.getY()*e.getX();
        return Vec(auxX, auxY, auxZ, d.getType());
    }

private:
    float x, y, z, type;
};


#endif //COMPUTER_GRAPHICS_VEC_H
