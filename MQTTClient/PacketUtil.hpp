#ifndef PACKETUTIL_HPP
#define PACKETUTIL_HPP

#include "Arduino.h"
#include "Bytes.hpp"

using namespace std;

class PacketUtil {
    public:     
        static Bytes* build(String input);
        static Bytes* build(uint8_t* buffer, uint32_t size);
        static void println(Bytes* input);
        static void print(Bytes* input);
        static void print(const unsigned char input);
        static String toString(Bytes* input);
};

#endif