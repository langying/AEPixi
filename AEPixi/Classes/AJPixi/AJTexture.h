//
//  AJTexture.h
//  TBBusiness
//
//  Created by hanqiong on 15/2/14.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AJTexture__
#define __AEPixi__AJTexture__

#include "AJCommon.h"

class AJTexture {
public:
    _aj_property(Size);
    
    _aj_property(Width);
    _aj_property(Height);
    
    _aj_function(fromFrame);
    _aj_function(fromImage);

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

#endif /* defined(__AEPixi__AJTexture__) */
