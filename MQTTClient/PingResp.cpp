#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "PingResp.hpp"

using namespace std;

PingResp::PingResp() : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PINGRESP, ControlPacket::CONTROL_PACKET_FLAG_PINGRESP){
    this->remainingLength = 0x00;
}

vector<unsigned char>* PingResp::toChar(){
    return ControlPacket::toChar();
}