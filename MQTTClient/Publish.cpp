#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Publish.hpp" 

using namespace std;

Publish::Publish(const bool dup, const unsigned char qosLevel, const bool retain) : ControlPacket(ControlPacket::CONTROL_PACKET_TYPE_PUBLISH, ControlPacket::CONTROL_PACKET_FLAG_PUBLISH){
    this->dup = dup;
    this->qosLevel = qosLevel;
    this->retain = retain;

    this->dup = this->qosLevel == 0x00 ? false : true;

    this->flags = 0x00;
    this->flags = dup ? this->flags | (0x01 << 3) : this->flags;
    this->flags = this->flags | ( (this->qosLevel & 0x03) << 1 );
    this->flags = retain ? this->flags | 0x01 : this->flags;    
}

bool Publish::isDup(){
    return dup;
}

void Publish::setDup(const bool dup){
    this->dup = dup;
}

unsigned char Publish::getQoSLevel(){
    return qosLevel;
}

void Publish::setQoSLevel(const unsigned char qosLevel){
    this->qosLevel = qosLevel;
}

bool Publish::isRetain(){
    return retain;
}

void Publish::setRetain(const bool retain){
    this->retain = retain;
}

String Publish::getTopicName(){
    return topicName;
}

void Publish::setTopicName(String topicName){
    this->topicName = topicName;
}

unsigned int Publish::getPacketIdentifier(){
    return packetIdentifier;
}

void Publish::setPacketIdentifier(const unsigned int packetIdentifier){
    this->packetIdentifier = packetIdentifier;
}

String Publish::getPayload(){
    return payload;
}

void Publish::setPayload(String payload){
    this->payload = payload;
}

vector<unsigned char>* Publish::toChar(){
    vector<unsigned char>* variableHeader = nullptr;
    
    if( this->topicName.length() != 0){
        vector<unsigned char>* topicNameField = PacketUtil::buildField(this->topicName);
        variableHeader = variableHeader == nullptr ? topicNameField : PacketUtil::concat(variableHeader, topicNameField);
    }

    if( this->qosLevel == Publish::PUBLISH_QOS_LEVEL_1 || this->qosLevel == Publish::PUBLISH_QOS_LEVEL_2 ){
        vector<unsigned char>* packetIdentifierField = new vector<unsigned char>();
        packetIdentifierField->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
        packetIdentifierField->push_back( (unsigned char) (0x00FF & this->packetIdentifier) );
        variableHeader = variableHeader == nullptr ? packetIdentifierField : PacketUtil::concat(variableHeader, packetIdentifierField);
    }
        

    vector<unsigned char>* payload = nullptr;
    if ( this->payload.length() != 0)
        payload = PacketUtil::buildField(this->payload);
    
    this->setRemainingLength( variableHeader->size() + payload->size() );

    vector<unsigned char>* result = ControlPacket::toChar();
    result = PacketUtil::concat(result, variableHeader);
    result = PacketUtil::concat(result, payload);
    return result;
}