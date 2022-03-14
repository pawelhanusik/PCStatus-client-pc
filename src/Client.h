#pragma once

#include "config.h"
#include "User.h"
#include "Logger.h"
#include "Sender.h"
#include "TokenManager.h"
#include "models/Model.h"

class Client {
private:
    CurlSender sender;
    User user;
    TokenManager tokenManager;
public:
    Client(CurlSender sender);
    ~Client();

    bool create(Model *model, bool retryOnUnauthorized = true);
    bool update(Model *model, bool retryOnUnauthorized = true);
private:
#ifndef USE_CONFIG_TOKEN
    bool login();
#endif
};
