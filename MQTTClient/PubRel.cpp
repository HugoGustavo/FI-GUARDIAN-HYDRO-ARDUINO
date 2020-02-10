#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PubRel.hpp"

using namespace std;

PubRel::PubRel(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBREL, ControlPacket::CONTROL_PACKET_FLAG_PUBREL){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

unsigned int PubRel::getPacketIdentifier(){
    return packetIdentifier;
}

void PubRel::setPacketIdentifier(unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

vector<unsigned char>* PubRel::toChar(){
    vector<unsigned char>* packetIdentifier = new vector<unsigned char>();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, packetIdentifier);
    return result;
}