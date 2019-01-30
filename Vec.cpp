//
// Created by Carlos on 27/09/2018.
//

#include "Vec.h"

Vec::Vec(float x, float y, float z, enum type type) {
    this->x = x;
    this->y = y;
    this->z = z;
    if(type == POINT){
        this->type = 1;
    } else {
        this->type = 0;
    }
}

Vec::Vec(float x, float y, float z, float type) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = type;
}


ostream& operator<<(ostream& os, const Vec& vec){
    os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.type << ')';
    return os;
}

float Vec::getX() const {
    return x;
}

void Vec::setX(float x) {
    Vec::x = x;
}

float Vec::getY() const {
    return y;
}

void Vec::setY(float y) {
    Vec::y = y;
}

float Vec::getZ() const {
    return z;
}

void Vec::setZ(float z) {
    Vec::z = z;
}

float Vec::getType() const {
    return type;
}

void Vec::setType(float type){
    Vec::type = type;
}

bool Vec::operator==(const Vec &rhs) const {
    float error = abs(x - rhs.x) + abs(y - rhs.y) + abs(z - rhs.z);
    if(error < 0.00001){ // Sino hay errores de decimales
        return true;
    }
    else{
        return false;
    }
}

bool Vec::operator!=(const Vec &rhs) const {
    return !(rhs == *this);
}
