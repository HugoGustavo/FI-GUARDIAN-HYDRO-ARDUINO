#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "ControlPacket.hpp"

using namespace std;

ControlPacket::ControlPacket(const unsigned char type, const unsigned char flags, const long int remainingLength){
    this->type = type;
    this->flags = flags;
    this->remainingLength = remainingLength;
}

unsigned char ControlPacket::getType(){ 
    return type;
}

void ControlPacket::setType(const unsigned char type) {
    this->type = type;
}

unsigned char ControlPacket::getFlags(){
    return flags;
}

void ControlPacket::setFlags(unsigned char flags){
    this->flags = flags;
}

long int ControlPacket::getRemainingLength(){
    return remainingLength;
}

void ControlPacket::setRemainingLength(const long int remainingLength){
    this->remainingLength = remainingLength;
}

vector<unsigned char>* ControlPacket::toChar(){
    vector<unsigned char>* result = new vector<unsigned char>();
    result->push_back( this->type | this->flags );

    unsigned char encodeByte;
    long int remainingLength = this->remainingLength;
    do {
        encodeByte = remainingLength % 128;
        remainingLength = remainingLength / 128;
        if( remainingLength ) encodeByte = encodeByte | 0x80;
        result->push_back( encodeByte );
    } while ( remainingLength > 0 );
    
    return result;
}