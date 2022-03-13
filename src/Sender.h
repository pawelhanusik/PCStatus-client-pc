#pragma once

#include <curl/curl.h>
#include <string>
#include <cstring>

struct MemoryStruct {
    char *memory;
    std::string xd;
    size_t size;
};
struct Response {
    bool success;
    long code;
    MemoryStruct memoryStruct;
};

class Sender {
public:
    virtual Response sendPost(
        const std::string &url,
        const std::string &postfields,
        const std::string *token = NULL
    ) = 0;
};

class CurlSender : public Sender {
private:
    static bool wasGlobalInit;

    static size_t curlWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
public:
    CurlSender();
    ~CurlSender();

    Response sendPost(
        const std::string &url,
        const std::string &postfields,
        const std::string *token = NULL
    );
};
