#include "Sen0161.hpp"

using namespace std;

Sen0161::Sen0161(const unsigned int pin, const float offset){
    this->pin = pin;
    this->offset = offset;
    this->readings = new unsigned int[40];
    for(int i = 0; i < 40; i++) this->readings[i] = 0;
    this->index = 0;
}

unsigned int Sen0161::getPin(){
    return this->pin;
}

void Sen0161::setPin(const unsigned int pin){
    this->pin = pin;
}

float Sen0161::getOffset(){
    return this->offset;
}

void Sen0161::setOffset(const float offset){
    this->offset = offset;
}

unsigned int* Sen0161::getReadings(){
    return this->readings;
}

void Sen0161::setReadings(unsigned int* readings){
    this->readings = readings;
}

unsigned int Sen0161::getIndex(){
    return this->index;
}

void Sen0161::setIndex(const unsigned int index){
    this->index = index;
}

float Sen0161::read(){
    this->readings[this->index] = analogRead(this->pin);
    this->index = ( this->index + 1 ) % 40;
    float phValue = 3.5*(this->average()*5.0/1024) + this->offset;
    return phValue;
}

float Sen0161::average(){
    unsigned int maximum, minimum;
    if( this->readings[0] < this->readings[1] ){
        minimum = this->readings[0]; maximum = this->readings[1];
    }
    else {
        minimum = this->readings[1]; maximum = this->readings[0];
    }
    
    int i;
    long amount = 0;
    for(i=2; i < 40; i++){
        if( this->readings[i] < minimum) {
            amount += minimum; minimum = this->readings[i];
        } else if( this->readings[i] > maximum ) {
            amount += maximum; maximum = this->readings[i];
        } else {
            amount += this->readings[i];
        }
    }

    float average = (float) amount / (40-2);
    return average;
}