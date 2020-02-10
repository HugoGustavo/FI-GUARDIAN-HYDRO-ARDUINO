#include "Sen0237A.hpp"
#include <avr/pgmspace.h> 
#include <EEPROM.h>

Sen0237A::Sen0237A(const unsigned int pin, const bool modeCalibration){
    this->pin = pin;
    this->modeCalibration = modeCalibration;

    this->saturationDoVoltage = 0.0;
    this->saturationDoTemperature = 0.0;
    this->averageVoltage = 0.0;
    this->temperature = 0.0;

    this->index = 0;
    this->readings = new int[30];
    for(int i = 0; i < 30; i++) this->readings[i] = 0;

    pinMode(this->pin, INPUT);
    this->configureEEPROM();
}

bool Sen0237A::isModeCalibration(){
    return this->modeCalibration;
}

void Sen0237A::setModeCalibration(const bool modeCalibration){
    this->modeCalibration = modeCalibration;
}

unsigned int Sen0237A::getSaturationDoVoltage(){
    return this->saturationDoVoltage;
}

void Sen0237A::setSaturationDoVoltage(unsigned int saturationDoVoltage){
    this->saturationDoVoltage = saturationDoVoltage;
}

unsigned int Sen0237A::getSaturationDoTemperature(){
    return this->saturationDoTemperature;
}

void Sen0237A::setSaturationDoTemperature(unsigned int saturationDoTemperature){
    this->saturationDoTemperature = saturationDoTemperature;
}

float Sen0237A::getAverageVoltage(){
    return this->averageVoltage;
}

void Sen0237A::setAverageVoltage(float averageVoltage){
    this->averageVoltage = averageVoltage;
}

float Sen0237A::getTemperature(){
    return this->temperature;
}

void Sen0237A::setTemperature(float temperature){
    this->temperature = temperature;
}

unsigned int Sen0237A::getPin(){
    return this->pin;
}

void Sen0237A::setPin(unsigned int pin){
    this->pin = pin;
}

int* Sen0237A::getReadings(){
    return this->readings;
}

void Sen0237A::setReadings(int* readings){
    this->readings = readings;
}

int Sen0237A::getIndex(){
    return this->index;
}

void Sen0237A::setIndex(int index){
    this->index = index;
}

float Sen0237A::read(){
    if ( ! Sen0237A::isModeCalibration() ){
        this->readings[this->index] = analogRead(this->pin);
        this->index = ( this->index + 1 ) % 30;
        this->averageVoltage = median() * (float) 5000 / 1024.0;
        float dissolvedOxygenValue =  pgm_read_float_near( &this->saturationValueTable[0] + (int)(this->saturationDoTemperature+0.5) ) * averageVoltage / this->saturationDoVoltage;
        return dissolvedOxygenValue;
    } else {
        this->doCalibration();
        return 0.0;
    }
}

void Sen0237A::EEPROM_write(unsigned int address, float p){
    int i = 0;
    byte *pp = (byte*)&(p);
    for(; i < sizeof(p); i++)
        EEPROM.write(address+i, pp[i]); 
}
        
void Sen0237A::EEPROM_read(unsigned int address, float p){
    int i = 0;
    byte *pp = (byte*)&(p);
    for(; i < sizeof(p); i++)
        pp[i]=EEPROM.read(address+i);
}

void Sen0237A::configureEEPROM(){
    this->EEPROM_read(12, this->saturationDoVoltage);
    this->EEPROM_read(16, this->saturationDoTemperature);

    if(EEPROM.read(12)==0xFF && EEPROM.read(12+1)==0xFF && EEPROM.read(12+2)==0xFF && EEPROM.read(12+3)==0xFF){
        this->saturationDoVoltage = 1127.6;
        EEPROM_write(12, this->saturationDoVoltage);
    }

    if(EEPROM.read(16)==0xFF && EEPROM.read(16+1)==0xFF && EEPROM.read(16+2)==0xFF && EEPROM.read(16+3)==0xFF){
        this->saturationDoTemperature = 25.0;
        EEPROM_write(16, this->saturationDoTemperature);
    }
}

void Sen0237A::doCalibration(){
    this->EEPROM_write(12, this->averageVoltage);
    this->EEPROM_write(16, this->temperature);
    this->saturationDoVoltage = this->averageVoltage;
    this->saturationDoTemperature = this->temperature;
}

int Sen0237A::median(){
    int* readingsTemp = new int[30];
    for(int i = 0; i < 30; i++) readingsTemp[i] = this->readings[i];

    // Ordering for calculating the median
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 30 - 1; j++){
            if ( readingsTemp[j] > readingsTemp[j+1] ){
                int aux = readingsTemp[j];
                readingsTemp[j] = readingsTemp[j+1];
                readingsTemp[j+1] = aux;
            }
        }
    }

    int median = ( readingsTemp[14] + readingsTemp[15]) / 2;

    return median;
} 