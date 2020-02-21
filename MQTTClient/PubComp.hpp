#ifndef PUBCOMP_HPP
#define PUBCOMP_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubComp : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubComp(const unsigned int packetIdentifier);

        ~PubComp();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();
};

#endif