//
//  AJConfig.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/2/6.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include <fstream>
#include "AJCommon.h"

using namespace JS;
using namespace std;

jsval AESizeToJSValue(JSContext* cx, const AESize& size) {
    RootedObject jssize(cx, JS_NewObject(cx, NULL, NullPtr(), NullPtr()));
    bool success = jssize
                && JS_DefineProperty(cx, jssize, "width",  size.width,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jssize, "height", size.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    return success ? OBJECT_TO_JSVAL(jssize) : JSVAL_VOID;
}
bool JSValueToAESize(JSContext *cx, jsval vp, AESize* size) {
    RootedObject jssize(cx);
    RootedValue  jswidth(cx);
    RootedValue  jsheight(cx);
    double width = 0, height = 0;
    bool success =  vp.isObject()
            && JS_ValueToObject(cx, RootedValue(cx, vp), &jssize)
            && JS_GetProperty(cx, jssize, "width",  &jswidth)
            && JS_GetProperty(cx, jssize, "height", &jsheight)
            && ToNumber(cx, jswidth,  &width)
            && ToNumber(cx, jsheight, &height);
    
    if (success) {
        size->width  = (float)width;
        size->height = (float)height;
    }
    return success;
}

jsval AEPointToJSValue(JSContext* cx, const AEPoint& pt) {
    RootedObject jspt(cx, JS_NewObject(cx, NULL, NullPtr(), NullPtr()));
    bool success = jspt
                && JS_DefineProperty(cx, jspt, "x", pt.x, JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jspt, "y", pt.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    return success ? OBJECT_TO_JSVAL(jspt) : JSVAL_VOID;
}
bool JSValueToAEPoint(JSContext* cx, jsval vp, AEPoint* pt) {
    RootedObject jspt(cx);
    RootedValue  jsx(cx);
    RootedValue  jsy(cx);
    double x = 0, y = 0;
    bool success = vp.isObject()
                && JS_ValueToObject(cx, RootedValue(cx, vp), &jspt)
                && JS_GetProperty(cx, jspt, "x", &jsx)
                && JS_GetProperty(cx, jspt, "y", &jsy)
                && ToNumber(cx, jsx, &x)
                && ToNumber(cx, jsy, &y);
    
    if (success) {
        pt->x = (float)x;
        pt->y = (float)y;
    }
    return success;
}

jsval AERectToJSValue(JSContext* cx, const AERect& rect) {
    RootedObject jsrect(cx, JS_NewObject(cx, NULL, NullPtr(), NullPtr()));
    bool success = jsrect
                && JS_DefineProperty(cx, jsrect, "x",      rect.x,      JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jsrect, "y",      rect.y,      JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jsrect, "width",  rect.width,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jsrect, "height", rect.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    return success ? OBJECT_TO_JSVAL(jsrect) : JSVAL_VOID;
}
bool JSValueToAERect(JSContext* cx, jsval v, AERect* ret) {
    RootedObject jsrect(cx);
    RootedValue  jsx(cx);
    RootedValue  jsy(cx);
    RootedValue  jswidth(cx);
    RootedValue  jsheight(cx);
    
    double x = 0, y = 0, width = 0, height = 0;
    bool success = v.isObject()
                && JS_ValueToObject(cx, RootedValue(cx, v), &jsrect)
                && JS_GetProperty(cx, jsrect, "x",      &jsx)
                && JS_GetProperty(cx, jsrect, "y",      &jsy)
                && JS_GetProperty(cx, jsrect, "width",  &jswidth)
                && JS_GetProperty(cx, jsrect, "height", &jsheight)
                && ToNumber(cx, jsx, &x)
                && ToNumber(cx, jsy, &y)
                && ToNumber(cx, jswidth, &width)
                && ToNumber(cx, jsheight, &height);
    
    if (success) {
        ret->x      = (float)x;
        ret->y      = (float)y;
        ret->width  = (float)width;
        ret->height = (float)height;
    }
    return success;
}

jsval AETransformToJSValue(JSContext* cx, const AETransform& t) {
    RootedObject jst(cx, JS_NewObject(cx, NULL, NullPtr(), NullPtr()));
    bool success = jst
                && JS_DefineProperty(cx, jst, "a",   t.a,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jst, "b",   t.b,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jst, "c",   t.c,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jst, "d",   t.d,  JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jst, "tx",  t.tx, JSPROP_ENUMERATE | JSPROP_PERMANENT)
                && JS_DefineProperty(cx, jst, "ty",  t.ty, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    return success ? OBJECT_TO_JSVAL(jst) : JSVAL_VOID;
}
bool  JSValueToAETransform(JSContext* cx, jsval v, AETransform* t) {
    RootedObject jst(cx);
    RootedValue  jsa(cx);
    RootedValue  jsb(cx);
    RootedValue  jsc(cx);
    RootedValue  jsd(cx);
    RootedValue  jstx(cx);
    RootedValue  jsty(cx);
    
    double a, b, c, d, tx, ty;
    a = b = c = d = tx = ty = 0;
    bool success = v.isObject()
                && JS_ValueToObject(cx, RootedValue(cx, v), &jst)
                && JS_GetProperty(cx, jst, "a",  &jsa)
                && JS_GetProperty(cx, jst, "b",  &jsb)
                && JS_GetProperty(cx, jst, "c",  &jsc)
                && JS_GetProperty(cx, jst, "d",  &jsd)
                && JS_GetProperty(cx, jst, "tx", &jstx)
                && JS_GetProperty(cx, jst, "ty", &jsty)
                && ToNumber(cx, jsa,  &a)
                && ToNumber(cx, jsb,  &b)
                && ToNumber(cx, jsc,  &c)
                && ToNumber(cx, jsd,  &d)
                && ToNumber(cx, jstx, &tx)
                && ToNumber(cx, jsty, &ty);
    if (success) {
        t->a  = a;
        t->b  = b;
        t->c  = c;
        t->d  = d;
        t->tx = tx;
        t->ty = ty;
    }
    return success;
}

jsval JSArrayGetElement(JSContext* cx, JSObject* array, GLuint index) {
    RootedValue element(cx);
    JS_GetElement(cx, RootedObject(cx, array), index, &element);
    return element;
}

JSObject* AJGetPropertyForKey(JSContext* cx, JSObject* target, const char* key) {
    RootedValue retv(cx);
    JS_GetProperty(cx, RootedObject(cx, target), key, &retv);
    return retv.toObjectOrNull();
}
void AJSetPropertyForKey(JSContext* cx, JSObject* target, const char* key, Value value) {
    JS_SetProperty(cx, RootedObject(cx, target), key, RootedValue(cx, value));
}
