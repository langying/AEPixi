//
//  AJRope.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/10.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AERope.h"
#include "AJPixi.h"
#include "AJRope.h"

using namespace JS;

bool AJRope::applyTransform(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "%s params count is 0.\n", __func__);
        return false;
    }
    
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AERope*   nathis = (AERope*)JS_GetPrivate(jsthis);
    JSObject* jsnode = jsargs.get(0).toObjectOrNull();
    AENode*   nanode = jsnode ? (AENode*)JS_GetPrivate(jsnode) : nullptr;
    
    RootedValue value(cx);
    JS_GetProperty(cx, RootedObject(cx, jsthis), "points", &value);
    
    GLuint length = 0;
    RootedObject jspoints(cx, value.toObjectOrNull());
    JS_GetArrayLength(cx, jspoints, &length);
    
    AEPoint     napoint;
    AEPointList napoints;
    RootedValue jspoint(cx);
    for (GLuint i = 0; i < length; i++) {
        JS_GetElement(cx, jspoints, i, &jspoint);
        JSValueToAEPoint(cx, jspoint, &napoint);
        napoints.push_back(napoint);
    }
    nathis->update(napoints);
    nathis->applyTransform(nanode);
    return true;
}


const JSClass AJRope::Clazz = _aj_class(AJRope, Rope);
const JSFunctionSpec AJRope::Functions[] = {
    _aj_function_spec(AJRope, 1, applyTransform),
    JS_FS_END
};
const JSPropertySpec AJRope::Properties[] = {
    JS_PS_END
};
const JSFunctionSpec AJRope::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJRope::StaticProperties[] = {
    JS_PS_END
};
bool AJRope::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 2) {
        fprintf(stderr, "[AJRope::%s] params count is %d.", __func__, argc);
        return false;
    }
    
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeRope()), NullPtr());
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    
    AETexture*   texture = (AETexture*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    RootedObject jspoints(cx, jsargs.get(1).toObjectOrNull());
    JS_SetProperty(cx, RootedObject(cx, jsthis), "points", RootedValue(cx, jsargs.get(1)));
    
    GLuint length = 0;
    JS_GetArrayLength(cx, jspoints, &length);
    
    AEPoint     napoint;
    AEPointList napoints;
    RootedValue jspoint(cx);
    for (GLuint i = 0; i < length; i++) {
        JS_GetElement(cx, jspoints, i, &jspoint);
        JSValueToAEPoint(cx, jspoint, &napoint);
        napoints.push_back(napoint);
    }
    JS_SetPrivate(jsthis, new AERope(texture, napoints));
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJRope::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJRope::%s]\n", __func__);
    AERope* nathis = (AERope*)JS_GetPrivate(jsthis);
    delete nathis;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJRope::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJRope::%s]\n", __func__);
    return true;
}
bool AJRope::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJRope::%s]\n", __func__);
    return true;
}

