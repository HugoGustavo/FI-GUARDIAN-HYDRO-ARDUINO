#ifndef PACKETUTIL_HPP
#define PACKETUTIL_HPP

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

#include "Arduino.h"

using namespace std;

class PacketUtil {
    public:     
        static vector<unsigned char>* buildField(String field);
        static vector<unsigned char>* concat(vector<unsigned char>* destiny, vector<unsigned char>* source);
        static unsigned int length(vector<unsigned char>* destiny);
        static bool equals(vector<unsigned char>* destiny, vector<unsigned char>* source);
        static void print(unsigned char field);
        static void print(vector<unsigned char>* field);
        static void println(vector<unsigned char>* field);
};

#endif