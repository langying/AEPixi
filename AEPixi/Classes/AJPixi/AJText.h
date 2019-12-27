//
//  AJText.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/16.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJText__
#define __AEPixi__AJText__

#include "AJCommon.h"

class AJText {
public:
    _aj_property(Text);
    
public:
    static const JSClass Clazz;
    static const JSFunctionSpec Functions[];
    static const JSPropertySpec Properties[];
    static const JSFunctionSpec StaticFunctions[];
    static const JSPropertySpec StaticProperties[];
    static bool  Constructor(JSContext* cx, uint32_t argc, jsval* vp);
    static void  Destructor(JSFreeOp* fop, JSObject* jsthis);
    static bool  GetProperty(JSContext* cx, JSObject* handle, jsval handId, jsval* vp);
    static bool  SetProperty(JSContext* cx, JSObject* handle, jsval handId, jsval* vp);
};

#endif /* defined(__AEPixi__AJText__) */
