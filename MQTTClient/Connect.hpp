
#ifndef CONNECT_HPP
#define CONNECT_HPP

#include "Arduino.h"
#include "Bytes.hpp"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"


using namespace std;

class Connect : public ControlPacket {
    private:
        Bytes* variableHeader;
        unsigned int keepAlive;
        String clientIdentifier;
        String willTopic;
        String willMessage;
        String userName;
        String password;

    public:
        static const unsigned char CONNECT_QOS_0 = 0x00;
        static const unsigned char CONNECT_QOS_1 = 0x01;
        static const unsigned char CONNECT_QOS_2 = 0x02;

        Connect(const bool userName, const bool password, const bool willRetain, const unsigned char willQoS, const bool willFlag, const bool cleanSession);

        ~Connect();

        Bytes* getVariableHeader();

        void setVariableHeader(Bytes* variableHeader);

        unsigned int getKeepAlive();

        void setKeepAlive(const unsigned int keepAlive);

        String getClientIdentifier();

        void setClientIdentifier(String clientIdentifier);

        String getWillTopic();

        void setWillTopic(String willTopic);

        String getWillMessage();

        void setWillMessage(String willMessage);

        String getUserName();

        void setUserName(String userName);

        String getPassword();

        void setPassword(String password);

        Bytes* toBytes();
};

#endif