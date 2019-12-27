//
//  AJNode.h
//  TBBusiness
//
//  Created by hanqiong on 15/1/28.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AJNode__
#define __AEPixi__AJNode__

#include "AJCommon.h"

class AJNode {
public:
    _aj_property(Uuid);
    _aj_property(State);
    _aj_property(BackgroundColor);
    
    _aj_property(Alpha);
    _aj_property(WorldAlpha);
    _aj_property(Resolution);
    _aj_property(Rotation);
    
    _aj_property(Visible);
    _aj_property(Interactive);
    _aj_property(CacheAsBitmap);
    
    _aj_property(Scale);
    _aj_property(Pivot);
    _aj_property(Anchor);
    
    _aj_property(Frame);
    
    _aj_property(Transform);
    _aj_property(WorldTransform);
    
    _aj_property(X);
    _aj_property(Y);
    _aj_property(Width);
    _aj_property(Height);
    _aj_property(Top);
    _aj_property(Left);
    _aj_property(Right);
    _aj_property(Bottom);
    _aj_property(ScaleX);
    _aj_property(ScaleY);
    _aj_property(Center);
    _aj_property(Position);
    
public:
    _aj_function(applyRender);
    _aj_function(applyTransform);
    _aj_function(pointInside);
    _aj_function(toBounds);
    _aj_function(toLocal);
    _aj_function(toGlobal);
    
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

#endif /* defined(__AEPixi__AJNode__) */
