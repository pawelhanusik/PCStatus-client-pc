#pragma once

class Model {
public:
    int id = -1;

    virtual const std::string getUrl() const = 0;
    virtual const std::string getCreatePostfields() const = 0;
    virtual const std::string getUpdatePostfields() const {
        return "";
    }
};
