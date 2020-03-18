#ifndef DS18B20_HPP
#define DS18B20_HPP

#include "Arduino.h"
#include "OneWire.h"
#include "DallasTemperature.h"

using namespace std;

class DS18B20 {
    private:
        DallasTemperature* reader;

    public:    
        DS18B20(const unsigned int pin);

        DallasTemperature* getReader();

        void setReader(DallasTemperature* reader);

        float read();
};

#endif