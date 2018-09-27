//
// Created by Carlos on 27/09/2018.
//

#ifndef COMPUTER_GRAPHICS_PLANET_H
#define COMPUTER_GRAPHICS_PLANET_H
#include "Vec.h"

class Planet
{
public:
    Planet(Vec center, Vec axis, Vec referenceCity){
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
};


#endif //COMPUTER_GRAPHICS_PLANET_H
