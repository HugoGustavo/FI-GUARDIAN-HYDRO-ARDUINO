#ifndef SEN0165_HPP
#define SEN0165_HPP

#include "Arduino.h"

using namespace std;

class Sen0165 {
    private:
        unsigned int pin;
        unsigned int offset;
        unsigned int* readings;
        unsigned int index;

    public:
        Sen0165(const unsigned int pin, const unsigned int offset=0);

        unsigned int getPin();

        void setPin(const unsigned int pin);

        unsigned int getOffset();

        void setOffset(const unsigned int offset);

        unsigned int* getReadings();

        void setReadings(unsigned int* readings);

        unsigned int getIndex();

        void setIndex(const unsigned int index);

        float read();

    private:
        float average();
};

#endif