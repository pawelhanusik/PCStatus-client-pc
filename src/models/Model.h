#pragma once

class Model {
public:
    int id = -1;

    virtual std::string getUrl() = 0;
    virtual std::string getCreatePostfields() = 0;
    virtual std::string getUpdatePostfields() {
        return "";
    }
};
