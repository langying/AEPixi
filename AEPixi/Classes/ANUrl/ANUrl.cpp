//
//  ANUrl.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "ANUrl.h"
#include "ANManager.h"
#include "ANRequest.h"

using namespace std;

_ae_synthesize(ANUrl, CURL*, Curl, curl);
_ae_synthesize(ANUrl, curl_slist*, Headers, headers);


ANUrl::ANUrl() {
    _curl = curl_easy_init();
    _headers = nullptr;
}

ANUrl::~ANUrl() {
    if (_curl)    { curl_easy_cleanup(_curl); }
    if (_headers) { curl_slist_free_all(_headers); }
}

bool ANUrl::init(ANRequest* request, ANCallback callback, ANData* stream, ANCallback headerCallback, ANData* headerStream, char* error) {
    bool suc = setOption(CURLOPT_ERRORBUFFER, error)
            && setOption(CURLOPT_TIMEOUT, request->timeout())
            && setOption(CURLOPT_CONNECTTIMEOUT, request->connTimeout())
            && setOption(CURLOPT_SSL_VERIFYPEER, 0L)
            && setOption(CURLOPT_SSL_VERIFYHOST, 0L)
            && setOption(CURLOPT_NOSIGNAL, 1L)
            && setOption(CURLOPT_ACCEPT_ENCODING, "");
    if (!suc) {
        return false;
    }
    
    vector<string> headers = request->headers();
    if (!headers.empty()) {
        for (vector<string>::iterator it = headers.begin(); it != headers.end(); ++it) {
            _headers = curl_slist_append(_headers, it->c_str());
        }
        setOption(CURLOPT_HTTPHEADER, _headers);
    }
    std::string cookieFilename = ANManager::sharedInstance()->getCookieFilename();
    if (!cookieFilename.empty()) {
        if (!setOption(CURLOPT_COOKIEFILE, cookieFilename.c_str())) {
            return false;
        }
        if (!setOption(CURLOPT_COOKIEJAR, cookieFilename.c_str())) {
            return false;
        }
    }
    return setOption(CURLOPT_URL, request->url().c_str())
        && setOption(CURLOPT_WRITEFUNCTION, callback)
        && setOption(CURLOPT_WRITEDATA, stream)
        && setOption(CURLOPT_HEADERDATA, headerStream)
        && setOption(CURLOPT_HEADERFUNCTION, headerCallback);
}

bool ANUrl::perform(long* code) {
    if (CURLE_OK != curl_easy_perform(_curl)) {
        return false;
    }
    CURLcode suc = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, code);
    if (suc != CURLE_OK || !(*code >= 200 && *code < 300)) {
        fprintf(stderr, "Curl curl_easy_getinfo failed: %s", curl_easy_strerror(suc));
        return false;
    }
    return true;
}
