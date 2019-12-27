//
//  ANResponse.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/6.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "ANResponse.h"

_ae_synthesize(ANResponse, bool, Succeed,      succeed);
_ae_synthesize(ANResponse, long, ResponseCode, responseCode);
_ae_synthesize(ANResponse, std::string, ErrorBuffer,    errorBuffer);
_ae_synthesize(ANResponse, std::string, ResponseString, responseString);

ANResponse::~ANResponse() {
}

ANResponse::ANResponse() {
    _succeed = false;
}

std::vector<char>* ANResponse::getResponseData() {
    return &_responseData;
}

std::vector<char>* ANResponse::getResponseHeader() {
    return &_responseHeader;
}

void ANResponse::setErrorBuffer(const char* value) {
    _errorBuffer.clear();
    _errorBuffer.assign(value);
};

void ANResponse::setResponseString(const char* value, size_t n) {
    _responseString.clear();
    _responseString.assign(value, n);
}

void ANResponse::setResponseData(ANData* data) {
    _responseData = *data;
}

void ANResponse::setResponseHeader(ANData* data) {
    _responseHeader = *data;
}