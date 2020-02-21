#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Arduino.h"
#include "Bytes.hpp"

using namespace std;

class Logger {
    public:     
        static void trace(String input);
        static void off(String input);
        static void fatal(String input);
        static void error(String input);
        static void warn(String input);
        static void info(String input);
        static void debug(String input);
};

#endif