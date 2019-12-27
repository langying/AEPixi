//
//  AJBaseCallback.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/1.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJBaseCallback.h"

using namespace JS;

AJBaseCallback::~AJBaseCallback() {
    RemoveValueRoot(_context, &_function);
}

AJBaseCallback::AJBaseCallback() {
}

AJBaseCallback::AJBaseCallback(JSContext* context, HandleValue& function, GLuint timeout): AJBaseCallback() {
    _context  = context;
    _function = function;
    _timeout  = timeout;
    AddValueRoot(_context, &_function);
}

GLuint AJBaseCallback::timeout() {
    return _timeout;
}
JSContext* AJBaseCallback::context() {
    return _context;
}
Value AJBaseCallback::AJBaseCallback::function() {
    return _function.get();
}

