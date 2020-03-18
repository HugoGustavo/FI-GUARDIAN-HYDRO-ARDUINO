#include "DS18B20.hpp"

using namespace std;

DS18B20::DS18B20(const unsigned int pin){
    this->reader = new DallasTemperature(new OneWire(pin));
}

DallasTemperature* DS18B20::getReader(){
    return this->reader;
}

void DS18B20::setReader(DallasTemperature* reader){
    this->reader = reader;
}

float DS18B20::read(){
    this->reader->requestTemperatures();
    return this->reader->getTempCByIndex(0);
}