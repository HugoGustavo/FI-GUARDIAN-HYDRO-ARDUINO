#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Connect.hpp"

using namespace std;

Connect::Connect(const bool userName, const bool password, const bool willRetain, const unsigned char willQoS, const bool willFlag, const bool cleanSession) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_CONNECT, ControlPacket::CONTROL_PACKET_FLAG_CONNECT){
    this->variableHeader = new vector<unsigned char>;
    this->variableHeader->push_back( (unsigned char) 0 );
    this->variableHeader->push_back( (unsigned char) 4 );
    this->variableHeader->push_back( (unsigned char) 'M' );
    this->variableHeader->push_back( (unsigned char) 'Q' );
    this->variableHeader->push_back( (unsigned char) 'T' );
    this->variableHeader->push_back( (unsigned char) 'T' );
    this->variableHeader->push_back( (unsigned char) 4 );

    // Connect Flag bits  
    unsigned char flags = (unsigned char) 0;  
    flags = flags | ( (userName ? 0x01 : 0x00) << 7 ); // User Name Flag
    flags = flags | ( (password ? 0x01 : 0x00) << 6 ); // Password Flag
    flags = flags | ( (willRetain ? 0x01 : 0x00) << 5 ); // Will Retain
    flags = flags | ( (willQoS & 0x03) << 3 ); // Will QoS
    flags = flags | ( (willFlag ? 0x01 : 0x00) << 2 ); // Will Flag
    flags = flags | ( (cleanSession ? 0x01 : 0x00) << 1 ); // Clean Session


    // Condition of willFlag
    if ( ! willFlag ){
        flags = flags | ( 0x00 << 5 ); // Will Retain
        flags = flags | ( 0x00 << 3 ); // Will QoS
    }
    if ( ! userName ){
        flags = flags | ( 0x00 << 6 ); // Password Flag
    }

    this->variableHeader->push_back(flags);
    this->keepAlive = 60;
}

vector<unsigned char>* Connect::getVariableHeader(){
    return variableHeader;
}

void Connect::setVariableHeader(vector<unsigned char>* variableHeader){
    this->variableHeader = variableHeader;
}

unsigned int Connect::getKeepAlive(){
    return keepAlive;
}

void Connect::setKeepAlive(unsigned int keepAlive){
    this->keepAlive = keepAlive;
}

String Connect::getClientIdentifier(){
    return clientIdentifier;
}

void Connect::setClientIdentifier(String clientIdentifier){
    this->clientIdentifier = clientIdentifier;
}

String Connect::getWillTopic(){
    return willTopic;
}

void Connect::setWillTopic(String willTopic){
    this->willTopic = willTopic;
}

String Connect::getWillMessage(){
    return willMessage;
}

void Connect::setWillMessage(String willMessage){
    this->willMessage = willMessage;
}

String Connect::getUserName(){
    return userName;
}

void Connect::setUserName(String userName){
    this->userName = userName;
}

String Connect::getPassword(){
    return password;
}

void Connect::setPassword(String password){
    this->password = password;
}

vector<unsigned char>* Connect::toChar(){
    vector<unsigned char>* payload = nullptr;
    if ( this->clientIdentifier.length() != 0 ){
        vector<unsigned char>* clientIdentifierField = PacketUtil::buildField(this->clientIdentifier);
        payload = payload == nullptr ? clientIdentifierField : PacketUtil::concat(payload, clientIdentifierField);
    }

    unsigned char flags = this->variableHeader->at(7);
    if ( ( flags & ( 0x01 << 2 ) ) && this->willTopic.length() != 0 ){
        vector<unsigned char>* willTopicField = PacketUtil::buildField(this->willTopic);
        payload = payload == nullptr ? willTopicField : PacketUtil::concat(payload, willTopicField);
    }
    if ( ( flags & ( 0x01 << 2 ) ) && this->willMessage.length() != 0 ){
        vector<unsigned char>* willMessageField = PacketUtil::buildField(this->willMessage);
        payload = payload == nullptr ? willMessageField : PacketUtil::concat(payload, willMessageField);
    }
    if ( ( flags & ( 0x01 << 7 ) ) && this->userName.length() != 0 ){
        vector<unsigned char>* userNameField = PacketUtil::buildField(this->userName);
        payload = payload == nullptr ? userNameField : PacketUtil::concat(payload, userNameField);

        if ( ( flags & ( 0x01 << 6 ) ) && this->password.length() != 0 ){
            vector<unsigned char>* passwordField = PacketUtil::buildField(this->password);
            payload = payload == nullptr ? passwordField : PacketUtil::concat(payload, passwordField);
        }
    }

    this->setRemainingLength( (long int) ( this->variableHeader->size() + payload->size() ) );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, this->variableHeader);
    result = PacketUtil::concat(result, payload);
    return result;
}