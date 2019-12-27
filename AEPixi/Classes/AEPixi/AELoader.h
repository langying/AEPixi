//
//  AELoader.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/2.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AELoader__
#define __AEPixi__AELoader__

#include "AECommon.h"

class AELoader {
public:
    ~AELoader();
    AELoader();
    
    GLvoid operator()(int a);
    GLvoid reset();
    GLvoid add(std::string& url);
    GLvoid load(std::string& callback);
    GLvoid handleBaseURL(std::string& url);
    
protected:
    std::string _baseURL;
    std::vector<std::string> _resources;
};

#endif /* defined(__AEPixi__AELoader__) */
