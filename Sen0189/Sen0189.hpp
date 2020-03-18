#ifndef SEN0189_HPP
#define SEN0189_HPP

#include "Arduino.h"

class Sen0189 {
    private:
        unsigned int pin;

    public:
        Sen0189(const unsigned int pin);

        unsigned int getPin();

        void setPin(const unsigned int pin);

        float read();
};

#endif