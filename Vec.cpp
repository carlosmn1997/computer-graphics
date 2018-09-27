//
// Created by Carlos on 27/09/2018.
//

#include "Vec.h"

Vec::Vec(float i, float j, float k, enum type type) {
    this->i = i;
    this->j = j;
    this->k = k;
    if(type == POINT){
        this->type = 1;
    } else {
        this->type = 0;
    }
}

Vec::Vec(float i, float j, float k, float type) {
    this->i = i;
    this->j = j;
    this->k = k;
    this->type = type;
}


ostream& operator<<(ostream& os, const Vec& vec){
    os << '(' << vec.i << ", " << vec.j << ", " << vec.k << ", " << vec.type << ')';
    return os;
}

float Vec::getI() const {
    return i;
}

void Vec::setI(float i) {
    Vec::i = i;
}

float Vec::getJ() const {
    return j;
}

void Vec::setJ(float j) {
    Vec::j = j;
}

float Vec::getK() const {
    return k;
}

void Vec::setK(float k) {
    Vec::k = k;
}

float Vec::getType() const {
    return type;
}

void Vec::setType(float type) {
    Vec::type = type;
}

/*
void Car::accelerate(float intensity) {
    speed = speed + ACCELERATION_FACTOR * intensity;
}

void Car::brake(float intensity) {
    speed = speed - BRAKING_FACTOR * intensity;
}
*/