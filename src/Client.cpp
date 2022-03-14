#include "Client.h"

Client::Client(CurlSender sender)
    :sender(sender)
{
#ifdef USE_CONFIG_TOKEN
    // token is already loaded from config by TokenManager
#else
    if (!this->tokenManager.hasToken()) {
        this->login();
    }

    this->user.username = Config::username;
    this->user.password = Config::password;
#endif
}

Client::~Client() {
    
}

#ifndef USE_CONFIG_TOKEN
bool Client::login() {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/user/login",
        "username=" + this->user.username + "&password=" + this->user.password
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

bool Client::create(Model *model, bool retryOnUnauthorized) {
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
            this->create(model, false);
        } else {
            Logger::errorAndExit("Error: Invalid credentials.");
        }
#endif
    } else if (response.code != 200) {
        Logger::error("Error: HTML code: " + std::to_string(response.code));
    }

    return response.success;
}

bool Client::update(Model *model, bool retryOnUnauthorized) {
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
            this->update(model, false);
        } else {
            Logger::errorAndExit("Error: Invalid credentials.");
        }
#endif
    } else if (response.code != 200) {
        Logger::error("Error: HTML code: " + std::to_string(response.code));
    }

    return response.success;
}
