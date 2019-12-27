//
//  AJNode.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/1/28.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AENode.h"
#include "AJNode.h"
#include "AJPixi.h"

using namespace JS;
using namespace std;

_propertyInteger(AJNode, AENode, Uuid);
_propertyInteger(AJNode, AENode, State);
_propertyInteger(AJNode, AENode, BackgroundColor);

_propertyDouble(AJNode, AENode, Alpha);
_propertyDouble(AJNode, AENode, WorldAlpha);
_propertyDouble(AJNode, AENode, Resolution);
_propertyDouble(AJNode, AENode, Rotation);

_propertyBoolean(AJNode, AENode, Visible);
_propertyBoolean(AJNode, AENode, Interactive);
_propertyBoolean(AJNode, AENode, CacheAsBitmap);

_propertyPoint(AJNode, AENode, Scale);
_propertyPoint(AJNode, AENode, Pivot);
_propertyPoint(AJNode, AENode, Anchor);

_propertyRect(AJNode, AENode, Frame);

_propertyTransform(AJNode, AENode, Transform);
_propertyTransform(AJNode, AENode, WorldTransform);

_propertyDouble(AJNode, AENode, X);
_propertyDouble(AJNode, AENode, Y);
_propertyDouble(AJNode, AENode, Width);
_propertyDouble(AJNode, AENode, Height);
_propertyDouble(AJNode, AENode, Top);
_propertyDouble(AJNode, AENode, Left);
_propertyDouble(AJNode, AENode, Right);
_propertyDouble(AJNode, AENode, Bottom);
_propertyDouble(AJNode, AENode, ScaleX);
_propertyDouble(AJNode, AENode, ScaleY);
_propertyPoint(AJNode,  AENode, Center);
_propertyPoint(AJNode,  AENode, Position);


bool AJNode::applyRender(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "%s params count is 0.\n", __func__);
        return false;
    }
    
    JSObject*   jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs    jsargs = CallArgsFromVp(argc, vp);
    AENode*     nathis = (AENode*)JS_GetPrivate(jsthis);
    JSObject*   jsrenderer = jsargs.get(0).toObjectOrNull();
    AERenderer* narenderer = (AERenderer*)JS_GetPrivate(jsrenderer);
    nathis->applyRender(narenderer);
    return true;
}
bool AJNode::applyTransform(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "%s params count is 0.\n", __func__);
        return false;
    }
    
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    AENode*   nathis = (AENode*)JS_GetPrivate(jsthis);
    JSObject* jsparent = jsargs.get(0).toObjectOrNull();
    AENode*   naparent = jsparent ? (AENode*)JS_GetPrivate(jsparent) : nullptr;
    nathis->applyTransform(naparent);
    return true;
}
bool AJNode::pointInside(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJNode::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    AEPoint  napoint;
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    if (!JSValueToAEPoint(cx, jsargs.get(0), &napoint)) {
        fprintf(stderr, "[AJNode::%s] params isnot js object.\n", __func__);
        return false;
    }
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    AENode*   nathis = (AENode*)JS_GetPrivate(jsthis);
    jsval     jsrval = BOOLEAN_TO_JSVAL(nathis->pointInside(napoint));
    jsargs.rval().set(jsrval);
    return true;
}
bool AJNode::toBounds(JSContext* cx, uint32_t argc, jsval* vp) {
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    JSObject* jsthis = JS_THIS_OBJECT(cx, vp);
    AENode*   nathis = (AENode*)JS_GetPrivate(jsthis);
    AETransform tran = nathis->worldTransform();
    if (argc > 0) {
        JSValueToAETransform(cx, jsargs.get(0), &tran);
    }
    AERect bounds = nathis->toBounds(tran);
    jsval  jsrval = AERectToJSValue(cx, bounds);
    jsargs.rval().set(jsrval);
    return true;
}
bool AJNode::toLocal(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJNode::%s] params count is %d.\n", __func__, argc);
        return false;
    }

    AEPoint  napoint;
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    if (!JSValueToAEPoint(cx, jsargs.get(0), &napoint)) {
        fprintf(stderr, "[AJNode::%s] params isnot js object.\n", __func__);
        return false;
    }
    if (argc >= 2) {
        AENode* from = (AENode*)JS_GetPrivate(jsargs.get(1).toObjectOrNull());
        napoint = from->toGlobal(napoint);
    }
    JSObject* jsthis  = JS_THIS_OBJECT(cx, vp);
    AENode*   nathis  = (AENode*)JS_GetPrivate(jsthis);
    jsval     jspoint = AEPointToJSValue(cx, nathis->toLocal(napoint));
    jsargs.rval().set(jspoint);
    return true;
}
bool AJNode::toGlobal(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJNode::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    AEPoint  napoint;
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    if (!JSValueToAEPoint(cx, jsargs.get(0), &napoint)) {
        fprintf(stderr, "[AJNode::%s] params isnot js object.\n", __func__);
        return false;
    }
    JSObject* jsthis  = JS_THIS_OBJECT(cx, vp);
    AENode*   nathis  = (AENode*)JS_GetPrivate(jsthis);
    jsval     jspoint = AEPointToJSValue(cx, nathis->toGlobal(napoint));
    jsargs.rval().set(jspoint);
    return true;
}

const JSClass AJNode::Clazz = _aj_class(AJNode, Container);
const JSFunctionSpec AJNode::Functions[] = {
    _aj_function_spec(AJNode, 1, applyRender),
    _aj_function_spec(AJNode, 1, applyTransform),
    _aj_function_spec(AJNode, 1, pointInside),
    _aj_function_spec(AJNode, 0, toBounds),
    _aj_function_spec(AJNode, 1, toLocal),
    _aj_function_spec(AJNode, 1, toGlobal),
    JS_FS_END
};
const JSPropertySpec AJNode::Properties[] = {
    _aj_property_spec(AJNode, Uuid,  uuid),
    _aj_property_spec(AJNode, State, state),
    _aj_property_spec(AJNode, BackgroundColor, backgroundColor),
    
    _aj_property_spec(AJNode, Alpha, alpha),
    _aj_property_spec(AJNode, WorldAlpha, worldAlpha),
    _aj_property_spec(AJNode, Resolution, resolution),
    _aj_property_spec(AJNode, Rotation, rotation),
    
    _aj_property_spec(AJNode, Visible, visible),
    _aj_property_spec(AJNode, Interactive, interactive),
    _aj_property_spec(AJNode, CacheAsBitmap, cacheAsBitmap),
    
    _aj_property_spec(AJNode, Scale, scale),
    _aj_property_spec(AJNode, Pivot, pivot),
    _aj_property_spec(AJNode, Anchor, anchor),
    
    _aj_property_spec(AJNode, Frame, frame),
    
    _aj_property_spec(AJNode, Transform, transform),
    _aj_property_spec(AJNode, WorldTransform, worldTransform),
    
    _aj_property_spec(AJNode, X, x),
    _aj_property_spec(AJNode, Y, y),
    _aj_property_spec(AJNode, Width, width),
    _aj_property_spec(AJNode, Height, height),
    _aj_property_spec(AJNode, Top, top),
    _aj_property_spec(AJNode, Left, left),
    _aj_property_spec(AJNode, Right, right),
    _aj_property_spec(AJNode, Bottom, bottom),
    _aj_property_spec(AJNode, ScaleX, scaleX),
    _aj_property_spec(AJNode, ScaleY, scaleY),
    _aj_property_spec(AJNode, Center, center),
    _aj_property_spec(AJNode, Position, position),
    
    JS_PS_END
};
const JSFunctionSpec AJNode::StaticFunctions[] = {
    JS_FS_END
};
const JSPropertySpec AJNode::StaticProperties[] = {
    JS_PS_END
};
bool AJNode::Constructor(JSContext* cx, uint32_t argc, jsval* vp) {
    AJPixi*   pixi   = (AJPixi*)JS_GetContextPrivate(cx);
    CallArgs  jsargs = CallArgsFromVp(argc, vp);
    JSObject* jsthis = JS_NewObject(cx, &Clazz, RootedObject(cx, pixi->getPrototypeNode()), NullPtr());
    AENode*   nathis = new AENode();
    JS_SetPrivate(jsthis, nathis);
    jsargs.rval().set(OBJECT_TO_JSVAL(jsthis));
    return true;
}
void AJNode::Destructor(JSFreeOp* fop, JSObject* jsthis) {
    AENode* nathils = (AENode*)JS_GetPrivate(jsthis);
    fprintf(stderr, "[AJNode::%s]\n", __func__);
    delete nathils;
    JS_SetPrivate(jsthis, nullptr);
}

bool AJNode::GetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJNode::%s]\n", __func__);
    return true;
}
bool AJNode::SetProperty(JSContext* cx, JSObject* jsobj, jsval id, jsval* vp) {
    fprintf(stderr, "[AJNode::%s]\n", __func__);
    return true;
}

