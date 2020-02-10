#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "MQTTClient.hpp"

MQTTClient::MQTTClient(ESP8266* wifi){ 
    this->wifi = wifi;
    this->connected = false;
    this->cleanSession = true;
}

String MQTTClient::getId(){
    return this->id;
}

void MQTTClient::setId(String id){
    this->id = id;
}

String MQTTClient::getIP(){
    return this->ip;
}

void MQTTClient::setIP(String ip){
    this->ip = ip;
}

ESP8266* MQTTClient::getWifi(){
    return this->wifi;
}

void MQTTClient::setWifi(ESP8266* wifi){
    this->wifi = wifi;
}

bool MQTTClient::isConnected(){
    return this->connected;
}

void MQTTClient::setConnected(const bool connected){
    this->connected = connected;
}

unsigned int MQTTClient::getPort(){
    return this->port;
}

void MQTTClient::setPort(const unsigned int port){
    this->port = port;
}

bool MQTTClient::isCleanSession(){
    return this->cleanSession;
}

void MQTTClient::setCleanSession(const bool cleanSession){
    this->cleanSession = cleanSession;
}

String MQTTClient::toString(){
    return getId();
}

void MQTTClient::connect(){
    if ( ! this->wifi->createTCP(this->ip, this->port) ){
        setConnected(false);
        return;
    }
    uint8_t buffer[1024] = {0};
    Connect* connect = new Connect(false, false, false, Connect::CONNECT_QOS_0, false, this->isCleanSession());
    connect->setClientIdentifier(this->getId());
    vector<unsigned char>* connectPacket = connect->toChar();
    this->wifi->send((const uint8_t*)connectPacket, sizeof connectPacket);
    uint32_t received = this->wifi->recv(buffer, sizeof(buffer), 10000); // 10.000 for timeout
    if ( received > 0 ){
        Connack* connack = new Connack(this->cleanSession, Connack::CONNACK_RETURN_CODE_CONNECTION_ACCEPTED);
        setConnected( true );
    }
    if( ! this->isConnected() ) this->wifi->releaseTCP();
}

void MQTTClient::publish(String topic, String payload){
    if( ! isConnected() ) return;

    Publish* publish = new Publish(false, Publish::PUBLISH_QOS_LEVEL_0, false);
    publish->setTopicName(topic);
    publish->setPayload(payload);

    vector<unsigned char>* publishPacket = publish->toChar();
    this->wifi->send((const uint8_t*)publishPacket, sizeof publishPacket);
}

void MQTTClient::disconnect(){
    if( ! isConnected() ) return ;

    Disconnect* disconnect = new Disconnect();
    vector<unsigned char>* disconnectPacket = disconnect->toChar();
    this->wifi->send((const uint8_t*)disconnectPacket, sizeof disconnectPacket);
    this->wifi->releaseTCP();
}