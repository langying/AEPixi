//
//  AJText.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/16.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AEText.h"
#include "AJText.h"

using namespace JS;
using namespace std;

_propertyString(AJText, AEText, Text);

const JSClass AJText::Clazz = _aj_class(AJText, Text);
const JSFunctionSpec AJText::Functions[] = {
    JS_FS_END
};
const JSPropertySpec AJText::Properties[] = {
    _aj_property_spec(AJText, Text, text),
    JS_PS_END
};
const JSFunctionSpec AJText::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJText::StaticProperties[] = {
    JS_PS_END
};
bool AJText::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJText::%s] params count is 0.", __func__);
        return false;
    }
    
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeSprite()), NullPtr());
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    string    natext = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    AEText*   nathis = new AEText(natext);
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJText::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJText::%s]\n", __func__);
    AEText* target = (AEText*)JS_GetPrivate(jsthis);
    delete target;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJText::GetProperty(JSContext* cx, JSObject* handle, jsval handId, jsval* vp) {
    fprintf(stderr, "[AJText::%s]\n", __func__);
    return true;
}
bool AJText::SetProperty(JSContext* cx, JSObject* handle, jsval handId, jsval* vp) {
    fprintf(stderr, "[AJText::%s]\n", __func__);
    return true;
}

