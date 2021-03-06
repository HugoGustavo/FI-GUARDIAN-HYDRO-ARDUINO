#include "Sen0189.hpp"

using namespace std;

Sen0189::Sen0189(const unsigned int pin){
    this->pin = pin;
}

unsigned int Sen0189::getPin(){
    return this->pin;
}

void Sen0189::setPin(const unsigned int pin){
    this->pin = pin;
}

float Sen0189::read(){
    int sensorValue = analogRead(this->pin);
    return sensorValue * (5.0 / 1024.0);
}