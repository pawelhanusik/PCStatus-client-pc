#include "Client.h"

Client::Client(CurlSender sender)
    :sender(sender)
{
#ifndef USE_CONFIG_TOKEN
    if (!this->tokenManager.hasToken()) {
        this->login();
    }
#endif
}

Client::~Client() {
    
}

#ifndef USE_CONFIG_TOKEN
bool Client::login() {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/user/login",
        "username=" + Config::username + "&password=" + Config::password + "&token_name=" + Config::device_name
    );

    if (response.code == 200) {
        this->tokenManager.setToken(
            std::string(response.message)
        );
    } else {
        Logger::errorAndExit("Error: Invalid credentials.");
    }
    
    return response.success;
}
#endif

Response Client::create(const Model *model, bool retryOnUnauthorized) {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/" + model->getUrl(),
        model->getCreatePostfields(),
        this->tokenManager.getToken()
    );

    if (response.code == 401) {
#ifdef USE_CONFIG_TOKEN
        Logger::errorAndExit("Error: Invalid credentials.");
#else
        if (retryOnUnauthorized) {
            this->login();
            return this->create(model, false);
        } else {
            Logger::errorAndExit("Error: Invalid credentials.");
        }
#endif
    } else if (response.code != 200) {
        Logger::error("Error: HTML code: " + std::to_string(response.code));
    }

    return response;
}

bool Client::update(const Model *model, bool retryOnUnauthorized) {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/" + model->getUrl() + "/" + std::to_string(model->id),
        model->getUpdatePostfields(),
        this->tokenManager.getToken()
    );

    if (response.code == 401) {
#ifdef USE_CONFIG_TOKEN
        Logger::errorAndExit("Error: Invalid credentials.");
#else
        if (retryOnUnauthorized) {
            this->login();
            return this->update(model, false);
        } else {
            Logger::errorAndExit("Error: Invalid credentials.");
        }
#endif
    } else if (response.code != 200) {
        Logger::error("Error: HTML code: " + std::to_string(response.code));
    }

    return response.success;
}
