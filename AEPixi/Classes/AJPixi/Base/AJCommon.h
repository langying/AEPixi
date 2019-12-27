//
//  AJCommon.h
//  AEPixi
//
//  Created by hanqiong on 15/2/6.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AJCommon__
#define __AEPixi__AJCommon__

#include "jsapi.h"
#include "AECommon.h"

jsval AESizeToJSValue(JSContext* cx, const AESize& size);
bool  JSValueToAESize(JSContext* cx, jsval v, AESize* size);

jsval AEPointToJSValue(JSContext* cx, const AEPoint& pt);
bool  JSValueToAEPoint(JSContext* cx, jsval v, AEPoint* pt);

jsval AERectToJSValue(JSContext* cx, const AERect& rect);
bool  JSValueToAERect(JSContext* cx, jsval v, AERect* rect);

jsval AETransformToJSValue(JSContext* cx, const AETransform& transform);
bool  JSValueToAETransform(JSContext* cx, jsval v, AETransform* transform);

jsval JSArrayGetElement(JSContext* cx, JSObject* array, GLuint index);

JSObject* AJGetPropertyForKey(JSContext* cx, JSObject* target, const char* key);
void      AJSetPropertyForKey(JSContext* cx, JSObject* target, const char* key, JSObject* value);




#define _aj_binding(context, target, Class, prototype) \
JS_InitClass(context, target, RootedObject(context, prototype), &Class::Clazz, Class::Constructor, 0, Class::Properties, Class::Functions, Class::StaticProperties, Class::StaticFunctions)

#define _aj_class(Clazz, Name) \
{#Name, JSCLASS_HAS_PRIVATE | JSCLASS_HAS_RESERVED_SLOTS(2), JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Clazz::Destructor}

#define _aj_clolr(color) ((color << 8) | 0xFF)




#define _propertyInteger(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = INT_TO_JSVAL(nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (!jsargs.get(0).isNumber()) { \
        JS_ReportError(cx, "argv isnot number."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(jsargs.get(0).toInt32()); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyDouble(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = DOUBLE_TO_JSVAL(nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (!jsargs.get(0).isNumber()) { \
        JS_ReportError(cx, "argv isnot number."); \
        return false; \
    } \
    if (nathis) { \
        double value;\
        ToNumber(cx, jsargs.get(0), &value);\
        nathis->set##Name(value); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyBoolean(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = BOOLEAN_TO_JSVAL(nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (!jsargs.get(0).isBoolean()) { \
        JS_ReportError(cx, "argv isnot number."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(jsargs.get(0).toBoolean()); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertySize(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = AESizeToJSValue(cx, nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    AESize size; \
    if (!JSValueToAESize(cx, jsargs.get(0), &size)) { \
        JS_ReportError(cx, "argv isnot size."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(size); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyRect(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = AERectToJSValue(cx, nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    AERect rect; \
    if (!JSValueToAERect(cx, jsargs.get(0), &rect)) { \
        JS_ReportError(cx, "argv isnot size."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(rect); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyPoint(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = AEPointToJSValue(cx, nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    AEPoint point; \
    if (!JSValueToAEPoint(cx, jsargs.get(0), &point)) { \
        JS_ReportError(cx, "argv isnot size."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(point); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyTransform(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = AETransformToJSValue(cx, nathis->get##Name()); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    AETransform transform; \
    if (!JSValueToAETransform(cx, jsargs.get(0), &transform)) { \
        JS_ReportError(cx, "argv isnot size."); \
        return false; \
    } \
    if (nathis) { \
        nathis->set##Name(transform); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}




#define _propertyString(Clazz, Target, Name) \
bool Clazz::get##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    if (nathis) { \
        jsval ret = STRING_TO_JSVAL(JS_NewStringCopyZ(cx, nathis->get##Name().c_str())); \
        if (ret != JSVAL_NULL) { \
            jsargs.rval().set(ret); \
            return true; \
        } \
        JS_ReportError(cx, "%s : Fail to retrieve property from Target.", __func__); \
        return false; \
    } \
    JS_ReportError(cx, "Invalid object call for function %s", #Clazz); \
    return false; \
} \
bool Clazz::set##Name(JSContext *cx, unsigned argc, JS::Value *vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    string    natext = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString())); \
    if (nathis) { \
        nathis->set##Name(natext); \
        return true; \
    } \
    JS_ReportError(cx, "%s : Invalid native object.", __func__); \
    return false; \
}



#define _propertySlot(Clazz, Target, Name, slot) \
bool Clazz::get##Name(JSContext* cx, JS::HandleObject handle, JS::HandleId handId, JS::MutableHandleValue vp) { \
    vp.set(JS_GetReservedSlot(handle, slot)); \
    return true; \
} \
bool Clazz::set##Name(JSContext* cx, JS::HandleObject handle, JS::HandleId handId, bool strict, JS::MutableHandleValue vp) { \
    JS_SetReservedSlot(handle, slot, vp.get()); \
    return true; \
}

#define _propertyObject(Clazz, Name, name) \
bool Clazz::get##Name(JSContext* cx, JS::HandleObject handle, JS::HandleId handId, JS::MutableHandleValue vp) { \
    RootedValue value(cx); \
    JS_GetProperty(cx, handle, #name, &value); \
    vp.set(value); \
    return true; \
} \
bool Clazz::set##Name(JSContext* cx, JS::HandleObject handle, JS::HandleId handId, bool strict, JS::MutableHandleValue vp) { \
    RootedValue value(cx, vp.get()); \
    JS_SetProperty(cx, handle, #name, value); \
    return true; \
}




#define _functionVoid(Clazz, Target, Name) \
bool Clazz::Name(JSContext* cx, uint32_t argc, jsval* vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    nathis->Name(); \
    return true; \
}

#define _functionInteger(Clazz, Target, Name) \
bool Clazz::Name(JSContext* cx, uint32_t argc, jsval* vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs  = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    jsargs.rval().set(INT_TO_JSVAL(nathis->Name())); \
    return true; \
}

#define _functionUInteger(Clazz, Target, Name) \
bool Clazz::Name(JSContext* cx, uint32_t argc, jsval* vp) { \
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp); \
    CallArgs  jsargs  = CallArgsFromVp(argc, vp); \
    Target*   nathis = (Target*)JS_GetPrivate(jsthis); \
    jsargs.rval().set(UINT_TO_JSVAL(nathis->Name())); \
    return true; \
}

#define _functionRect(Clazz, Target, Name) \
bool Clazz::Name(JSContext* cx, uint32_t argc, jsval* vp) { \
    JSObject* jsobj = JS_THIS_OBJECT(cx, vp); \
    Target* target = (Target*)JS_GetPrivate(jsobj); \
    if (target == nullptr) { \
        return false; \
    } \
    jsval value = RECT_TO_JSVAL(cx, target->Name()); \
    JS_SET_RVAL(cx, vp, value); \
    return true; \
}

#define _functionPoint(Clazz, Target, Name) \
bool Clazz::Name(JSContext* cx, uint32_t argc, jsval* vp) { \
    JSObject* jsobj = JS_THIS_OBJECT(cx, vp); \
    Target* target = (Target*)JS_GetPrivate(jsobj); \
    if (target == nullptr) { \
        return false; \
    } \
    jsval value = POINT_TO_JSVAL(cx, target->Name()); \
    JS_SET_RVAL(cx, vp, value); \
    return true; \
}




// ===============================AEBinding=================================
#define _aj_function(Name) \
static bool Name(JSContext* cx, uint32_t argc, jsval* vp)

#define _aj_function_spec(Clazz, Count ,Function) \
JS_FN(#Function, Clazz::Function, Count, JSPROP_PERMANENT | JSPROP_ENUMERATE)


#define _aj_property(Name) \
static bool get##Name(JSContext *cx, unsigned argc, JS::Value *vp); \
static bool set##Name(JSContext *cx, unsigned argc, JS::Value *vp)

#define _aj_property_spec(Clazz, FuncName, PropName) \
JS_PSGS(#PropName, Clazz::get##FuncName, Clazz::set##FuncName, JSPROP_PERMANENT | JSPROP_ENUMERATE)

#endif /* defined(__AEPixi__AJCommon__) */
