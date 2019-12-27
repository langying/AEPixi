//
//  ANRequest.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/6.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "ANRequest.h"

_ae_synthesize(ANRequest, uint,  Timeout,     timeout);
_ae_synthesize(ANRequest, uint,  ConnTimeout, connTimeout);
_ae_synthesize(ANRequest, void*,        UserData, userData);
_ae_synthesize(ANRequest, ANMethod,     Method,   method);
_ae_synthesize(ANRequest, std::string,  Tag,      tag);
_ae_synthesize(ANRequest, std::string,  Url,      url);
_ae_synthesize(ANRequest, ANHeaderList, Headers, headers);


ANRequest* ANRequest::create(std::string& url, uint timeout, uint connTimeout) {
    ANRequest* request = new ANRequest();
    request->_url         = url;
    request->_timeout     = timeout;
    request->_connTimeout = connTimeout;
    return request;
}

ANRequest::~ANRequest() {
};

ANRequest::ANRequest() {
    _timeout     = 5000;
    _connTimeout = 3000;
    _url.clear();
    _method = ANMethod::GET;
};

void ANRequest::setRequestData(const char* buffer, size_t len) {
    _requestData.assign(buffer, buffer + len);
};

char* ANRequest::getRequestData() {
    return _requestData.size() ? &(_requestData.front()) : nullptr;
}

ssize_t ANRequest::getRequestDataSize() {
    return _requestData.size();
}

