//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_PLANET_H
#define COMPUTER_GRAPHICS_PLANET_H
#include "Vec.h"
#include <cmath>
#include "ReferenceSystem.h"
#include "exception.h"

class Planet
{
public:
    Planet(Vec center, Vec axis, Vec referenceCity){
        float radius = (center - referenceCity).modulus();
        // Check if  radius defined by the axis and by the distance between the center and
        //the reference city is the same (maximum error of 10−6)
        float difference = radius - axis.modulus()/2; // The radius
        if(abs(difference) > 0.000001){
            throw (Exception ("Radius not OK"));
        }
        this->center = center;
        this->axis = axis;
        this->referenceCity = referenceCity;

        // Now calculate the reference system of the own planet

        Vec k = axis;
        k.getUnitVector();
        Vec toRefCity = referenceCity - center;
        float cosBeta = (axis * toRefCity) / (axis.modulus() * toRefCity.modulus());
        float a1Scalar = toRefCity.modulus() * cosBeta;
        Vec a1 = a1Scalar * k;
        Vec a2 = toRefCity - a1;
        if(a2.modulus() == 0){
            std::cout<< "Reference city can't be in the poles";
            std::exit(1);
        }
        a2.getUnitVector();
        Vec i = a2;
        Vec j = Vec::crossProduct(i, k);
        this->r = ReferenceSystem(i, j, k, center);

        // this->r = ReferenceSystem(i, axis, k, center);

        // https://en.wikipedia.org/wiki/Vector_projection

    }

    const ReferenceSystem &getR() const {
        return r;
    }

    void setR(const ReferenceSystem &r) {
        Planet::r = r;
    }

private:
    Vec center, axis, referenceCity;
    ReferenceSystem r;
public:
    const Vec &getCenter() const {
        return center;
    }

    void setCenter(const Vec &center) {
        Planet::center = center;
    }

    const Vec &getAxis() const {
        return axis;
    }

    void setAxis(const Vec &axis) {
        Planet::axis = axis;
    }

    const Vec &getReferenceCity() const {
        return referenceCity;
    }

    void setReferenceCity(const Vec &referenceCity) {
        Planet::referenceCity = referenceCity;
    }

    float getRadio(){
        return axis.modulus()/2;
    }
};


#endif //COMPUTER_GRAPHICS_PLANET_H
