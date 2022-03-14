#pragma once

#include "Model.h"

class Notification : public Model {
public:
    int id;
    std::string title;
    std::string message;
    
    const std::string getUrl() const {
        return "notification";
    }
    const std::string getCreatePostfields() const {
        return "title=" + this->title + 
            "&message=" + this->message;
    }
};
