#include "Disconnect.hpp"

using namespace std;

Disconnect::Disconnect() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_DISCONNECT, ControlPacket::CONTROL_PACKET_FLAG_DISCONNECT){
    this->remainingLength = 0x00;
}

Disconnect::~Disconnect(){

}

Bytes* Disconnect::toBytes(){
    return ControlPacket::toBytes();
}
