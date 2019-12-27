//
//  AJMatrix.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AEMatrix.h"
#include "AJMatrix.h"

using namespace JS;
using namespace std;

_propertyDouble(AJMatrix, AEMatrix, A);
_propertyDouble(AJMatrix, AEMatrix, B);
_propertyDouble(AJMatrix, AEMatrix, C);
_propertyDouble(AJMatrix, AEMatrix, D);
_propertyDouble(AJMatrix, AEMatrix, Tx);
_propertyDouble(AJMatrix, AEMatrix, Ty);

_functionVoid(AJMatrix, AEMatrix, invert);
_functionVoid(AJMatrix, AEMatrix, identity);

bool AJMatrix::scale(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 2) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    GLfloat x = jsargs.get(0).toDouble();
    GLfloat y = jsargs.get(1).toDouble();
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(jsthis);
    nathis->scale(x, y);
    return true;
}

bool AJMatrix::rotate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    GLfloat   angle  = jsargs.get(0).toDouble();
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    nathis->rotate(angle);
    return true;
}

bool AJMatrix::translate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 2) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    GLfloat x = jsargs.get(0).toDouble();
    GLfloat y = jsargs.get(1).toDouble();
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(jsthis);
    nathis->translate(x, y);
    return true;
}

bool AJMatrix::append(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* matrix = (AEMatrix*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    nathis->append(matrix);
    return true;
}

bool AJMatrix::prepend(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* matrix = (AEMatrix*)JS_GetPrivate(jsargs.get(0).toObjectOrNull());
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    nathis->prepend(matrix);
    return true;
}

bool AJMatrix::toArray(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    GLboolean transp = jsargs.get(0).toBoolean();
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    
    GLfloat matrix[8];
    RootedValue  value(cx);
    RootedObject array(cx, JS_NewArrayObject(cx, 8));
    nathis->toArray(matrix, transp);
    for (GLuint i = 0; i < 8; i++) {
        value = DOUBLE_TO_JSVAL(matrix[i]);
        JS_SetElement(cx, array, i, value);
    }
    jsargs.rval().set(OBJECT_TO_JSVAL(array));
    return true;
}

bool AJMatrix::fromArray(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    JSObject* arrays = jsargs.get(0).toObjectOrNull();
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    
    GLfloat matrix[8];
    for (GLuint i = 0; i < 6; i++) {
        matrix[i] = JSArrayGetElement(cx, arrays, i).toDouble();
    }
    nathis->fromArray(matrix);
    return true;
}

bool AJMatrix::copy(JSContext *cx, uint32_t argc, jsval *vp) {
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    AEMatrix* matrix = (AEMatrix*)JS_GetParent(jsargs.get(0).toObjectOrNull());
    nathis->copy(matrix);
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}

bool AJMatrix::clone(JSContext *cx, uint32_t argc, jsval *vp) {
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    JSObject* object = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeMatrix()), NullPtr());
    JS_SetPrivate(object, nathis->clone());
    jsargs.rval().set(OBJECT_TO_JSVAL(object));
    return true;
}

bool AJMatrix::apply(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    };
    
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    
    AEPoint point;
    JSValueToAEPoint(cx, jsargs.get(0), &point);
    jsargs.rval().set(AEPointToJSValue(cx, nathis->apply(point)));
    return true;
}

bool AJMatrix::applyInverse(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJMatrix::%s] params count is %d.\n", __func__, argc);
        return false;
    };
    
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(JS_THIS_OBJECT(cx, vp));
    
    AEPoint point;
    JSValueToAEPoint(cx, jsargs.get(0), &point);
    jsargs.rval().set(AEPointToJSValue(cx, nathis->applyInverse(point)));
    return true;
}


const JSClass AJMatrix::Clazz = _aj_class(AJMatrix, Matrix);
const JSFunctionSpec AJMatrix::Functions[] = {
    _aj_function_spec(AJMatrix, 2, scale),
    _aj_function_spec(AJMatrix, 1, rotate),
    _aj_function_spec(AJMatrix, 2, translate),
    _aj_function_spec(AJMatrix, 1, append),
    _aj_function_spec(AJMatrix, 1, prepend),
    _aj_function_spec(AJMatrix, 1, toArray),
    _aj_function_spec(AJMatrix, 1, fromArray),
    _aj_function_spec(AJMatrix, 1, copy),
    _aj_function_spec(AJMatrix, 0, clone),
    _aj_function_spec(AJMatrix, 1, apply),
    _aj_function_spec(AJMatrix, 1, applyInverse),
    JS_FS_END
};
const JSPropertySpec AJMatrix::Properties[] = {
    _aj_property_spec(AJMatrix, A,  a),
    _aj_property_spec(AJMatrix, B,  b),
    _aj_property_spec(AJMatrix, C,  c),
    _aj_property_spec(AJMatrix, D,  d),
    _aj_property_spec(AJMatrix, Tx, tx),
    _aj_property_spec(AJMatrix, Ty, ty),
    JS_PS_END
};
const JSFunctionSpec AJMatrix::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJMatrix::StaticProperties[] = {
    JS_PS_END
};
bool AJMatrix::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeMatrix()), NullPtr());
    AEMatrix* nathis = new AEMatrix();
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJMatrix::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    AEMatrix* nathis = (AEMatrix*)JS_GetPrivate(jsthis);
    fprintf(stderr, "[AJMatrix::%s]\n", __func__);
    delete nathis;
    JS_SetPrivate(jsthis, nullptr);
}

bool AJMatrix::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJMatrix::%s]\n", __func__);
    return true;
}
bool AJMatrix::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJMatrix::%s]\n", __func__);
    return true;
}

