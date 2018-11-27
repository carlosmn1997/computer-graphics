//
// Created by Carlos on 22/10/2018.
//

#ifndef COMPUTER_GRAPHICS_RGB_H
#define COMPUTER_GRAPHICS_RGB_H
#include <iostream>

class RGB{
private:
    float R, G, B;
public:
    RGB(){}
    RGB(float R, float G, float B){
        this->R = R;
        this->G = G;
        this->B = B;
    }

    bool operator==(const RGB &rhs) const {
        return R == rhs.R &&
               G == rhs.G &&
               B == rhs.B;
    }

    bool operator!=(const RGB &rhs) const {
        return !(rhs == *this);
    }

    float getR() const {
        return R;
    }

    void setR(float R) {
        this->R = R;
    }

    float getG() const {
        return G;
    }

    void setG(float G) {
        this->G = G;
    }

    float getB() const {
        return B;
    }

    void setB(float B) {
        this->B = B;
    }

    float getMax(){
        return std::max(R, std::max(G, B));
    }

    RGB operator* (const float& first) const {
        return RGB(R*first, G*first, B*first);
    }

    RGB operator / (const float& first) const {
        return RGB(R/first, G/first, B/first);
    }

    RGB operator* (const RGB& first) const {
        return RGB(R*first.getR(), G*first.getG(), B*first.getB());
    }

    RGB operator+ (const RGB& first) const {
        return RGB(R+first.getR(), G+first.getG(), B+first.getB());
    }
};


#endif //COMPUTER_GRAPHICS_RGB_H
