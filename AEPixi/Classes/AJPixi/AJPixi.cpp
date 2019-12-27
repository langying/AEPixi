//
//  AJPixi.cpp
//  AEPixi
//
//  Created by hanqiong on 15/1/26.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AJPixi.h"
#include "AJNode.h"
#include "AJRope.h"
#include "AJText.h"
#include "AJMatrix.h"
#include "AJSprite.h"
#include "AJTexture.h"
#include "AJGraphics.h"
#include "AJRenderer.h"
#include "AJMovieClip.h"

using namespace JS;
using namespace std;

enum _AJFunction {
    AJFunctionRequestAnimFrame = 0,
} AJFunction;

_ae_synthesize(AJPixi, JSObject*,  Global,  global);
_ae_synthesize(AJPixi, JSObject*,  JSPIXI,  jspixi);
_ae_synthesize(AJPixi, JSContext*, Context, context);
_ae_synthesize(AJPixi, JSRuntime*, Runtime, runtime);

_ae_synthesize(AJPixi, JSObject*, PrototypeNodeBase,     prototypeNodeBase);
_ae_synthesize(AJPixi, JSObject*, PrototypeRendererBase, prototypeRendererBase);
_ae_synthesize(AJPixi, JSObject*, PrototypeNode,         prototypeNode);
_ae_synthesize(AJPixi, JSObject*, PrototypeRope,         prototypeRope);
_ae_synthesize(AJPixi, JSObject*, PrototypeGraphics,     prototypeGraphics);
_ae_synthesize(AJPixi, JSObject*, PrototypeSprite,       prototypeSprite);
_ae_synthesize(AJPixi, JSObject*, PrototypeMovieClip,    prototypeMovieClip);
_ae_synthesize(AJPixi, JSObject*, PrototypeTilingSprite, prototypeTilingSprite);
_ae_synthesize(AJPixi, JSObject*, PrototypeText,         prototypeText);
_ae_synthesize(AJPixi, JSObject*, PrototypeTexture,      prototypeTexture);
_ae_synthesize(AJPixi, JSObject*, PrototypeRenderer,     prototypeRenderer);
_ae_synthesize(AJPixi, JSObject*, PrototypeAssertLoader, prototypeAssertLoader);

_ae_synthesize(AJPixi, JSObject*, PrototypeTouch,  prototypeTouch);
_ae_synthesize(AJPixi, JSObject*, PrototypeMatrix, prototypeMatrix);

// ---------------------JSBindingMethods--------------------
bool AJPixi::_log(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJPixi::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    fprintf(stderr, "%s\n", JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString())));
    return true;
}
bool AJPixi::_setTimeout(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJPixi::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    AJPixi*  napixi = (AJPixi*)JS_GetContextPrivate(cx);
    napixi->addCallback(cx, jsargs.get(0), jsargs.get(1).toInt32());
    return true;
}
bool AJPixi::_addResource(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJPixi::%s] params count is 0.\n", __func__);
        return false;
    }
    CallArgs jsargs   = CallArgsFromVp(argc, vp);
    AJPixi*  napixi   = (AJPixi*)JS_GetContextPrivate(cx);
    string   resource = JS_EncodeStringToUTF8(cx, RootedString(cx, jsargs.get(0).toString()));
    napixi->addResource(resource);
    return true;
}
bool AJPixi::_loadResourcesCallback(JSContext* cx, uint32_t argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJPixi::%s] params count is 0.\n", __func__);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    AJPixi*  napixi = (AJPixi*)JS_GetContextPrivate(cx);
    napixi->loadAllResouces();
    napixi->addCallback(cx, jsargs.get(0), 0);
    return true;
}
bool AJPixi::_requestAnimationFrame(JSContext* cx, unsigned argc, jsval* vp) {
    if (argc < 1) {
        fprintf(stderr, "[AJPixi::%s] params count is %d.\n", __func__, argc);
        return false;
    }
    CallArgs jsargs = CallArgsFromVp(argc, vp);
    AJPixi*  napixi = (AJPixi*)JS_GetContextPrivate(cx);
    JS_SetReservedSlot(napixi->getGlobal(), AJFunctionRequestAnimFrame, jsargs.get(0));
    return true;
}

const JSClass AJPixi::Clazz = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub
};
const JSPrincipals AJPixi::TrustedPrincipals = {
    1
};
const JSSecurityCallbacks AJPixi::SecurityCallbacks = {
    checkAuthAccess, NULL
};
void AJPixi::report(JSContext* cx, const char* message, JSErrorReport* report) {
    fprintf(stderr, "[%s at %u line] %s\n", (report->filename?report->filename:"[no filename]"), report->lineno, message);
}
bool AJPixi::checkAuthAccess(JSContext* context) {
    return true;
}


AJPixi::~AJPixi() {
    if (_context) {
        JS_DestroyContext(_context);
        _context = nullptr;
    }
    if (_runtime) {
        JS_DestroyRuntime(_runtime);
        _runtime = nullptr;
    }
    JS_ShutDown();
}
AJPixi::AJPixi() {
}
AJPixi::AJPixi(string pixifile): AJPixi() {
    if (!JS_Init()) {
        return;
    }
    
    _pixifile = pixifile;
    _runtime  = JS_NewRuntime(1024*1024*8);
    JS_SetGCParameter(_runtime, JSGC_MAX_BYTES, 0xffffffff);
    JS_SetNativeStackQuota( _runtime, 500000);
    JS_SetSecurityCallbacks(_runtime, &SecurityCallbacks);
    JS_SetTrustedPrincipals(_runtime, &TrustedPrincipals);
    
    _context = JS_NewContext(_runtime, 1024*8);
    JS_SetErrorReporter( _context, report);
    JS_SetContextPrivate(_context, this);
    RuntimeOptionsRef(_runtime).setIon(true);
    RuntimeOptionsRef(_runtime).setBaseline(true);
    
    _global = globalObject();
    JSAutoCompartment ac(_context, _global);
    js::SetDefaultObjectForContext(_context, _global);

    this->bindingPixi();
}

void AJPixi::onLoop() {
    GLlong current  = AECurrentTime();
    GLlong delatime = current - _last;
    if (delatime <= 500) {
        _time += delatime;
    }
    _last = current;
    
    runCallback();
    runRequestAnimFrame();
}

void AJPixi::onTouch(AEPointList& points, const char* function) {
    JSAutoCompartment ac(_context, _global);
    RootedObject array(_context, JS_NewArrayObject(_context, points.size()));
    for (GLuint i = 0, size = (GLuint)points.size(); i < size; i++) {
        JS_SetElement(_context, array, i, RootedValue(_context, AEPointToJSValue(_context, points[i])));
    }
    RootedValue retval(_context);
    jsval params = OBJECT_TO_JSVAL(array);
    HandleValueArray jsargs = HandleValueArray::fromMarkedLocation(1, &params);
    JS_CallFunctionName(_context, RootedObject(_context, _jspixi), function, jsargs, &retval);
}

void AJPixi::loadGame(string pathfile) {
    _basepath = AEURLPath(pathfile);
    evaluate(pathfile);
}
void AJPixi::evaluate(string pathfile) {
    AEData file = AEDataWithPathfile(pathfile);
    GLuint linecount = 1;
    for (GLuint i = 0; i < file.size; i++) {
        if (file.bytes[i] == '\n') {
            linecount++;
        }
    }
    
    RootedValue rval(_context);
    JSAutoCompartment ac(_context, _global);
    string filename = pathfile.substr(pathfile.find_last_of("/") + 1);
    bool success = JS_EvaluateScript(_context, RootedObject(_context, _global), file.bytes, file.size, filename.c_str(), linecount, &rval);
    free(file.bytes);
    JS_MaybeGC(_context);
    
    fprintf(stderr, "[AJPixi::%s] runscrript[%s] success[%d]\n", __func__, filename.c_str(), success);
}
void AJPixi::addCallback(JSContext* cx, HandleValue function, GLuint timeout) {
    callbacks.push_back(new AJBaseCallback(cx, function, _time + timeout));
}

// --------------------------------Private_Methods--------------------------------
JSObject* AJPixi::globalObject() {
    CompartmentOptions options;
    options.setVersion(JSVERSION_LATEST);
    
    JSAutoRequest ar(_context);
    RootedObject glob(_context, JS_NewGlobalObject(_context, &Clazz, nullptr, DontFireOnNewGlobalHook, options));
    if (glob == nullptr) {
        return nullptr;
    }
    JSAutoCompartment ac(_context, glob);
    if (!JS_InitStandardClasses(_context, glob)) {
        return nullptr;
    }
    JS_InitReflect(_context, glob);
    JS_FireOnNewGlobalObject(_context, glob);
    JS_DefineFunction(_context, glob, "setTimeout",            _setTimeout,            1, JSPROP_PERMANENT|JSPROP_ENUMERATE);
    JS_DefineFunction(_context, glob, "requestAnimationFrame", _requestAnimationFrame, 1, JSPROP_PERMANENT|JSPROP_ENUMERATE);
    JS_DefineFunction(_context, glob, "_addResource",          _addResource,           1, JSPROP_PERMANENT|JSPROP_ENUMERATE);
    JS_DefineFunction(_context, glob, "_loadResourcesCallback",_loadResourcesCallback, 1, JSPROP_PERMANENT|JSPROP_ENUMERATE);
    return glob;
}

void AJPixi::bindingPixi() {
    RootedValue  pixiValue(_context);
    RootedObject pixiObject(_context);
    RootedObject glob(_context, _global);
    JS_GetProperty(_context, glob, "PIXI", &pixiValue);
    if (pixiValue == JSVAL_VOID) {
        {
            RootedObject document(_context, JS_NewObject(_context, NULL, NullPtr(), NullPtr()));
            JS_SetProperty(_context, glob, "document", RootedValue(_context, OBJECT_TO_JSVAL(document)));
        }
        {
            RootedObject console(_context, JS_NewObject(_context, NULL, NullPtr(), NullPtr()));
            JS_SetProperty(_context, glob, "console", RootedValue(_context, OBJECT_TO_JSVAL(console)));
            JS_DefineFunction(_context, console, "log", _log, 1, JSPROP_PERMANENT|JSPROP_ENUMERATE);
        }
        pixiObject = JS_NewObject(_context, NULL, NullPtr(), NullPtr());
        pixiValue  = OBJECT_TO_JSVAL(pixiObject);
        JS_SetProperty(_context, glob, "PIXI", pixiValue);
        
        evaluate(_pixifile);
        _prototypeNodeBase     = AJGetPropertyForKey(_context, pixiObject, "NodeBase");
        _prototypeRendererBase = AJGetPropertyForKey(_context, pixiObject, "RendererBase");
    }
    else {
        pixiObject = pixiValue.toObjectOrNull();
    }
    
    _jspixi = pixiObject;
    
    _prototypeNode         = _aj_binding(_context, pixiObject, AJNode,         _prototypeNodeBase);
    _prototypeRope         = _aj_binding(_context, pixiObject, AJRope,         _prototypeNode);
    _prototypeGraphics     = _aj_binding(_context, pixiObject, AJGraphics,     _prototypeNode);
    _prototypeSprite       = _aj_binding(_context, pixiObject, AJSprite,       _prototypeNode);
    _prototypeMovieClip    = _aj_binding(_context, pixiObject, AJMovieClip,    _prototypeSprite);
    _prototypeTilingSprite = _aj_binding(_context, pixiObject, AJTilingSprite, _prototypeSprite);
    _prototypeText         = _aj_binding(_context, pixiObject, AJText,         _prototypeText),
    _prototypeTexture      = _aj_binding(_context, pixiObject, AJTexture,      NULL);
    _prototypeRenderer     = _aj_binding(_context, pixiObject, AJRenderer,     _prototypeRendererBase);
    
    _prototypeTouch  = _aj_binding(_context, pixiObject, AJTouch,  NULL);
    _prototypeMatrix = _aj_binding(_context, pixiObject, AJMatrix, NULL);
}

void AJPixi::runCallback() {
    if (callbacks.empty()) {
        return;
    }
    
    AJBaseCallback* callback = callbacks[0];
    if (_time < callback->timeout()) {
        return;
    }
    
    RootedValue retval(_context);
    RootedValue function(_context, callback->function());
    if (function == JSVAL_VOID) {
        fprintf(stderr, "[AJPixi::%s] function is void.\n", __func__);
    }
    else {
        JSAutoCompartment ac(_context, _global);
        JS_CallFunctionValue(_context, RootedObject(_context, _global), function, HandleValueArray::empty(), &retval);
    }
    callbacks.erase(callbacks.begin());
    delete callback;
}

void AJPixi::runRequestAnimFrame() {
    RootedValue jsfunc(_context, JS_GetReservedSlot(_global, AJFunctionRequestAnimFrame));
    if (jsfunc.isNullOrUndefined()) {
        return;
    }
    
    JSAutoCompartment ac(_context, _global);
    RootedObject target(_context, _global);
    RootedValue  retval(_context);
    JS_CallFunctionValue(_context, target, jsfunc, HandleValueArray::empty(), &retval);
}
