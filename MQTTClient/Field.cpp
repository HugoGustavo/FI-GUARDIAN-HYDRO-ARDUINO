#include "Field.hpp"

template<class Type> Field::Node::Node(){
    this->value = nullptr;
    this->previous = this->next = nullptr;
}

template<class Type> Field::Node::Node(Type* value, Field::Node* previous, Field::Node* next){
    this->value = value;
    this->previous = previous;
    this->next = next;
}

template<class Type> Type* Field::Node::getValue(){ 
    return this->value;
}

template<class Type> void Field::Node::setValue(Type* value){
    this->value = value;
}

template<class Type> Node* Field::Node::getPrevious(){
    return this->previous;
}

template<class Type> void Field::Node::setPrevious(Node* previous){
    this->previous = previous;
}

template<class Type> Node* Field::Node::getNext(){
    return this->next;
}

template<class Type> void Field::Node::setNext(Node* next){
    this->next = next;
}

template<class Type> Field::Field(){
    this->front = this->back = nullptr;
    this->size = 0;
}

template<class Type> Type* Field::at(unsigned int index){
    if ( index < 0 || index >= this->size) return nullptr;
    
    Field::Node* current = this->front;
    while( index != 0 && current != nullptr) {
        current = current->getNext();
        index--;
    }

    return current == nullptr ? nullptr : current->getValue();
}

template<class Type> Type* Field::front(){
    return this->front == nullptr ? nullptr : this->front->getValue();
}

template<class Type> Type* Field:: back(){
    return this->back == nullptr ? nullptr : this->back->getValue();
}

template<class Type> void  Field::push_back(const Type& value){
    Field::Node* node = new Node(value, this->back, nullptr);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->back->setNext(node);
        this->back = node;
    }

    this->size++;
}

template<class Type> void Field::pop_back(){
    if ( this->back == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Node* temp = this->back->getPrevious();
        this->back->setPrevious(nullptr);
        this->back->setNext(nullptr);
        temp->setNext(nullptr);
        delete this->back;
        this->back = temp;
    }

    this->size--;
}

template<class Type> void Field::push_front(const Type& value){
    Field::Node* node = new Node(value, nullptr, this->front);

    if ( this->front == nullptr ){
        this->front = this->back = node;
    } else{
        this->front->setPrevious(node);
        this->front = node;
    }

    this->size++;
}

template<class Type> void  Field::pop_front(){
    if ( this->front == nullptr ) return;

    if ( this->front == this->back ){
        delete this->front;
        this->front = this->back = nullptr;
    } else {
        Node* temp = this->front->getNext();
        this->front->setPrevious(nullptr);
        this->front->setNext(nullptr);
        temp->setPrevious(nullptr);
        delete this->front;
        this->front = temp;
    }

    this->size--;
}

template<class Type> unsigned int Field::getSize(){
    return this->size;
}

#endif