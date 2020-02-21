#include "PubComp.hpp"

using namespace std;

PubComp::PubComp(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBCOMP, ControlPacket::CONTROL_PACKET_FLAG_PUBCOMP){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubComp::~PubComp(){
    this->packetIdentifier = 0;
}

unsigned int PubComp::getPacketIdentifier(){
    return packetIdentifier;
}

void PubComp::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubComp::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ((0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) (0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}
