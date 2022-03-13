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
    int id;
    std::string title;
    TaskStatus status;
    std::string message;

    std::string getUrl() {
        return "task";
    }
    std::string getCreatePostfields() {
        return "title=" + this->title + 
            "&message=" + this->message +
            "&status=" + this->getStatusAsString();
    }
    std::string getUpdatePostfields() {
        return "status=" + this->getStatusAsString();
    }

private:
    std::string getStatusAsString() {
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
