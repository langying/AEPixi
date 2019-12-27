//
//  AJTexture.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/2/14.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AJPixi.h"
#include "AJCommon.h"
#include "AETexture.h"
#include "AJTexture.h"

using namespace JS;
using namespace std;

_propertySize(AJTexture,  AETexture, Size);

_propertyDouble(AJTexture, AETexture, Width);
_propertyDouble(AJTexture, AETexture, Height);

bool AJTexture::fromFrame(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stdout, "%s.%s: params count is 0.", __FILE__, __func__);
        return false;
    }
    
    CallArgs   jsargs = CallArgsFromVp(argc, vp);
    string     frame  = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    AJPixi*    napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject*  jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeSprite()), NullPtr());
    AETexture* nathis = napixi->textureWithFrame(frame);
    if (nathis == nullptr) {
        fprintf(stderr, "%s.%s:textureForFrame(%s) not exist!", __FILE__, __func__, frame.c_str());
    }
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}


bool AJTexture::fromImage(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stdout, "AJTexture.%s: params count is 0.", __func__);
        return false;
    }
    
    
    CallArgs   jsargs = CallArgsFromVp(argc, vp);
    AJPixi*    napixi = (AJPixi*)JS_GetContextPrivate(cx);
    string     image  = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    JSObject*  jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeTexture()), NullPtr());
    AETexture* nathis = napixi->textureWithImage(image);
    if (nathis == nullptr) {
        fprintf(stderr, "%s.%s:textureForFrame(%s) not exist!", __FILE__, __func__, image.c_str());
    }
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

const JSClass AJTexture::Clazz = _aj_class(AJTexture, Texture);
const JSFunctionSpec AJTexture::Functions[] = {
    JS_FS_END
};
const JSPropertySpec AJTexture::Properties[] = {
    _aj_property_spec(AJTexture, Size,   size),
    _aj_property_spec(AJTexture, Width,  width),
    _aj_property_spec(AJTexture, Height, height),
    JS_PS_END
};
const JSFunctionSpec AJTexture::StaticFunctions[] = {
    _aj_function_spec(AJTexture, 1, fromImage),
    _aj_function_spec(AJTexture, 1, fromFrame),
    JS_FS_END
};
const JSPropertySpec AJTexture::StaticProperties[] = {
    JS_PS_END
};
bool AJTexture::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    return fromFrame(cx, argc, vp);
}
void AJTexture::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJTexture::%s]\n", __func__);
}
bool AJTexture::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTexture::%s]\n", __func__);
    return true;
}
bool AJTexture::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTexture::%s]\n", __func__);
    return true;
}
