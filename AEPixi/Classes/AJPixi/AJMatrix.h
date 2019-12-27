//
//  AJMatrix.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJMatrix__
#define __AEPixi__AJMatrix__

#include "AJCommon.h"

class AJMatrix {
public:
    _aj_property(A);
    _aj_property(B);
    _aj_property(C);
    _aj_property(D);
    _aj_property(Tx);
    _aj_property(Ty);
    
public:
    _aj_function(invert);
    _aj_function(identity);
    _aj_function(scale);
    _aj_function(rotate);
    _aj_function(translate);
    _aj_function(append);
    _aj_function(prepend);
    _aj_function(toArray);
    _aj_function(fromArray);
    _aj_function(copy);
    _aj_function(clone);
    _aj_function(apply);
    _aj_function(applyInverse);
    
    static const JSClass Clazz;
    static const JSFunctionSpec Functions[];
    static const JSPropertySpec Properties[];
    static const JSFunctionSpec StaticFunctions[];
    static const JSPropertySpec StaticProperties[];
    static bool  Constructor(JSContext* cx, uint32_t argc, jsval* vp);
    static void  Destructor(JSFreeOp* fop, JSObject* jsthis);
    static bool  GetProperty(JSContext* cx, JSObject* obj, jsval val, jsval* vp);
    static bool  SetProperty(JSContext* cx, JSObject* obj, jsval val, jsval* vp);
};

#endif /* defined(__AEPixi__AJMatrix__) */
