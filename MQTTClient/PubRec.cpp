#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PubRec.hpp"

using namespace std;

PubRec::PubRec(const unsigned int packetIdentifier) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBREC, ControlPacket::CONTROL_PACKET_FLAG_PUBREC){
    this->packetIdentifier = packetIdentifier;
    this->remainingLength = 0x02;
}

unsigned int PubRec::getPacketIdentifier(){
    return packetIdentifier;
}

void PubRec::setPacketIdentifier(unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

vector<unsigned char>* PubRec::toChar(){
    vector<unsigned char>* packetIdentifier = new vector<unsigned char>();
    packetIdentifier->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
    packetIdentifier->push_back( (unsigned char) ( 0x00FF & this->packetIdentifier) );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, packetIdentifier);
    return result;
}