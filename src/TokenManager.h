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
    void setToken(const std::string& token);
    const std::string* getToken() const;
    bool hasToken() const;
private:
#ifndef USE_CONFIG_TOKEN
    void loadToken();
    void saveToken() const;
#endif
};
