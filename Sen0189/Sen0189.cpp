#include "Sen0189.hpp"

using namespace std;

Sen0189::Sen0189(const unsigned int pin){
    this->pin = pin;
}

unsigned int Sen0189::getPin(){
    return this->pin;
}

void Sen0189::setPing(const unsigned int pin){
    this->pin = pin;
}

float Sen0189::read(){
    int sensorValue = analogRead(A0);
    return sensorValue * (5.0 / 1024.0);
}