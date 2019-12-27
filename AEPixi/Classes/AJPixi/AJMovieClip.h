//
//  AJMovieClip.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/3.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJMovieClip__
#define __AEPixi__AJMovieClip__

#include "AJCommon.h"

class AJMovieClip {
public:
    _aj_property(Loop);
    _aj_property(Playing);
    _aj_property(CurrentTime);
    _aj_property(AnimationSpeed);

public:
    _aj_function(totalFrames);
    _aj_function(currentFrame);
    
    _aj_function(play);
    _aj_function(stop);
    _aj_function(gotoAndStop);
    _aj_function(gotoAndPlay);
    _aj_function(fromFrames);
    _aj_function(fromImages);
    
public:
    static const JSClass Clazz;
    static const JSFunctionSpec Functions[];
    static const JSPropertySpec Properties[];
    static const JSFunctionSpec StaticFunctions[];
    static const JSPropertySpec StaticProperties[];
    static bool  Constructor(JSContext* cx, uint32_t argc, jsval* vp);
    static void  Destructor(JSFreeOp* fop,  JSObject* jsthis);
    static bool  GetProperty(JSContext* cx, JSObject* obj, jsval id, jsval* vp);
    static bool  SetProperty(JSContext* cx, JSObject* obj, jsval id, jsval* vp);
    
protected:
    
};

#endif /* defined(__AEPixi__AJMovieClip__) */
