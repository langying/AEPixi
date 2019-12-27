//
//  AJGraphics.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJGraphics__
#define __AEPixi__AJGraphics__

#include "AJCommon.h"

class AJGraphics {
public:
    _aj_property(Tint);
    _aj_property(IsMask);
    _aj_property(BlendMode);
    _aj_property(Filling);
    _aj_property(Fillable);
    _aj_property(FillAlpha);
    _aj_property(FillColor);
    _aj_property(LineAlpha);
    _aj_property(LineColor);
    _aj_property(LineWidth);
    _aj_property(BoundsPadding);
    
public:
    _aj_function(clone);
    _aj_function(lineStyle);
    
    _aj_function(moveTo);
    _aj_function(lineTo);
    _aj_function(quadraticCurveTo);
    _aj_function(bezierCurveTo);
    _aj_function(arcTo);
    _aj_function(arc);
    
    _aj_function(beginFill);
    _aj_function(endFill);
    _aj_function(drawRect);
    _aj_function(drawRoundedRect);
    _aj_function(drawCircle);
    _aj_function(drawEllipse);
    _aj_function(drawPolygon);
    
    _aj_function(clear);
    
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
    
protected:
};

#endif /* defined(__AEPixi__AJGraphics__) */
