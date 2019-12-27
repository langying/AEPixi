//
//  AJTouch.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/11.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJTouch__
#define __AEPixi__AJTouch__

#include "AJCommon.h"

class AJTouch {
public:
    _aj_property(Global);
    _aj_function(getLocalPosition);
public:
    static const JSClass Clazz;
    static const JSFunctionSpec Functions[];
    static const JSPropertySpec Properties[];
    static const JSFunctionSpec StaticFunctions[];
    static const JSPropertySpec StaticProperties[];
    static bool  Constructor(JSContext* cx, uint32_t argc, jsval* vp);
    static void  Destructor(JSFreeOp* fop,  JSObject* jsthis);
    static bool  GetProperty(JSContext* cx, JSObject* jsthis, jsval id, jsval* vp);
    static bool  SetProperty(JSContext* cx, JSObject* jsthis, jsval id, jsval* vp);
};

#endif /* defined(__AEPixi__AJTouch__) */
