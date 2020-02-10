#ifndef PUBCOMP_HPP
#define PUBCOMP_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubComp : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubComp(const unsigned int packetIdentifier);

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(unsigned int packetIdentifier);

        vector<unsigned char>* toChar();
};

#endif