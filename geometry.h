//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_GEOMETRY_H
#define COMPUTER_GRAPHICS_GEOMETRY_H

#include <iostream>
#include "Vec.h"
#include <cmath>
using namespace std;

int nada(){
    return 1;
}

Vec parametricSpehere(float theta, float phi, float r, Vec c){
    // Se pone tipo punto para que la multiplicación no afecte
    Vec aux(sin(theta)*cos(phi), sin(theta)*cos(phi), cos(theta), POINT);

    // La suma debe comprobar que son puntos con puntos y direcciones con direcciones
    return c + r*aux;
}


#endif
