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


Publish::~Publish(){
    this->dup = false;
    this->qosLevel = 0;
    this->retain = false;
    this->topicName = "";
    this->packetIdentifier = 0;
    this->payload = "";
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

Bytes* Publish::toBytes(){
    Bytes* variableHeader = new Bytes();
    if( this->topicName.length() != 0 ){
        Bytes* topicNameField = PacketUtil::build(this->topicName);
        variableHeader->concat(topicNameField);
    }

    if( this->qosLevel == Publish::PUBLISH_QOS_LEVEL_1 || this->qosLevel == Publish::PUBLISH_QOS_LEVEL_2 ){
        Bytes* packetIdentifierField = new Bytes();
        packetIdentifierField->push_back( (unsigned char) ( (0xFF00 & this->packetIdentifier) >> 8 ) );
        packetIdentifierField->push_back( (unsigned char) (0x00FF & this->packetIdentifier) );
        variableHeader->concat(packetIdentifierField);
    }

    Bytes* payload = new Bytes();
    if ( this->payload.length() != 0 )
        payload->concat(PacketUtil::build(this->payload));
        
    this->setRemainingLength( variableHeader->getSize() + payload->getSize() );

    Bytes* result = ControlPacket::toBytes();
    result->concat(variableHeader);
    result->concat(payload);
    return result;
}
