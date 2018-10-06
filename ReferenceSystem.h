//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_REFERENCESYSTEM_H
#define COMPUTER_GRAPHICS_REFERENCESYSTEM_H

#include "Vec.h"
#include "geometry.h"

class ReferenceSystem
{
public:
    ReferenceSystem(float theta, float phi, ReferenceSystem r, float radius){
      origin = parametricSpehere(theta, phi, radius, r.getOrigin()); // Position of station
      k = origin - r.getOrigin(); // Surface normal
      k.getUnitVector();
      i = Vec::crossProduct(r.getI(), k); // positive azimuth
      i.getUnitVector();
      j = Vec::crossProduct(k, i); // positive inclination
      j.getUnitVector();

      i = r.changeReferenceSystem(i);
      j = r.changeReferenceSystem(j);
      k = r.changeReferenceSystem(k);
    }

    ReferenceSystem(Vec i, Vec j, Vec k){
        this->i = i;
        this->j = j;
        this->k = k;
    }

    ReferenceSystem(){}

    ReferenceSystem(Vec i, Vec j, Vec k, Vec origin){
        this->i = i;
        this->j = j;
        this->k = k;
        this->origin = origin;
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

    const Vec &getOrigin() const {
        return origin;
    }

    void setOrigin(const Vec &origin) {
        ReferenceSystem::origin = origin;
    }

    Vec changeReferenceSystem(Vec vec){
        float auxX = i.getX()*vec.getX() + j.getX()*vec.getY() + k.getX()*vec.getZ() + origin.getX()*vec.getType();
        float auxY = i.getY()*vec.getX() + j.getY()*vec.getY() + k.getY()*vec.getZ() + origin.getY()*vec.getType();
        float auxZ = i.getZ()*vec.getX() + j.getZ()*vec.getY() + k.getZ()*vec.getZ() + origin.getZ()*vec.getType();
        float type = vec.getType();
        return Vec(auxX, auxY, auxZ, type);
    }
private:
    Vec i, j, k, origin;
};

#endif //COMPUTER_GRAPHICS_REFERENCESYSTEM_H
