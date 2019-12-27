//
//  AJGraphics.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AJPixi.h"
#include "AEGraphics.h"
#include "AJGraphics.h"

using namespace JS;

_propertyInteger(AJGraphics, AEGraphics, Tint);
_propertyBoolean(AJGraphics, AEGraphics, IsMask);
_propertyInteger(AJGraphics, AEGraphics, BlendMode);
_propertyBoolean(AJGraphics, AEGraphics, Filling);
_propertyBoolean(AJGraphics, AEGraphics, Fillable);
_propertyDouble( AJGraphics, AEGraphics, FillAlpha);
_propertyInteger(AJGraphics, AEGraphics, FillColor);
_propertyDouble( AJGraphics, AEGraphics, LineAlpha);
_propertyInteger(AJGraphics, AEGraphics, LineColor);
_propertyDouble( AJGraphics, AEGraphics, LineWidth);
_propertyDouble( AJGraphics, AEGraphics, BoundsPadding);

bool AJGraphics::clone(JSContext* cx, uint32_t argc, jsval* vp) {
    AJPixi*     napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject*   jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeGraphics()), NullPtr());
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    JS_SetPrivate(jsthis, nathis->clone());
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
bool AJGraphics::lineStyle(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    GLfloat width = 0;
    GLuint  color = 0;
    GLfloat alpha = 1;
    if (argc <= 0) {
    }
    else if (argc <= 1) {
        width = jsargs.get(0).toNumber();
    }
    else if (argc <= 2) {
        width = jsargs.get(0).toNumber();
        color = _aj_clolr(jsargs.get(1).toInt32());
    }
    else {
        width = jsargs.get(0).toNumber();
        color = _aj_clolr(jsargs.get(1).toInt32());
        alpha = jsargs.get(2).toNumber();
    }
    nathis->lineStyle(width, color, alpha);
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}


bool AJGraphics::moveTo(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 2) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->moveTo(jsargs.get(0).toNumber(), jsargs.get(1).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::lineTo(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 2) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->lineTo(jsargs.get(0).toNumber(), jsargs.get(1).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::quadraticCurveTo(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 4) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->quadraticCurveTo(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::bezierCurveTo(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 6) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->bezierCurveTo(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber(), jsargs.get(4).toNumber(), jsargs.get(5).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::arcTo(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 5) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->arcTo(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber(), jsargs.get(4).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::arc(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 5) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    GLbool anticlockwise = argc < 6 ? GL_FALSE : jsargs.get(6).toBoolean();
    nathis->arc(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber(), jsargs.get(4).toNumber(), anticlockwise);
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}

bool AJGraphics::beginFill(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    GLuint  color = 0;
    GLfloat alpha = 1;
    if (argc <= 0) {
    }
    else if (argc <= 1) {
        color = _aj_clolr(jsargs.get(0).toInt32());
    }
    else {
        color = _aj_clolr(jsargs.get(0).toInt32());
        alpha = jsargs.get(1).toNumber();
    }
    
    nathis->beginFill(color, alpha);
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::endFill(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    nathis->endFill();
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::drawRect(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 4) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->drawRect(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::drawRoundedRect(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 5) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->drawRoundedRect(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber(), jsargs.get(4).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}

bool AJGraphics::drawCircle(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 3) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->drawCircle(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::drawEllipse(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 4) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    nathis->drawEllipse(jsargs.get(0).toNumber(), jsargs.get(1).toNumber(), jsargs.get(2).toNumber(), jsargs.get(3).toNumber());
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}
bool AJGraphics::drawPolygon(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJGraphics::%s]: params count is %d.\n", __func__, argc);
        return false;
    }
    
    JSObject*    jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs     jsargs = CallArgsFromVp(argc, vp);
    AEGraphics*  nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    GLuint length;
    AEPointList pointList;
    RootedValue  x(cx);
    RootedValue  y(cx);
    RootedObject points(cx, jsargs.get(0).toObjectOrNull());
    JS_GetArrayLength(cx, points, &length);
    for (GLuint i = 0; i < length; i=i+2) {
        JS_GetElement(cx, points, i+0, &x);
        JS_GetElement(cx, points, i+1, &x);
        pointList.push_back(AEPointMake(x.toNumber(), y.toNumber()));
    }
    nathis->drawPolygon(pointList);
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}


bool AJGraphics::clear(JSContext* cx, uint32_t argc, jsval* vp) {
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    
    nathis->clear();
    jsargs.rval().set(JS_THIS(cx, vp));
    return true;
}

const JSClass AJGraphics::Clazz = _aj_class(AJGraphics, Graphics);
const JSFunctionSpec AJGraphics::Functions[] = {
    _aj_function_spec(AJGraphics, 0, clone),
    _aj_function_spec(AJGraphics, 1, lineStyle),
    
    _aj_function_spec(AJGraphics, 2, moveTo),
    _aj_function_spec(AJGraphics, 2, lineTo),
    _aj_function_spec(AJGraphics, 4, quadraticCurveTo),
    _aj_function_spec(AJGraphics, 6, bezierCurveTo),
    _aj_function_spec(AJGraphics, 5, arcTo),
    _aj_function_spec(AJGraphics, 5, arc),
    
    _aj_function_spec(AJGraphics, 0, beginFill),
    _aj_function_spec(AJGraphics, 0, endFill),
    _aj_function_spec(AJGraphics, 4, drawRect),
    _aj_function_spec(AJGraphics, 5, drawRoundedRect),
    _aj_function_spec(AJGraphics, 3, drawCircle),
    _aj_function_spec(AJGraphics, 4, drawEllipse),
    _aj_function_spec(AJGraphics, 1, drawPolygon),
    
    _aj_function_spec(AJGraphics, 0, clear),
    JS_FS_END
};
const JSPropertySpec AJGraphics::Properties[] = {
    _aj_property_spec(AJGraphics, Tint,      tint),
    _aj_property_spec(AJGraphics, IsMask,    isMask),
    _aj_property_spec(AJGraphics, BlendMode, blendMode),
    _aj_property_spec(AJGraphics, Filling,   filling),
    _aj_property_spec(AJGraphics, Fillable,  fillable),
    _aj_property_spec(AJGraphics, FillAlpha, fillAlpha),
    _aj_property_spec(AJGraphics, FillColor, fillColor),
    _aj_property_spec(AJGraphics, LineAlpha, lineAlpha),
    _aj_property_spec(AJGraphics, LineColor, lineColor),
    _aj_property_spec(AJGraphics, LineWidth, lineWidth),
    _aj_property_spec(AJGraphics, BoundsPadding, boundsPadding),
    JS_PS_END
};
const JSFunctionSpec AJGraphics::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJGraphics::StaticProperties[] = {
    JS_PS_END
};
bool AJGraphics::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    AJPixi*   napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, napixi->getPrototypeGraphics()), NullPtr());
    CallArgs  jsargs = CallArgsFromVp(argc, vp);

    JS_SetPrivate(jsthis, new AEGraphics());
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJGraphics::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    fprintf(stderr, "[AJGraphics::%s]\n", __func__);
    AEGraphics* nathis = (AEGraphics*)JS_GetPrivate(jsthis);
    delete nathis;
    JS_SetPrivate(jsthis, nullptr);
}
bool AJGraphics::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJGraphics::%s]\n", __func__);
    return true;
}
bool AJGraphics::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJGraphics::%s]\n", __func__);
    return true;
}

