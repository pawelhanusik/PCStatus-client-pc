#pragma once

#include "config.h"
#include "models.h"
#include "Logger.h"
#include "Sender.h"
#include "TokenManager.h"

class Client {
private:
    CurlSender sender;
    User user;
    TokenManager tokenManager;
public:
    Client(CurlSender sender);
    ~Client();

    bool login();
};
