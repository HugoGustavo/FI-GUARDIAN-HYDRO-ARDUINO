#include "Connect.hpp"

using namespace std;

Connect::Connect(const bool userName, const bool password, const bool willRetain, const unsigned char willQoS, const bool willFlag, const bool cleanSession) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_CONNECT, ControlPacket::CONTROL_PACKET_FLAG_CONNECT){
    this->variableHeader = new Bytes;
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

Connect::~Connect(){
    //delete(this->variableHeader);
    this->variableHeader = nullptr;
    this->keepAlive = 0;
    this->clientIdentifier = "";
    this->willTopic = "";
    this->willMessage = "";
    this->userName = "";
    this->password = "";
    
}

Bytes* Connect::getVariableHeader(){
    return variableHeader;
}

void Connect::setVariableHeader(Bytes* variableHeader){
    this->variableHeader = variableHeader;
}

unsigned int Connect::getKeepAlive(){
    return keepAlive;
}

void Connect::setKeepAlive(const unsigned int keepAlive){
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

Bytes* Connect::toBytes(){
    Bytes* payload = new Bytes();

    if ( this->clientIdentifier.length() != 0 ){
        Bytes* clientIdentifierBytes = PacketUtil::build(this->clientIdentifier);
        payload->concat(clientIdentifierBytes);
    }

    unsigned char flags = this->variableHeader->at(7);
    if ( ( flags & ( 0x01 << 2 ) ) && this->willTopic.length() != 0 ){
        Bytes* willTopicBytes = PacketUtil::build(this->willTopic);
        payload->concat(willTopicBytes);
    }
    if ( ( flags & ( 0x01 << 2 ) ) && this->willMessage.length() != 0 ){
        Bytes* willMessageBytes = PacketUtil::build(this->willMessage);
        payload->concat(willMessageBytes);
    }
    if ( ( flags & ( 0x01 << 7 ) ) && this->userName.length() != 0 ){
        Bytes* userNameBytes = PacketUtil::build(this->userName);
        payload->concat(userNameBytes);

        if ( ( flags & ( 0x01 << 6 ) ) && this->password.length() != 0 ){
            Bytes* passwordBytes = PacketUtil::build(this->password);
            payload->concat(passwordBytes);
        }
    }

    this->setRemainingLength( (long int) ( this->variableHeader->getSize() + payload->getSize() + sizeof(this->keepAlive)) );
    
    Bytes* result = ControlPacket::toBytes();
    result->concat(this->variableHeader);
    result->push_back( (unsigned char) ( (this->keepAlive & 0xFF00) >> 8) );
    result->push_back( (unsigned char) ( (this->keepAlive & 0x00FF) ) );
    result->concat(payload);
    return result;
}
