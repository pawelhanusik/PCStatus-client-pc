#include "TokenManager.h"

TokenManager::TokenManager() {
#ifdef USE_CONFIG_TOKEN
    this->token = Config::token;
#else
    this->loadToken();
#endif
}
TokenManager::~TokenManager() {
#ifndef USE_CONFIG_TOKEN
    this->saveToken();
#endif
}
void TokenManager::setToken(std::string token) {
    this->token = token;
}
std::string TokenManager::getToken() {
    return this->token;
}

bool TokenManager::hasToken() {
    return (this->token.length() > 0);
}

#ifndef USE_CONFIG_TOKEN
void TokenManager::loadToken() {
    std::ifstream file_in(Config::tokenStoragePath);
    file_in >> this->token;
    file_in.close();
}
void TokenManager::saveToken() {
    std::ofstream file_out(Config::tokenStoragePath);
    file_out << this->token;
    file_out.close();
}
#endif
