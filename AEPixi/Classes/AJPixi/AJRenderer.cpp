//
//  AJRenderer.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/3/5.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AJPixi.h"
#include "AERenderer.h"
#include "AJRenderer.h"

using namespace JS;

_propertyDouble(AJRenderer, AERenderer, Width);
_propertyDouble(AJRenderer, AERenderer, Height);

bool AJRenderer::clear(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    AERenderer* nathis = (AERenderer*)JS_GetPrivate(jsthis);
    nathis->clear();
    return true;
}
bool AJRenderer::flush(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    AERenderer* nathis = (AERenderer*)JS_GetPrivate(jsthis);
    nathis->flush();
    return true;
}

const JSClass AJRenderer::Clazz = _aj_class(AJRenderer, Renderer);
const JSFunctionSpec AJRenderer::Functions[] = {
    _aj_function_spec(AJRenderer, 0, clear),
    _aj_function_spec(AJRenderer, 0, flush),
    JS_FS_END
};
const JSPropertySpec AJRenderer::Properties[] = {
    _aj_property_spec(AJRenderer, Width,  width),
    _aj_property_spec(AJRenderer, Height, height),
    JS_PS_END
};
const JSFunctionSpec AJRenderer::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJRenderer::StaticProperties[] = {
    JS_PS_END
};
bool AJRenderer::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    AJPixi*     pixi   = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    JSObject*   jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, pixi->getPrototypeRenderer()), NullPtr());
    AERenderer* nathis = new AERenderer(jsargs.get(0).toInt32(), jsargs.get(1).toInt32());
    if (argc >= 3) {
        RootedValue bgColor(cx);
        JS_GetProperty(cx, RootedObject(cx, jsargs.get(2).toObjectOrNull()), "backgroundColor", &bgColor);
        nathis->setBgColor({ (GLuint)bgColor.toInt32()});
    }
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJRenderer::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJRenderer::%s]\n", __func__);
    AERenderer* target = (AERenderer*)JS_GetPrivate(jsthis);
    delete target;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJRenderer::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJRenderer::%s]\n", __func__);
    return true;
}
bool AJRenderer::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJRenderer::%s]\n", __func__);
    return true;
}