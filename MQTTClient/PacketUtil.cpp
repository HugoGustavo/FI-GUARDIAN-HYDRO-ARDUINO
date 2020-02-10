#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PacketUtil.hpp"

using namespace std;

vector<unsigned char>* PacketUtil::buildField(String field){
    int length = field.length();
    vector<unsigned char>* result = new vector<unsigned char>();

    result->push_back( (unsigned char) ( (0xFF00 & length) >> 8 ) );
    result->push_back( (unsigned char) ( 0x00FF & length ) );
    for(int i = 0; i < length; i++) result->push_back( (unsigned char) field.charAt(i) );

    return result;    
}

vector<unsigned char>* PacketUtil::concat(vector<unsigned char>* destiny, vector<unsigned char>* source){
    vector<unsigned char>* result = new vector<unsigned char>();
    vector<unsigned char>::iterator end;
    
    end = result->end();
    result->insert(end, destiny->begin(), destiny->end());
    end = result->end();
    result->insert(end, source->begin(), source->end());

    return result;
}

unsigned int PacketUtil::length(vector<unsigned char>* destiny){
    return destiny->size();
}

bool PacketUtil::equals(vector<unsigned char>* destiny, vector<unsigned char>* source){
    return (*destiny) == (*source);
}

void PacketUtil::println(vector<unsigned char>* field){
    PacketUtil::print(field);
    Serial.println();
}

void PacketUtil::print(vector<unsigned char>* field){
    for(vector<unsigned char>::iterator it = field->begin(); it != field->end(); ++it)
        PacketUtil::print(*it);
}

void PacketUtil::print(unsigned char x){
    char value = (char) x;
    if( value >= 32 && value <= 126 ) Serial.print(value);
    else {
        Serial.print("\\x"); Serial.print(x, HEX);
    }
}
