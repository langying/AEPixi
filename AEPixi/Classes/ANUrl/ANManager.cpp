//
//  ANManager.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "ANManager.h"

using namespace std;

_ae_synthesize(ANManager, ANCookie*,   Cookie, cookie);
_ae_synthesize(ANManager, std::string, CookieFilename,  cookieFilename);
_ae_synthesize(ANManager, std::string, SSLVerification, sslVerification);

static ANManager* manager = nullptr;

void ANManager::releaseInstance() {
    _ae_delete(manager);
}

ANManager* ANManager::sharedInstance() {
    if (manager == nullptr) {
        manager = new ANManager();
    }
    return manager;
}


void ANManager::process(ANRequest* request, ANResponse* response) {
    long code = -1;
    bool succeed = false;
    char buffer[RESPONSE_BUFFER_SIZE] = { 0 };
    switch (request->method()) {
        case ANMethod::GET: {
            succeed = GET(request, writeData, response->getResponseData(), &code, writeHead, response->getResponseHeader(), buffer);
            break;
        }
        case ANMethod::PUT: {
            succeed = PUT(request, writeData, response->getResponseData(), &code, writeHead, response->getResponseHeader(), buffer);
            break;
        }
        case ANMethod::POST: {
            succeed = POST(request, writeData, response->getResponseData(), &code, writeHead, response->getResponseHeader(), buffer);
            break;
        }
        case ANMethod::DELETE: {
            succeed = DELETE(request, writeData, response->getResponseData(), &code, writeHead, response->getResponseHeader(), buffer);
            break;
        }
    }
    response->setResponseCode(code);
    if (succeed) {
        response->setSucceed(true);
    }
    else {
        response->setSucceed(false);
        response->setErrorBuffer(buffer);
    }
}

size_t ANManager::writeData(char* ptr, size_t size, size_t nmemb, ANData* data) {
    size_t sizes = size * nmemb;
    data->insert(data->end(), ptr, ptr + sizes);
    return sizes;
}

size_t ANManager::writeHead(char* ptr, size_t size, size_t nmemb, ANData* data) {
    size_t sizes = size * nmemb;
    data->insert(data->end(), ptr, ptr + sizes);
    return sizes;
}

bool ANManager::GET(ANRequest* request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error) {
    ANUrl url;
    return url.init(request, callback, stream, headerCallback, headerStream, error)
        && url.setOption(CURLOPT_FOLLOWLOCATION, true)
        && url.perform(code);
}

bool ANManager::PUT(ANRequest* request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error) {
    ANUrl url;
    return url.init(request, callback, stream, headerCallback, headerStream, error)
    && url.setOption(CURLOPT_CUSTOMREQUEST, "PUT")
    && url.setOption(CURLOPT_POSTFIELDS,    request->getRequestData())
    && url.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
    && url.perform(code);
}

bool ANManager::POST(ANRequest* request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error) {
    ANUrl url;
    return url.init(request, callback, stream, headerCallback, headerStream, error)
        && url.setOption(CURLOPT_POST, 1)
        && url.setOption(CURLOPT_POSTFIELDS,    request->getRequestData())
        && url.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
        && url.perform(code);
}

bool ANManager::DELETE(ANRequest* request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error) {
    ANUrl url;
    return url.init(request, callback, stream, headerCallback, headerStream, error)
        && url.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
        && url.setOption(CURLOPT_FOLLOWLOCATION, true)
        && url.perform(code);
}


ANManager::~ANManager() {
    curl_global_cleanup();
}
ANManager::ANManager() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}
ANManager::ANManager(uint32_t timeout) : ANManager() {
}

void ANManager::enableCookies(std::string& pathfile) {
    _cookieFilename = pathfile;
}

ANResponse* ANManager::sendSynchronousRequest(ANRequest* request) {
    ANResponse* response = new ANResponse();
    process(request, response);
    return response;
}




