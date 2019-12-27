//
//  AJMovieClip.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/3.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AEMovieClip.h"
#include "AJMovieClip.h"

using namespace JS;
using namespace std;

_propertyBoolean(AJMovieClip, AEMovieClip, Loop);
_propertyBoolean(AJMovieClip, AEMovieClip, Playing);
_propertyInteger(AJMovieClip, AEMovieClip, CurrentTime);
_propertyDouble( AJMovieClip, AEMovieClip, AnimationSpeed);

_functionVoid(AJMovieClip, AEMovieClip, play);
_functionVoid(AJMovieClip, AEMovieClip, stop);

_functionUInteger(AJMovieClip, AEMovieClip, totalFrames);
_functionUInteger(AJMovieClip, AEMovieClip, currentFrame);

bool AJMovieClip::fromFrames(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is 0.\n", __func__);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeMovieClip()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    GLuint length = 0;
    vector<AETexture*> textures;
    RootedObject jsframes(cx, jsargs.get(0).toObjectOrNull());
    JS_GetArrayLength(cx, jsframes, &length);
    for (GLuint i = 0; i < length; i++) {
        RootedValue jsframe(cx);
        JS_GetElement(cx, jsframes, i, &jsframe);
        string frame = JS_EncodeStringToUTF8(cx, RootedString(cx, jsframe.toString()));
        textures.push_back(napixi->textureWithFrame(frame));
    }
    
    JS_SetPrivate(jsthis, new AEMovieClip(textures));
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

bool AJMovieClip::fromImages(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is 0.\n", __func__);
        return false;
    }
    
    AJPixi*   napixi  = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis  = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeMovieClip()), NullPtr());
    CallArgs  jsargs  = CallArgsFromVp(argc, vp);
    
    GLuint length = 0;
    vector<AETexture*> textures;
    RootedObject jsimages(cx, jsargs.get(0).toObjectOrNull());
    JS_GetArrayLength(cx, jsimages, &length);
    for (GLuint i = 0; i < length; i++) {
        RootedValue jsimage(cx);
        JS_GetElement(cx, jsimages, i, &jsimage);
        string image = JS_EncodeStringToUTF8(cx, RootedString(cx, jsimage.toString()));
        textures.push_back(napixi->textureWithImage(image));
    }
    
    JS_SetPrivate(jsthis, new AEMovieClip(textures));
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}

bool AJMovieClip::gotoAndStop(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*    jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs     jsargs = CallArgsFromVp(argc, vp);
    AEMovieClip* nathis = (AEMovieClip*)JS_GetPrivate(jsthis);
    nathis->gotoAndStop(jsargs.get(0).toNumber());
    return true;
}

bool AJMovieClip::gotoAndPlay(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*    jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs     jsargs = CallArgsFromVp(argc, vp);
    AEMovieClip* nathis = (AEMovieClip*)JS_GetPrivate(jsthis);
    nathis->gotoAndPlay(jsargs.get(0).toNumber());
    return true;
}

const JSClass AJMovieClip::Clazz = _aj_class(AJMovieClip, MovieClip);
const JSFunctionSpec AJMovieClip::Functions[] = {
    _aj_function_spec(AJMovieClip, 0, play),
    _aj_function_spec(AJMovieClip, 0, stop),
    _aj_function_spec(AJMovieClip, 1, gotoAndStop),
    _aj_function_spec(AJMovieClip, 1, gotoAndPlay),
    _aj_function_spec(AJMovieClip, 0, totalFrames),
    _aj_function_spec(AJMovieClip, 0, currentFrame),
    JS_FS_END
};
const JSPropertySpec AJMovieClip::Properties[] = {
    _aj_property_spec(AJMovieClip, Loop,           loop),
    _aj_property_spec(AJMovieClip, Playing,        playing),
    _aj_property_spec(AJMovieClip, CurrentTime,    currentTime),
    _aj_property_spec(AJMovieClip, AnimationSpeed, animationSpeed),
    JS_PS_END
};
const JSFunctionSpec AJMovieClip::StaticFunctions[] = {
    _aj_function_spec(AJMovieClip, 1, fromFrames),
    _aj_function_spec(AJMovieClip, 1, fromImages),
    JS_FS_END
};
const JSPropertySpec AJMovieClip::StaticProperties[] = {
    JS_PS_END
};
bool AJMovieClip::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMovieClip::%s] params count is 0.", __func__);
        return false;
    }
    
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeMovieClip()), NullPtr());
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    
    GLuint length = 0;
    vector<AETexture*> textures;
    RootedObject jstextures(cx, jsargs.get(0).toObjectOrNull());
    JS_GetArrayLength(cx, jstextures, &length);
    for (GLuint i = 0; i < length; i++) {
        RootedValue jstexture(cx);
        JS_GetElement(cx, jstextures, i, &jstexture);
        AETexture* texture = (AETexture*)JS_GetPrivate(jstexture.toObjectOrNull());
        textures.push_back(texture);
    }
    
    JS_SetPrivate(jsthis, new AEMovieClip(textures));
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJMovieClip::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJMovieClip::%s]\n", __func__);
    AJMovieClip* nathis = (AJMovieClip*)JS_GetPrivate(jsthis);
    _ae_delete(nathis);
    JS_SetPrivate(jsthis, nullptr);
}
bool AJMovieClip::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJMovieClip::%s]\n", __func__);
    return true;
}
bool AJMovieClip::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJMovieClip::%s]\n", __func__);
    return true;
}
