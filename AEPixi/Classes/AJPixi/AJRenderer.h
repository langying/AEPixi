//
//  AJRenderer.h
//  TBBusiness
//
//  Created by hanqiong on 15/3/5.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AJRenderer__
#define __AEPixi__AJRenderer__

#include "AJCommon.h"

class AJRenderer {
public:
    _aj_property(Width);
    _aj_property(Height);
public:
    _aj_function(clear);
    _aj_function(flush);
public:
    static const JSClass Clazz;
    static const JSFunctionSpec Functions[];
    static const JSPropertySpec Properties[];
    static const JSFunctionSpec StaticFunctions[];
    static const JSPropertySpec StaticProperties[];
    static bool  Constructor(JSContext* cx, uint32_t argc, jsval* vp);
    static void  Destructor(JSFreeOp* fop, JSObject* jsthis);
    static bool  GetProperty(JSContext* cx, JSObject* obj, jsval id, jsval* vp);
    static bool  SetProperty(JSContext* cx, JSObject* obj, jsval id, jsval* vp);
};

#endif /* defined(__AEPixi__AJRenderer__) */
