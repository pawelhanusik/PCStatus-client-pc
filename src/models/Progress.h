#pragma once

#include "Model.h"

class Progress : public Model {
public:
    int id;
    std::string title;
    int progress;
    int progress_max = 100;
    std::string message;

    std::string getUrl() {
        return "progress";
    }
    std::string getCreatePostfields() {
        return "title=" + this->title + 
            "&message=" + this->message +
            "&progress=" + std::to_string(this->progress) +
            "&progress_max=" + std::to_string(this->progress_max);
    }
    std::string getUpdatePostfields() {
        return "progress=" + std::to_string(this->progress);
    }
};
