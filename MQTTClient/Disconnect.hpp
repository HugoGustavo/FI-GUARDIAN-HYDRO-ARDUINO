#ifndef DISCONNECT_HPP
#define DISCONNECT_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class Disconnect : public ControlPacket {
    public:
        Disconnect();
        
        vector<unsigned char>* toChar();

};

#endif