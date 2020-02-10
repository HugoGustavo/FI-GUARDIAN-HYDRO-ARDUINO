#ifndef PINGRESP_HPP
#define PINGRESP_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PingResp : public ControlPacket {
    public:
        PingResp();

        vector<unsigned char>* toChar();
};

#endif