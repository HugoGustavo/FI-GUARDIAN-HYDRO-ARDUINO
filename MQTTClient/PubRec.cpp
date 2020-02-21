#include "PubRec.hpp"

using namespace std;

PubRec::PubRec(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBREC, ControlPacket::CONTROL_PACKET_FLAG_PUBREC){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubRec::~PubRec(){
    this->packetIdentifier = 0;
}

unsigned int PubRec::getPacketIdentifier(){
    return packetIdentifier;
}

void PubRec::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubRec::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}
