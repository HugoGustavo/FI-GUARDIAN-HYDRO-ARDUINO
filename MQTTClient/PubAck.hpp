#ifndef PUBACK_HPP
#define PUBACK_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubAck : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubAck(const unsigned int packetIdentifier);

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(unsigned int packetIdentifier);

        vector<unsigned char>* toChar();
};

#endif