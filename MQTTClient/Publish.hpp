#ifndef PUBLISH_HPP
#define PUBLISH_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp" 

using namespace std;

class Publish : public ControlPacket {
    private:
        bool dup;
        unsigned char qosLevel;
        bool retain;
        String topicName;
        unsigned int packetIdentifier;
        String payload;

    public:
        static const unsigned char PUBLISH_QOS_LEVEL_0 = 0x00;
        static const unsigned char PUBLISH_QOS_LEVEL_1 = 0x01;
        static const unsigned char PUBLISH_QOS_LEVEL_2 = 0x02;

        Publish(const bool dup, const unsigned char qosLevel, const bool retain);

        bool isDup();

        void setDup(const bool dup);

        unsigned char getQoSLevel();

        void setQoSLevel(const unsigned char qosLevel);

        bool isRetain();

        void setRetain(const bool retain);

        String getTopicName();

        void setTopicName(String topicName);

        unsigned int getPacketIdentifier();

        void setPacketIdentifier(const unsigned int packetIdentifier);

        String getPayload();

        void setPayload(String payload);

        vector<unsigned char>* toChar();
};

#endif