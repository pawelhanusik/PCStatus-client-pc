#include "Sender.h"

// https://curl.se/libcurl/c/http-post.html
bool CurlSender::wasGlobalInit = false;
CurlSender::CurlSender() {
    if (!CurlSender::wasGlobalInit) {
        curl_global_init(CURL_GLOBAL_ALL);
        CurlSender::wasGlobalInit = true;
    }
    this->curl = curl_easy_init();
}
CurlSender::~CurlSender() {
    if (CurlSender::wasGlobalInit) {
        curl_global_cleanup();
        CurlSender::wasGlobalInit = false;
    }
}
size_t CurlSender::curlWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    std::memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
Response CurlSender::sendPost(const std::string &url, const std::string &postfields) {
    Response response;
    
    if(!this->curl) {
        response.success = false;
        return response;
    }

    response.memoryStruct.memory = (char*)malloc(1);
    response.memoryStruct.size = 0;

    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, postfields.c_str());
    
    curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, CurlSender::curlWriteMemoryCallback);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void *)&response.memoryStruct);

    CURLcode res = curl_easy_perform(this->curl);
    
    curl_easy_getinfo (this->curl, CURLINFO_RESPONSE_CODE, &response.code);

    if(res != CURLE_OK) {
        fprintf(
            stderr,
            "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res)
        );
    }

    curl_easy_cleanup(this->curl);
    
    response.success = (res == CURLE_OK);
    return response;
}
