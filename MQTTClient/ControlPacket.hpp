#ifndef CONTROLPACKET_HPP
#define CONTROLPACKET_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"

using namespace std;

class ControlPacket {
    protected:
        unsigned char type;
        unsigned char flags;
        long int remainingLength;

    public:
        static const unsigned char CONTROL_PACKET_TYPE_CONNECT      = 0x10;
        static const unsigned char CONTROL_PACKET_TYPE_CONNACK      = 0x20;
        static const unsigned char CONTROL_PACKET_TYPE_PUBLISH      = 0x30;
        static const unsigned char CONTROL_PACKET_TYPE_PUBACK       = 0x40;
        static const unsigned char CONTROL_PACKET_TYPE_PUBREC       = 0x50;
        static const unsigned char CONTROL_PACKET_TYPE_PUBREL       = 0x60;
        static const unsigned char CONTROL_PACKET_TYPE_PUBCOMP      = 0x70;
        static const unsigned char CONTROL_PACKET_TYPE_SUBSCRIBE    = 0x80;
        static const unsigned char CONTROL_PACKET_TYPE_SUBACK       = 0x90;
        static const unsigned char CONTROL_PACKET_TYPE_UNSUBSCRIBE  = 0xA0;
        static const unsigned char CONTROL_PACKET_TYPE_UNSUBACK     = 0xB0;
        static const unsigned char CONTROL_PACKET_TYPE_PINGREQ      = 0xC0;
        static const unsigned char CONTROL_PACKET_TYPE_PINGRESP     = 0xD0;
        static const unsigned char CONTROL_PACKET_TYPE_DISCONNECT   = 0xE0;

        static const unsigned char CONTROL_PACKET_FLAG_CONNECT      = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_CONNACK      = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PUBLISH      = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PUBACK       = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PUBREC       = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PUBREL       = 0x01;
        static const unsigned char CONTROL_PACKET_FLAG_PUBCOMP      = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_SUBSCRIBE    = 0x01;
        static const unsigned char CONTROL_PACKET_FLAG_SUBACK       = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_UNSUBSCRIBE  = 0x01;
        static const unsigned char CONTROL_PACKET_FLAG_UNSUBACK     = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PINGREQ      = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_PINGRESP     = 0x00;
        static const unsigned char CONTROL_PACKET_FLAG_DISCONNECT   = 0x00;

    public:
        ControlPacket(const unsigned char type, const unsigned char flags, const long int remainingLength=0x00000000);

        ~ControlPacket();

        unsigned char getType();
        
        void setType(const unsigned char type);
        
        unsigned char getFlags();
    
        void setFlags(const unsigned char flags);

        long int getRemainingLength();

        void setRemainingLength(const long int remainingLength);

        Bytes* toBytes();

};

#endif
