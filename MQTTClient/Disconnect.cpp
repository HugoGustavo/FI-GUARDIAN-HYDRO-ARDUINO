#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Disconnect.hpp"

using namespace std;

Disconnect::Disconnect() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_DISCONNECT, ControlPacket::CONTROL_PACKET_FLAG_DISCONNECT){
    this->remainingLength = 0x00;
}

vector<unsigned char>* Disconnect::toChar(){
    return ControlPacket::toChar();
}