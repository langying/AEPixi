//
//  AJBaseCallback.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/1.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJBaseCallback__
#define __AEPixi__AJBaseCallback__

#include "AJCommon.h"

class AJBaseCallback {
public:
    ~AJBaseCallback();
    AJBaseCallback(JSContext* context, JS::HandleValue& function, GLuint timeout);

    GLuint     timeout();
    JSContext* context();
    JS::Value  function();
protected:
    AJBaseCallback();

protected:
    GLuint              _timeout;
    JSContext*          _context;
    JS::Heap<JS::Value> _function;
};

#endif /* defined(__AEPixi__AJBaseCallback__) */
