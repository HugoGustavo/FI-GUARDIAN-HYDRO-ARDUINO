#include "PubComp.hpp"

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

using namespace std;

PubComp::PubComp(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBCOMP, ControlPacket::CONTROL_PACKET_FLAG_PUBCOMP){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

unsigned int PubComp::getPacketIdentifier(){
    return packetIdentifier;
}

void PubComp::setPacketIdentifier(unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

vector<unsigned char>* PubComp::toChar(){
    vector<unsigned char>* packetIdentifier = new vector<unsigned char>();
    packetIdentifier->push_back( (unsigned char) ((0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) (0x00FF & this->packetIdentifier) );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, packetIdentifier);
    return result;
}