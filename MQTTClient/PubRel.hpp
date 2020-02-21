#ifndef PUBREL_HPP
#define PUBREL_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class PubRel : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubRel(const unsigned int packetIdentifier);

        ~PubRel();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();
};

#endif