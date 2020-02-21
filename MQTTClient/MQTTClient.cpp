#include "MQTTClient.hpp"

MQTTClient::MQTTClient(ESP8266* wifi){ 
    this->wifi = wifi;
    this->connected = false;
    this->cleanSession = true;
}

MQTTClient::~MQTTClient(){
    this->id = "";
    this->ip = "";
    this->wifi = nullptr;
    this->connected = false;
    this->port = 0;
    this->cleanSession = false;
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
    if ( isConnected() ) {
        Logger::info("You are already logged in to the server " + String(this->getIP()) + ":" + String(this->getPort()));
        return;
    }

    Logger::info("Connecting to the server " + String(this->getIP()) + ":" + String(this->getPort()));

    bool connected = false;
    if ( createTCPConnection() ){
        sendConnectPacket();
        connected = receiveConnackPacket();
    }

    if ( connected ) Logger::info("Connected  to the server " + String(this->getIP()) + ":" + String(this->getPort()));
    else Logger::info("Could not connect to the server " + String(this->getIP()) + ":" + String(this->getPort()));
    
    setConnected( connected );
}

bool MQTTClient::createTCPConnection(){
    Logger::info("Creating a tcp connection on the server " + String(this->getIP()) + ":" + String(this->getPort()));
    return this->wifi->createTCP(this->ip, this->port);
}

void MQTTClient::sendConnectPacket(){
    Connect* connect = new Connect(false, false, false, Connect::CONNECT_QOS_0, false, this->cleanSession);
    connect->setClientIdentifier(this->getId());
    Bytes* bytes = connect->toBytes();
    this->wifi->send((const uint8_t*)bytes->toArray(), bytes->getSize());

    delete(bytes);
    delete(connect);
}

bool MQTTClient::receiveConnackPacket(){
    Connack* connack = new Connack(this->cleanSession, Connack::CONNACK_RETURN_CODE_CONNECTION_ACCEPTED);
    bool receiveConnackPacket = false;
    
    Bytes* bytesConnackPacket = connack->toBytes();
    uint8_t buffer[bytesConnackPacket->getSize()] = {0};
    uint32_t len = this->wifi->recv(buffer, sizeof(buffer), 10000);
    if ( len > 0 ){
        Bytes* bytesReceived = PacketUtil::build(buffer, len);
        receiveConnackPacket = bytesReceived->equals(bytesConnackPacket);
        delete(bytesReceived);
    }
    delete(bytesConnackPacket);
    delete(connack);

    return receiveConnackPacket;
}

void MQTTClient::publish(String topic, String payload){
    if( ! isConnected() ) {
        Logger::error("You are not connected! First connect to the server to publish.");
        return;
    }

    Publish* publish = new Publish(false, Publish::PUBLISH_QOS_LEVEL_0, false);
    publish->setPayload(payload);
    publish->setTopicName(topic);

    Bytes* bytes = publish->toBytes();
    this->wifi->send((const uint8_t*)bytes->toArray(), bytes->getSize());

    delete(bytes);
    delete(publish);
}

void MQTTClient::disconnect(){
    if( ! isConnected() ) {
        Logger::error("You are not connected to any server  to disconnect!");
        return ;
    }
    
    Logger::info("Disconnecting to the server " + String(this->getIP()) + ":" + String(this->getPort()));

    Disconnect* disconnect = new Disconnect();
    Bytes* bytes = disconnect->toBytes();
    this->wifi->send((const uint8_t*)bytes->toArray(), bytes->getSize());

    releaseTCPConnection();
    setConnected(false);

    Logger::info("Disconnected to server " + String(this->getIP()) + ":" + String(this->getPort()));

    delete(bytes);
    delete(disconnect);
}

void MQTTClient::releaseTCPConnection(){
    Logger::info("Releasing the server connection " + String(this->getIP()) + ":" + String(this->getPort()));
    this->wifi->releaseTCP();
}