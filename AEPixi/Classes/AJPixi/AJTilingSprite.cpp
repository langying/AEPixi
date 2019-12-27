//
//  AJTilingSprite.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/4.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AETilingSprite.h"
#include "AJTilingSprite.h"

using namespace JS;
using namespace std;

_propertyPoint(AJTilingSprite,  AETilingSprite, TileScale);
_propertyPoint(AJTilingSprite,  AETilingSprite, TilePosition);
_propertyDouble(AJTilingSprite, AETilingSprite, TileScaleX);
_propertyDouble(AJTilingSprite, AETilingSprite, TileScaleY);
_propertyDouble(AJTilingSprite, AETilingSprite, TilePositionX);
_propertyDouble(AJTilingSprite, AETilingSprite, TilePositionY);


bool AJTilingSprite::fromFrame(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 3) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeTilingSprite()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    string     frame       = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    GLfloat    width       = jsargs.get(1).toDouble();
    GLfloat    height      = jsargs.get(2).toDouble();
    AETexture* texture     = napixi->textureWithFrame(frame);
    AETilingSprite* nathis = new AETilingSprite(texture, width, height);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

bool AJTilingSprite::fromImage(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 3) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeTilingSprite()), NullPtr());
    
    string     image       = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    GLfloat    width       = jsargs.get(1).toDouble();
    GLfloat    height      = jsargs.get(2).toDouble();
    AETexture* texture     = napixi->textureWithImage(image);
    AETilingSprite* nathis = new AETilingSprite(texture, width, height);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}


const JSClass AJTilingSprite::Clazz = _aj_class(AJTilingSprite, TilingSprite);
const JSFunctionSpec AJTilingSprite::Functions[] = {
    JS_FS_END
};
const JSPropertySpec AJTilingSprite::Properties[] = {
    _aj_property_spec(AJTilingSprite, TileScale,     tileScale),
    _aj_property_spec(AJTilingSprite, TilePosition,  tilePosition),
    _aj_property_spec(AJTilingSprite, TileScaleX,    tileScaleX),
    _aj_property_spec(AJTilingSprite, TileScaleY,    tileScaleY),
    _aj_property_spec(AJTilingSprite, TilePositionX, tilePositionX),
    _aj_property_spec(AJTilingSprite, TilePositionY, tilePositionY),
    JS_PS_END
};
const JSFunctionSpec AJTilingSprite::StaticFunctions[] = {
    _aj_function_spec(AJTilingSprite, 3, fromFrame),
    _aj_function_spec(AJTilingSprite, 3, fromImage),
    JS_FS_END
};
const JSPropertySpec AJTilingSprite::StaticProperties[] = {
    JS_PS_END
};
bool AJTilingSprite::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 3) {
        fprintf(stderr, "[AJTilingSprite::%s] params count is %d.", __func__, argc);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeTilingSprite()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    AETexture*      texture = (AETexture*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    GLfloat         width   = jsargs.get(1).toDouble();
    GLfloat         height  = jsargs.get(2).toDouble();
    AETilingSprite* nathis  = new AETilingSprite(texture, width, height);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJTilingSprite::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJTilingSprite::%s]\n", __func__);
    AETilingSprite* nathis = (AETilingSprite*)JS_GetPrivate(jsthis);
    delete nathis;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJTilingSprite::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTilingSprite::%s]\n", __func__);
    return true;
}
bool AJTilingSprite::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTilingSprite::%s]\n", __func__);
    return true;
}
