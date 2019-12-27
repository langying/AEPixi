//
//  AJTilingSprite.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/4.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AJTilingSprite__
#define __AEPixi__AJTilingSprite__

#include "AJCommon.h"

class AJTilingSprite {
public:
    _aj_property(TileScale);
    _aj_property(TilePosition);
    _aj_property(TileScaleX);
    _aj_property(TileScaleY);
    _aj_property(TilePositionX);
    _aj_property(TilePositionY);
    
    _aj_function(fromFrame);
    _aj_function(fromImage);
    
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

#endif /* defined(__AEPixi__AJTilingSprite__) */
