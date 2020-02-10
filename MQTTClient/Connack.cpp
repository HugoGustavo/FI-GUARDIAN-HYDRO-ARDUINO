#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Connack.hpp"

using namespace std;

Connack::Connack(bool cleanSession, const unsigned char returnCode) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_CONNACK, ControlPacket::CONTROL_PACKET_FLAG_CONNACK) {
    this->cleanSession = cleanSession;
    this->remainingLength = 0x02;
    this->returnCode = returnCode;
}

bool Connack::getCleanSession(){
    return cleanSession;
}

void Connack::setCleanSession(bool cleanSession){
    this->cleanSession = cleanSession;
}

unsigned char Connack::getReturnCode(){
    return returnCode;
}

void Connack::setReturnCode(const unsigned char returnCode){
    this->returnCode = returnCode;
}

vector<unsigned char>* Connack::toChar(){
    return nullptr;
}