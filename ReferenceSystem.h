//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_REFERENCESYSTEM_H
#define COMPUTER_GRAPHICS_REFERENCESYSTEM_H

#include "Vec.h"
#include "geometry.h"
#include "matrix.h"

class ReferenceSystem
{
public:
    ReferenceSystem(float theta, float phi, ReferenceSystem r, float radius){
        // theta -> (0, PI), (0, 180)
        // phi -> (-PI, PI], (-180, 180)

        if (theta < 0 || theta - M_PI > 0.0001) {
            throw (Exception ("Inclination out of range"));
        }
        if (phi + M_PI < -0.0001 || phi - M_PI > 0.0001) {
            throw (Exception ("Azimuth out of range"));
        }

        // origin = radius * Vec(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta), POINT);
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

      // We let it in UCS
      origin = radius * Vec(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta), POINT);
      Matrix base = r.getMatrix();
      origin = base * origin; // IN UCS
    }

    ReferenceSystem(){}

    ReferenceSystem(Vec i, Vec j, Vec k, Vec origin){
        this->i = i;
        this->j = j;
        this->k = k;
        this->origin = origin;
    }

    Matrix getMatrix() {
        float matrix[N][N];
        matrix[0][0] = getI().getX();
        matrix[1][0] = getI().getY();
        matrix[2][0] = getI().getZ();
        matrix[3][0] = 0;

        matrix[0][1] = getJ().getX();
        matrix[1][1] = getJ().getY();
        matrix[2][1] = getJ().getZ();
        matrix[3][1] = 0;

        matrix[0][2] = getK().getX();
        matrix[1][2] = getK().getY();
        matrix[2][2] = getK().getZ();
        matrix[3][2] = 0;

        matrix[0][3] = getOrigin().getX();
        matrix[1][3] = getOrigin().getY();
        matrix[2][3] = getOrigin().getZ();
        matrix[3][3] = 1;

        return Matrix(matrix);
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

    bool operator==(const ReferenceSystem &rhs) const;

    bool operator!=(const ReferenceSystem &rhs) const;

private:
    Vec i, j, k, origin;
};

bool ReferenceSystem::operator==(const ReferenceSystem &rhs) const {
    return i == rhs.i &&
           j == rhs.j &&
           k == rhs.k &&
           origin == rhs.origin;
}

bool ReferenceSystem::operator!=(const ReferenceSystem &rhs) const {
    return !(rhs == *this);
}

#endif //COMPUTER_GRAPHICS_REFERENCESYSTEM_H
