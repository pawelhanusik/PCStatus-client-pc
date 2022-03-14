#pragma once

#include "Model.h"

class Progress : public Model {
public:
    std::string title;
    int progress;
    int progress_max = 100;
    std::string message;

    const std::string getUrl() const {
        return "progress";
    }
    const std::string getCreatePostfields() const {
        return "title=" + this->title + 
            "&message=" + this->message +
            "&progress=" + std::to_string(this->progress) +
            "&progress_max=" + std::to_string(this->progress_max);
    }
    const std::string getUpdatePostfields() const {
        return "progress=" + std::to_string(this->progress);
    }
};
