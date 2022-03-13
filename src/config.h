#pragma once

#include <string>

namespace Config {

    /*
    * Whole server url, including protocol
    * eg. http://localhost:8000/
    */
    static std::string serverAddress = "http://localhost:8000/";

    /*
    * Please specify Authentication method. There are 2 possibilities:
    * 1) useToken (leave "#define USE_CONFIG_TOKEN" uncommented)
    *    authenticate by sending preset token
    * 2) useCredentials (comment "#define USE_CONFIG_TOKEN" line)
    *    authenticate by username & password
    *    and store the token in specified file
    */

// #define USE_CONFIG_TOKEN

#ifdef USE_CONFIG_TOKEN
    static std::string token = "";
#else
    static std::string username = "user";
    static std::string password = "password";
    static std::string tokenStoragePath = "creds.conf";
#endif
}