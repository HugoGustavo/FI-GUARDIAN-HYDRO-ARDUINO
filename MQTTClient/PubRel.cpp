#include "PubRel.hpp"

using namespace std;

PubRel::PubRel(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBREL, ControlPacket::CONTROL_PACKET_FLAG_PUBREL){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubRel::~PubRel(){
    this->packetIdentifier = 0;
}

unsigned int PubRel::getPacketIdentifier(){
    return packetIdentifier;
}

void PubRel::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubRel::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    return result;
}
