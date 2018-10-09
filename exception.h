//
// Created by Nicolas on 09/10/2018.
//

#ifndef COMPUTER_GRAPHICS_EXCEPTION_H
#define COMPUTER_GRAPHICS_EXCEPTION_H

#include <iostream>

using namespace std;

class Exception {

public:
    Exception(const string& msg) : msg_(msg) {}
    ~Exception() {}

    string getMessage() const {return(msg_);}
private:
    string msg_;
};

#endif //COMPUTER_GRAPHICS_EXCEPTION_H
