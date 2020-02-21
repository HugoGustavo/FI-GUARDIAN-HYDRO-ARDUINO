#include "PingReq.hpp"

using namespace std;

PingReq::PingReq() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PINGREQ, ControlPacket::CONTROL_PACKET_FLAG_PINGREQ){
    this->remainingLength = 0x00;
}

PingReq::~PingReq(){

}

Bytes* PingReq::toBytes(){
    return ControlPacket::toBytes();
}
