//
//  ANManager.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__ANManager__
#define __AEPixi__ANManager__

#include "ANCookie.h"
#include "ANRequest.h"
#include "ANResponse.h"

class ANManager {
public:
    static const int RESPONSE_BUFFER_SIZE = 256;

public:
    static ANManager* sharedInstance();
    static void releaseInstance();
    static void process(ANRequest* request, ANResponse* response);
    static size_t writeData(char* ptr, size_t size, size_t nmemb, ANData* stream);
    static size_t writeHead(char* ptr, size_t size, size_t nmemb, ANData* stream);
    static bool GET(ANRequest*    request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error);
    static bool PUT(ANRequest*    request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error);
    static bool POST(ANRequest*   request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error);
    static bool DELETE(ANRequest* request, ANCallback callback, ANData* stream, long* code, ANCallback headerCallback, ANData* headerStream, char* error);

public:
    _ae_property(ANCookie*, Cookie, cookie);
    _ae_property(std::string, CookieFilename,  cookieFilename);
    _ae_property(std::string, SSLVerification, sslVerification);
    
public:
    ANManager(uint32_t timeout);
    void enableCookies(std::string& pathfile);
    void setSSLVerification(std::string& caPathfile);
    ANResponse* sendSynchronousRequest(ANRequest* request);

protected:
    ~ANManager();
    ANManager();
};

#endif /* defined(__AEPixi__ANManager__) */
