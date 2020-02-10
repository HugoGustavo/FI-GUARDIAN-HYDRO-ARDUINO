#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PubAck.hpp"

using namespace std;

PubAck::PubAck(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBACK, ControlPacket::CONTROL_PACKET_FLAG_PUBACK){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

unsigned int PubAck::getPacketIdentifier(){
    return packetIdentifier;
}

void PubAck::setPacketIdentifier(unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

vector<unsigned char>* PubAck::toChar(){
    vector<unsigned char>* packetIdentifier = new vector<unsigned char>();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, packetIdentifier);
    return result;
}