#pragma once

#include "Model.h"

class Notification : public Model {
public:
    int id;
    std::string title;
    std::string message;
    
    std::string getUrl() {
        return "notification";
    }
    std::string getCreatePostfields() {
        return "title=" + this->title + 
            "&message=" + this->message;
    }
};
