//
//  ANRequest.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/6.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__ANRequest__
#define __AEPixi__ANRequest__

#include "ANUrl.h"

enum class ANMethod: uint { GET, POST, PUT, DELETE };

class ANRequest {
public:
    static ANRequest* create(std::string& url, uint timeout, uint connTimeout);
    
public:
    ~ANRequest();
    ANRequest();
    void  setRequestData(const char* buffer, size_t len);
    char* getRequestData();
    ssize_t getRequestDataSize();
    
public:
    std::vector<char> _requestData;
    
    _ae_property(uint,  Timeout,     timeout);
    _ae_property(uint,  ConnTimeout, connTimeout);
    _ae_property(void*,        UserData, userData);
    _ae_property(ANMethod,     Method,   method);
    _ae_property(std::string,  Tag,      tag);
    _ae_property(std::string,  Url,      url);
    _ae_property(ANHeaderList, Headers, headers);
};

#endif /* defined(__AEPixi__ANRequest__) */
