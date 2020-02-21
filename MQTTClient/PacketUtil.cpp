#include "PacketUtil.hpp"

using namespace std;

Bytes* PacketUtil::build(String input){
    Bytes* result = new Bytes();
    
    int length = input.length();
    result->push_back( (unsigned char) ( (0xFF00 & length) >> 8 ) );
    result->push_back( (unsigned char) ( 0x00FF & length ) );
    for(int i = 0; i < length; i++) result->push_back( (unsigned char) input.charAt(i) );

    return result;
}

Bytes* PacketUtil::build(uint8_t* buffer, uint32_t size){
    Bytes* result = new Bytes();
    for(uint32_t i = 0; i < size; i++)
        result->push_back(buffer[i]);
    return result;
}

void PacketUtil::println(Bytes* input){
    PacketUtil::print(input);
    Serial.println();
}

void PacketUtil::print(Bytes* input){
    for(unsigned int i = 0; i < input->getSize(); i++)
        PacketUtil::print(input->at(i));
}

void PacketUtil::print(const unsigned char x){
    char value = (char) x;
    if( value >= 32 && value <= 126 ) Serial.print(value);
    else {
        Serial.print("\\x"); Serial.print(x, HEX);
    }
}

String PacketUtil::toString(Bytes* input){
    String result = String();

    for(unsigned int i = 0; i < input->getSize(); i++){
        unsigned char value = input->at(i);
        if( ((char) value) >= 33 && ((char) value) <= 126 ) result.concat(String((char) value));
        else result.concat("\\x" + String(value, HEX));
    }

    return result;
}
