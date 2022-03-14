#pragma once

#include "config.h"
#include "Logger.h"
#include "Sender.h"
#include "TokenManager.h"
#include "models/Model.h"

class Client {
private:
    CurlSender sender;
    TokenManager tokenManager;
public:
    Client(CurlSender sender);
    ~Client();

    bool create(const Model *model, bool retryOnUnauthorized = true);
    bool update(const Model *model, bool retryOnUnauthorized = true);
private:
#ifndef USE_CONFIG_TOKEN
    bool login();
#endif
};
