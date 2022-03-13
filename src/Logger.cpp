#include "Logger.h"

void Logger::log(const std::string message) {
    printf("%s\n", message.c_str());
}
void Logger::error(const std::string message) {
    fprintf(stderr, "%s\n", message.c_str());
}
void Logger::errorAndExit(const std::string message, const int errorcode) {
    Logger::error(message);
    exit(errorcode);
}
