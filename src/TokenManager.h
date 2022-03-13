#pragma once

#include <string>
#include <fstream>

#include "config.h"

class TokenManager {
private:
    std::string token;
public:
    TokenManager();
    ~TokenManager();
    void setToken(std::string token);
    std::string getToken();
    bool hasToken();
private:
#ifndef USE_CONFIG_TOKEN
    void loadToken();
    void saveToken();
#endif
};
