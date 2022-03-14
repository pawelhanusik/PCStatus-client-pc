#pragma once

#include "Model.h"

enum TaskStatus {
    CREATED,
    STARTED,
    RUNNING,
    DONE
};

class Task : public Model {
public:
    std::string title;
    TaskStatus status;
    std::string message;

    const std::string getUrl() const {
        return "task";
    }
    const std::string getCreatePostfields() const {
        return "title=" + this->title + 
            "&message=" + this->message +
            "&status=" + this->getStatusAsString();
    }
    const std::string getUpdatePostfields() const {
        return "status=" + this->getStatusAsString();
    }

private:
    const std::string getStatusAsString() const {
        switch (this->status) {
        case TaskStatus::CREATED:
            return "created";
        case TaskStatus::STARTED:
            return "started";
        case TaskStatus::RUNNING:
            return "running";
        case TaskStatus::DONE:
            return "done";
        default:
            return "";
        };
    }
};
