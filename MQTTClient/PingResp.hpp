#ifndef PINGRESP_HPP
#define PINGRESP_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingResp : public ControlPacket {
    public:
        PingResp();

        ~PingResp();

        Bytes* toBytes();
};

#endif