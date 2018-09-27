//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_REFERENCESYSTEM_H
#define COMPUTER_GRAPHICS_REFERENCESYSTEM_H

#include "Planet.h"
#include "Vec.h"
#include "geometry.h"

class ReferenceSystem
{
public:
    ReferenceSystem(float theta, float phi, Planet planet){
      Vec vec(1,2,3,POINT);
      i = vec;
      j = vec;
      k = vec;
      float radio = 100;
      center = parametricSpehere(theta, phi, radio, planet.getCenter());
    }
private:
    Vec i, j, k, center;
};

#endif //COMPUTER_GRAPHICS_REFERENCESYSTEM_H
