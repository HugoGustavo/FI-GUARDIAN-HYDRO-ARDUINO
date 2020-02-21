#include "PubAck.hpp"

using namespace std;

PubAck::PubAck(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBACK, ControlPacket::CONTROL_PACKET_FLAG_PUBACK){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

PubAck::~PubAck(){
    this->packetIdentifier = 0;
}

unsigned int PubAck::getPacketIdentifier(){
    return packetIdentifier;
}

void PubAck::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

Bytes* PubAck::toBytes(){
    Bytes* packetIdentifier = new Bytes();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    Bytes* result = ControlPacket::toBytes();
    result->concat(packetIdentifier);
    
    return result;
}
