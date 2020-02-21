#include "PingResp.hpp"

using namespace std;

PingResp::PingResp() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PINGRESP, ControlPacket::CONTROL_PACKET_FLAG_PINGRESP){
    this->remainingLength = 0x00;
}

PingResp::~PingResp(){

}

Bytes* PingResp::toBytes(){
    return ControlPacket::toBytes();
}
