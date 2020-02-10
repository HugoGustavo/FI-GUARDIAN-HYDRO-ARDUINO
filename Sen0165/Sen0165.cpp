#include "Sen0165.hpp"

using namespace std;

Sen0165::Sen0165(const unsigned int pin, const unsigned int offset){
    this->pin = pin;
    this->offset = offset;
    this->readings = new unsigned int[40];
    for(int i = 0; i < 40; i++) this->readings[i] = 0;
    this->index = 0;
}

unsigned int Sen0165::getPin(){
    return this->pin;
}

void Sen0165::setPin(const unsigned int pin){
    this->pin = pin;
}

unsigned int Sen0165::getOffset(){
    return this->offset;
}

void Sen0165::setOffset(const unsigned int offset){
    this->offset = offset;
}

unsigned int* Sen0165::getReadings(){
    return this->readings;
}

void Sen0165::setReadings(unsigned int* readings){
    this->readings = readings;
}

unsigned int Sen0165::getIndex(){
    return this->index;
}

void Sen0165::setIndex(const unsigned int index){
    this->index = index;
}

float Sen0165::read(){
    this->readings[this->index] = analogRead(this->pin);
    this->index = ( this->index + 1 ) % 40;
    float orpValue = ((30*(double)5.00*1000)-(75*average()*5.00*1000/1024))/75-this->offset;
    return orpValue;
}

float Sen0165::average(){
    int maximum, minimum;
    if( this->readings[0] < this->readings[1] ){
        minimum = this->readings[0]; maximum = this->readings[1];
    } else {
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