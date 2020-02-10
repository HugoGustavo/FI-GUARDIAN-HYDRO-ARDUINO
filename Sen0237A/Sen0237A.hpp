#ifndef SEN0237A_HPP
#define SEN0237A_HPP

#include "Arduino.h"
#include <avr/pgmspace.h>
#include <EEPROM.h>

using namespace std;

class Sen0237A {
    private:
        bool modeCalibration;
        float saturationDoVoltage;
        float saturationDoTemperature;
        float averageVoltage;
        float temperature;
        unsigned int pin;

        const float saturationValueTable[41] PROGMEM = {
            14.46, 14.22, 13.82, 13.44, 13.09,
            12.74, 12.42, 12.11, 11.81, 11.53,
            11.26, 11.01, 10.77, 10.53, 10.30,
            10.08, 9.86,  9.66,  9.46,  9.27,
            9.08,  8.90,  8.73,  8.57,  8.41,
            8.25,  8.11,  7.96,  7.82,  7.69,
            7.56,  7.43,  7.30,  7.18,  7.07,
            6.95,  6.84,  6.73,  6.63,  6.53,
            6.41,
        };

        int* readings;
        
        int index;
    
    public:
        Sen0237A(const unsigned int pin, const bool modeCalibration);

        bool isModeCalibration();

        void setModeCalibration(const bool modeCalibration);

        unsigned int getSaturationDoVoltage();

        void setSaturationDoVoltage(unsigned int saturationDoVoltage);

        unsigned int getSaturationDoTemperature();

        void setSaturationDoTemperature(unsigned int saturationDoTemperature);

        float getAverageVoltage();

        void setAverageVoltage(float averageVoltage);

        float getTemperature();

        void setTemperature(float temperature);

        unsigned int getPin();

        void setPin(unsigned int pin);

        int* getReadings();

        void setReadings(int* readings);

        int getIndex();

        void setIndex(int index);
    
        float read();

    private:
        void EEPROM_write(unsigned int address, float p);

        void EEPROM_read(unsigned int address, float p);

        void configureEEPROM();

        void doCalibration();

        int median();

};

#endif

