#ifndef PUBREC_HPP
#define PUBREC_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;


class PubRec : public ControlPacket {
    private:
        unsigned int packetIdentifier;
    
    public:
        PubRec(const unsigned int packetIdentifier);

        ~PubRec();

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        Bytes* toBytes();
};

#endif