#ifndef PINGREQ_HPP
#define PINGREQ_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingReq : public ControlPacket {
    public:
        PingReq();

        vector<unsigned char>* toChar();
};

#endif