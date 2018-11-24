//
// Created by Carlos on 20/11/2018.
//

#ifndef COMPUTER_GRAPHICS_LIGHT_H
#define COMPUTER_GRAPHICS_LIGHT_H

#include "../Vec.h"
#include "../imaging/RGB.h"

class Light{
private:
    float power;
    Vec position;
public:
    Light() {}

    Light(float power, const Vec &position) : power(power), position(position) {}

    RGB getPower() const {
        return RGB(power, power, power);
    }

    void setPower(float power) {
        Light::power = power;
    }

    const Vec &getPosition() const {
        return position;
    }

    void setPosition(const Vec &position) {
        Light::position = position;
    }
};

#endif //COMPUTER_GRAPHICS_LIGHT_H
