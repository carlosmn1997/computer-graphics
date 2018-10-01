//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_PLANET_H
#define COMPUTER_GRAPHICS_PLANET_H
#include "Vec.h"
#include <cmath>

class Planet
{
public:
    Planet(Vec center, Vec axis, Vec referenceCity){
        float radius = (center - referenceCity).modulus();
        // Check if  radius defined by the axis and by the distance between the center and
        //the reference city is the same (maximum error of 10−6)
        float difference = radius - axis.modulus()/2; // The radius
        if(abs(difference) > 0.000001){
            std::cout<< "Radius not OK";
            std::exit(1);
        }
        this->center = center;
        this->axis = axis;
        this->referenceCity = referenceCity;
    }
private:
    Vec center, axis, referenceCity;
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
