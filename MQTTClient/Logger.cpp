#include "Logger.hpp"

using namespace std;

void Logger::trace(String input){
    Serial.println("[TRACE] " + input);
}

void Logger::off(String input){
    Serial.println("[OFF] " + input);
}

void Logger::fatal(String input){
    Serial.println("[FATAL] " + input);
}

void Logger::error(String input){
    Serial.println("[ERROR] " + input);
}

void Logger::warn(String input){
    Serial.println("[WARN] " + input);
}

void Logger::info(String input){
    Serial.println("[INFO] " + input);
}

void Logger::debug(String input){
    Serial.println("[DEBUG] " + input);
}
