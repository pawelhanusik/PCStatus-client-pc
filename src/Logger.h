#pragma once

#include <cstdlib>
#include <string>

class Logger {
public:
    static void log(const std::string message);
    static void error(const std::string message);
    static void errorAndExit(const std::string message, const int errorcode = 1);
};
