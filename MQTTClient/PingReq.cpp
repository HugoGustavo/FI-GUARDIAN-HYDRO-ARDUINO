#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PingReq.hpp"

using namespace std;

PingReq::PingReq() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PINGREQ, ControlPacket::CONTROL_PACKET_FLAG_PINGREQ){
    this->remainingLength = 0x00;
}

vector<unsigned char>* PingReq::toChar(){
    return ControlPacket::toChar();
}