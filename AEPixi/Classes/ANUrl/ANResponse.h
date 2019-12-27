//
//  ANResponse.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/6.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__ANResponse__
#define __AEPixi__ANResponse__

#include "ANRequest.h"

class ANResponse {
public:
    ~ANResponse();
    ANResponse();
    
    std::vector<char>* getResponseData();
    std::vector<char>* getResponseHeader();
    void setResponseData(ANData* data);
    void setResponseHeader(ANData* data);
    
    void setErrorBuffer(const char* value);
    void setResponseString(const char* value, size_t n);
    
protected:
    std::vector<char> _responseData;
    std::vector<char> _responseHeader;
    
    _ae_property(bool, Succeed,      succeed);
    _ae_property(long, ResponseCode, responseCode);
    _ae_property(std::string, ErrorBuffer,    errorBuffer);
    _ae_property(std::string, ResponseString, responseString);
};

#endif /* defined(__AEPixi__ANResponse__) */
