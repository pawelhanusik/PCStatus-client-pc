#include "Sender.h"

// https://curl.se/libcurl/c/http-post.html
bool CurlSender::wasGlobalInit = false;
CurlSender::CurlSender() {
    if (!CurlSender::wasGlobalInit) {
        curl_global_init(CURL_GLOBAL_ALL);
        CurlSender::wasGlobalInit = true;
    }
    
}
CurlSender::~CurlSender() {
    if (CurlSender::wasGlobalInit) {
        curl_global_cleanup();
        CurlSender::wasGlobalInit = false;
    }
}
size_t CurlSender::curlWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Response *response = (struct Response *)userp;
    response->message = std::string((char*)contents);
    return realsize;
}
const Response CurlSender::sendPost(
    const std::string &url,
    const std::string &postfields,
    const std::string *token
) {
    Response response;
    CURL *curl = curl_easy_init();
    
    if(!curl) {
        response.success = false;
        return response;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());

    if (token != NULL) {
        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, (*token).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
    }
    
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlSender::curlWriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

    CURLcode res = curl_easy_perform(curl);
    
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response.code);

    if(res != CURLE_OK) {
        fprintf(
            stderr,
            "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res)
        );
    }

    curl_easy_cleanup(curl);

    response.success = (res == CURLE_OK);
    return response;
}
