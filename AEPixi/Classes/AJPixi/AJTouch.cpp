//
//  AJTouch.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/11.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AETouch.h"
#include "AJTouch.h"

using namespace JS;

_propertyPoint(AJTouch, AETouch, Global);

bool AJTouch::getLocalPosition(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJSprite::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AETouch*  nathis = (AETouch*)JS_GetPrivate(jsthis);
    AENode*   nanode = (AENode* )JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    AEPoint  napoint = nathis->getLocalPosition(nanode);
    jsargs.rval().set(AEPointToJSValue(cx, napoint));
    return true;
}

const JSClass AJTouch::Clazz = _aj_class(AJTouch, Touch);
const JSFunctionSpec AJTouch::Functions[] = {
    _aj_function_spec(AJTouch, 1, getLocalPosition),
    JS_FS_END
};
const JSPropertySpec AJTouch::Properties[] = {
    _aj_property_spec(AJTouch, Global, global),
    JS_PS_END
};
const JSFunctionSpec AJTouch::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJTouch::StaticProperties[] = {
    JS_PS_END
};
bool AJTouch::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {    
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeTouch()), NullPtr());
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AETouch*  nathis = new AETouch();
    
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJTouch::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJTouch::%s]\n", __func__);
    AETouch* nathis = (AETouch*)JS_GetPrivate(jsthis);
    delete nathis;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJTouch::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTouch::%s]\n", __func__);
    return true;
}
bool AJTouch::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJTouch::%s]\n", __func__);
    return true;
}