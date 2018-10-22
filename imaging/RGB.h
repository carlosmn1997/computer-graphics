//
// Created by Carlos on 22/10/2018.
//

#ifndef COMPUTER_GRAPHICS_RGB_H
#define COMPUTER_GRAPHICS_RGB_H

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

    float getR() const {
        return B;
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
};


#endif //COMPUTER_GRAPHICS_RGB_H
