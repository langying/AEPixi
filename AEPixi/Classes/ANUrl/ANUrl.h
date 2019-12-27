//
//  ANUrl.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__ANUrl__
#define __AEPixi__ANUrl__

#include "curl.h"
#include "AECommon.h"

class ANRequest;
class ANManager;

typedef std::vector<char> ANData;
typedef std::vector<std::string> ANHeaderList;
typedef size_t (*ANCallback)(char* ptr, size_t size, size_t nmemb, ANData* data);

class ANUrl {
public:
    _ae_property(CURL*, Curl, curl);
    _ae_property(curl_slist*, Headers, headers);
    
public:
    ANUrl();
    ~ANUrl();
    
    bool init(ANRequest* request, ANCallback callback, ANData* stream, ANCallback headerCallback, ANData* headerStream, char* error);
    bool perform(long* code);
    
    template <class T>
    bool setOption(CURLoption option, T data) {
        return CURLE_OK == curl_easy_setopt(_curl, option, data);
    }
};

#endif /* defined(__AEPixi__ANUrl__) */
