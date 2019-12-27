//
//  AJSprite.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/2/14.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AJPixi.h"
#include "AESprite.h"
#include "AJSprite.h"

using namespace JS;
using namespace std;

_propertyInteger(AJSprite, AESprite, Tint);
_propertyInteger(AJSprite, AESprite, CachedTint);

bool AJSprite::getTexture(JSContext* cx, uint32_t argc, JS::Value* vp) {
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    jsargs.rval().set(JSVAL_NULL);
    return true;
}
bool AJSprite::setTexture(JSContext* cx, uint32_t argc, JS::Value* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AESprite*   nathis = (AESprite* )JS_GetPrivate(jsthis);
    AETexture* texture = (AETexture*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    nathis->setTexture(texture);
    return true;
}

bool AJSprite::fromFrame(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeSprite()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    string     frame   = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    AETexture* texture = napixi->textureWithFrame(frame);
    AESprite*  nathis  = new AESprite(texture);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

bool AJSprite::fromImage(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is 0.\n", __func__);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeSprite()), NullPtr());

    string     image   = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    AETexture* texture = napixi->textureWithImage(image);
    AESprite*  nathis  = new AESprite(texture);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

const JSClass AJSprite::Clazz = _aj_class(AJSprite, Sprite);
const JSFunctionSpec AJSprite::Functions[] = {
    JS_FS_END
};
const JSPropertySpec AJSprite::Properties[] = {
    _aj_property_spec(AJSprite, Tint, cint),
    _aj_property_spec(AJSprite, CachedTint, cachedTint),
    _aj_property_spec(AJSprite, Texture,    texture),
    JS_PS_END
};
const JSFunctionSpec AJSprite::StaticFunctions[] = {
    _aj_function_spec(AJSprite, 1, fromFrame),
    _aj_function_spec(AJSprite, 1, fromImage),
    JS_FS_END
};
const JSPropertySpec AJSprite::StaticProperties[] = {
    JS_PS_END
};
bool AJSprite::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s] params count is 0.", __func__);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeSprite()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    AETexture* texture = (AETexture*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    AESprite*  nathis  = new AESprite(texture);
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJSprite::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJSprite::%s]\n", __func__);
    AESprite* target = (AESprite*)JS_GetPrivate(jsthis);
    delete target;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJSprite::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJSprite::%s]\n", __func__);
    return true;
}
bool AJSprite::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJSprite::%s]\n", __func__);
    return true;
}
