//
//  AJRope.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/10.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJRope__
#define __AEPixi__AJRope__

#include "AJCommon.h"

class AJRope {
public:
    _aj_function(applyTransform);
    
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
    
protected:
};

#endif /* defined(__AEPixi__AJRope__) */
