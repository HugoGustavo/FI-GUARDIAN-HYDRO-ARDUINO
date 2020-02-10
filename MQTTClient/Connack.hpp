#ifndef CONNACK_HPP
#define CONNACK_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "PacketUtil.hpp"
#include "ControlPacket.hpp"

using namespace std;

class Connack : public ControlPacket {
    private:
        bool cleanSession;
        unsigned char returnCode;

    public:
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_ACCEPTED                              = 0x00;
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_UNACCEPTABLE_PROTOCOL_VERSION = 0x01;
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_IDENTIFIER_REJECTED           = 0x02;
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_SERVER_UNAVAILABLE            = 0x03;
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_BAD_USERNAME_OR_PASSWORD      = 0x04;
        static const unsigned char CONNACK_RETURN_CODE_CONNECTION_REFUSED_NOT_AUTHORIZED                = 0x05;

        Connack(bool cleanSession, const unsigned char returnCode);

        bool getCleanSession();

        void setCleanSession(bool cleanSession);

        unsigned char getReturnCode();

        void setReturnCode(const unsigned char returnCode);

        vector<unsigned char>* toChar();
};

#endif