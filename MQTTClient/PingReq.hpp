#ifndef PINGREQ_HPP
#define PINGREQ_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingReq : public ControlPacket {
    public:
        PingReq();

        ~PingReq();

        Bytes* toBytes();
};

#endif