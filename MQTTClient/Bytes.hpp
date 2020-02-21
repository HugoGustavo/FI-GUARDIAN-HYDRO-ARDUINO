#ifndef BYTES_HPP
#define BYTES_HPP

using namespace std;

class Bytes {
    private:
        class Node {
            private:
                unsigned char value;
                Node* previous;
                Node* next;

            public:
                Node();

                ~Node();

                Node(unsigned char value, Node* previous, Node* next);

                unsigned char getValue();
                
                void setValue(unsigned char value);

                Node* getPrevious();

                void setPrevious(Node* previous);

                Node* getNext();

                void setNext(Node* next);
        };

        Node* front;
        Node* back;
        unsigned int size;

    public:
        Bytes();

        ~Bytes();

        unsigned char at(const unsigned int index);
        
        unsigned char atFront();
        
        unsigned char atBack();
        
        void push_back(unsigned char value);
        
        void pop_back();
        
        void push_front(unsigned char value);
        
        void pop_front();
        
        unsigned int getSize();
        
        void concat(Bytes* other);
        
        unsigned char* toArray();
        
        bool equals(Bytes* other);
        
};

#endif