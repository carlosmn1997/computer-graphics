//
// Created by Carlos on 24/11/2018.
//

#ifndef COMPUTER_GRAPHICS_RANDOMNUMBER_H
#define COMPUTER_GRAPHICS_RANDOMNUMBER_H
#include <random>

class RandomNumber {
public:
    RandomNumber(){
        double lower_bound = 0;
        double upper_bound = 1;
        unif = std::uniform_real_distribution<double>(lower_bound,upper_bound);
    }

    float giveNumber(){
        return unif(re);
    }

private:
    std::uniform_real_distribution<double> unif;
    std::default_random_engine re;

};

#endif //COMPUTER_GRAPHICS_RANDOMNUMBER_H
