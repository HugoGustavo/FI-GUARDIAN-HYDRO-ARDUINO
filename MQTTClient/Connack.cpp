#include "Connack.hpp"

using namespace std;

Connack::Connack(const bool cleanSession, const unsigned char returnCode) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_CONNACK, ControlPacket::CONTROL_PACKET_FLAG_CONNACK) {
    this->cleanSession = cleanSession;
    this->remainingLength = 0x02;
    this->returnCode = returnCode;
}

Connack::~Connack() {

}

bool Connack::isCleanSession(){
    return this->cleanSession;
}

void Connack::setCleanSession(const bool cleanSession){
    this->cleanSession = cleanSession;
}

unsigned char Connack::getReturnCode(){
    return returnCode;
}

void Connack::setReturnCode(const unsigned char returnCode){
    this->returnCode = returnCode;
}

Bytes* Connack::toBytes(){
    Bytes* result = ControlPacket::toBytes();
    result->push_back((unsigned char) ( this->cleanSession ? 0x00 : 0x01 ) );
    result->push_back(this->returnCode);
    return result;
}
