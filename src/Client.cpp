#include "Client.h"

Client::Client(CurlSender sender)
    :sender(sender)
{
#ifdef USE_CONFIG_TOKEN
    // token is already loaded from config by TokenManager
    this->user.isLoggedIn = true;
#else
    if (!this->tokenManager.hasToken()) {
        this->user.username = Config::username;
        this->user.password = Config::password;
        
        this->login();
    }
#endif
}

Client::~Client() {
    
}

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

bool Client::create(Model *model) {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/" + model->getUrl(),
        model->getCreatePostfields(),
        this->tokenManager.getToken()
    );
    return response.success;
}

bool Client::update(Model *model) {
    Response response = this->sender.sendPost(
        Config::serverAddress + "api/" + model->getUrl() + "/" + std::to_string(model->id),
        model->getUpdatePostfields(),
        this->tokenManager.getToken()
    );
    return response.success;
}
