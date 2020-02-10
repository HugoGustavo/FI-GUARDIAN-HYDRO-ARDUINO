#ifndef MQTTCLIENT_HPP
#define MQTTCLIENT_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"
#include "ESP8266.h"
#include "Connect.hpp" 
#include "Connack.hpp"
#include "Publish.hpp"
#include "Disconnect.hpp"
#include "PacketUtil.hpp"

using namespace std;

class MQTTClient {
    private:
        String id;
        String ip;
        ESP8266* wifi;
        bool connected;
        unsigned int port;
        bool cleanSession;

    public:
        MQTTClient(ESP8266* wifi);

        String getId();

        void setId(String id);

        String getIP();

        void setIP(String ip);

        ESP8266* getWifi();

        void setWifi(ESP8266* wifi);
    
        bool isConnected();

        void setConnected(const bool connected);

        unsigned int getPort();

        void setPort(const unsigned int port);

        bool isCleanSession();

        void setCleanSession(const bool cleanSession);

        String toString();

        void connect();

        void publish(String topic, String payload);

        void disconnect();  
};

#endif