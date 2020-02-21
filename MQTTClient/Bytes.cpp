#include "Bytes.hpp"

Bytes::Node::Node(){
    this->value = (unsigned char) 0;
    this->previous = this->next = nullptr;
}

Bytes::Node::~Node(){
    this->value = (unsigned char) 0;
    this->previous = this->next = nullptr;
}

Bytes::Node::Node(unsigned char value, Bytes::Node* previous, Bytes::Node* next){
    this->value = value;
    this->previous = previous;
    this->next = next;
}

unsigned char Bytes::Node::getValue(){ 
    return this->value;
}

void Bytes::Node::setValue(unsigned char value){
    this->value = value;
}

Bytes::Node* Bytes::Node::getPrevious(){
    return this->previous;
}

void Bytes::Node::setPrevious(Bytes::Node* previous){
    this->previous = previous;
}

Bytes::Node* Bytes::Node::getNext(){
    return this->next;
}

void Bytes::Node::setNext(Bytes::Node* next){
    this->next = next;
}

Bytes::Bytes(){
    this->front = this->back = nullptr;
    this->size = 0;
}

Bytes::~Bytes(){
    Bytes::Node* current = this->front;
    while( current != nullptr ){
        Bytes::Node* next = current->getNext();
        delete(current);
        current = next;
    }
    
    this->front = this->back = nullptr;
    this->size = 0;
}

unsigned char Bytes::at(const unsigned int index){
    if ( index >= this->size )
        return (unsigned char) 0;
    
    int position = index;
    Bytes::Node* current = this->front;
    while( position != 0 && current != nullptr) {
        current = current->getNext();
        position--;
    }

    return current == nullptr ? (unsigned char) 0 : current->getValue();
}

unsigned char Bytes::atFront(){
    return this->front == nullptr ? (unsigned char) 0 : this->front->getValue();
}

unsigned char Bytes::atBack(){
    return this->back == nullptr ? (unsigned char) 0 : this->back->getValue();
}

void Bytes::push_back(unsigned char value){
    Bytes::Node* node = new Node(value, this->back, nullptr);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->back->setNext(node);
        this->back = node;
    }

    this->size++;
}

void Bytes::pop_back(){
    if ( this->back == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Bytes::Node* temp = this->back->getPrevious();
        this->back->setPrevious(nullptr);
        this->back->setNext(nullptr);
        temp->setNext(nullptr);
        delete this->back;
        this->back = temp;
    }

    this->size--;
}

void Bytes::push_front(unsigned char value){
    Bytes::Node* node = new Bytes::Node(value, nullptr, this->front);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->front->setPrevious(node);
        this->front = node;
    }

    this->size++;
}

void Bytes::pop_front(){
    if ( this->front == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Bytes::Node* temp = this->front->getNext();
        this->front->setPrevious(nullptr);
        this->front->setNext(nullptr);
        temp->setPrevious(nullptr);
        delete this->front;
        this->front = temp;
    }

    this->size--;
}

unsigned int Bytes::getSize(){
    return this->size;
}

void Bytes::concat(Bytes* other){
    if ( other == nullptr ) return;

    for(unsigned int i = 0; i < other->getSize(); i++){
        this->push_back( other->at(i) );
    }
}

unsigned char* Bytes::toArray(){
    if( this->size == 0 ) return nullptr;
    unsigned char* result = new unsigned char[this->size];
    for(unsigned int i = 0; i < this->getSize(); i++) result[i] = this->at(i);
    return result;
}

bool Bytes::equals(Bytes* that){
    if ( that == nullptr || that->getSize() != this->getSize() ) return false;

    for(unsigned int i = 0; i < this->getSize(); i++)
        if ( this->at(i) != that->at(i) ) return false;
    
    return true;
}