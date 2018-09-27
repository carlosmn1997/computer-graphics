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
      float radio = planet.getRadio();
      center = parametricSpehere(theta, phi, radio, planet.getCenter()); // Position
      k = center - planet.getCenter(); // Surface normal
      k.getUnitVector();
      i = Vec::crossProduct(planet.getAxis(), k);
      i.getUnitVector();
      j = Vec::crossProduct(i, k);
      j.getUnitVector();
    }

    const Vec &getI() const {
        return i;
    }

    void setI(const Vec &i) {
        ReferenceSystem::i = i;
    }

    const Vec &getJ() const {
        return j;
    }

    void setJ(const Vec &j) {
        ReferenceSystem::j = j;
    }

    const Vec &getK() const {
        return k;
    }

    void setK(const Vec &k) {
        ReferenceSystem::k = k;
    }

    const Vec &getCenter() const {
        return center;
    }

    void setCenter(const Vec &center) {
        ReferenceSystem::center = center;
    }

    Vec changeReferenceSystem(Vec vec){
        float auxX = i.getX()*vec.getX() + j.getX()*vec.getY() + k.getX()*vec.getZ() + center.getX()*vec.getType();
        float auxY = i.getY()*vec.getX() + j.getY()*vec.getY() + k.getY()*vec.getZ() + center.getY()*vec.getType();
        float auxZ = i.getZ()*vec.getX() + j.getZ()*vec.getY() + k.getZ()*vec.getZ() + center.getZ()*vec.getType();
        float type = vec.getType();
        return Vec(auxX, auxY, auxZ, type);
    }
private:
    Vec i, j, k, center;
};

#endif //COMPUTER_GRAPHICS_REFERENCESYSTEM_H
