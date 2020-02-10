#ifndef FIELD_HPP
#define FIELD_HPP

using namespace std;

template <class Type>
class Field {
    private:
        Node* front, back;
        unsigned int size;

    public:
        Field();
        
        Type* at(unsigned int index);

        Type* front();

        Type* back();

        void push_back(const Type* value);

        void pop_back();

        void push_front(const Type* value);

        void pop_front();

        unsigned int getSize();

        class Node {
            Type* value;
            Node* previous, next;

            public:
                Node();

                Node(Type* value, Node* previous, Node* next);

                Type* getValue();
                
                void setValue(Type* value);

                Node* getPrevious();

                void setPrevious(Node* previous);

                Node* getNext();

                void setNext(Node* next);
        };

};

#endif