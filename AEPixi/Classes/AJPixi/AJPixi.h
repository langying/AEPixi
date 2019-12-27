//
//  AJPixi.h
//  AEPixi
//
//  Created by hanqiong on 15/1/26.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AJPixi__
#define __AEPixi__AJPixi__

#include "jsapi.h"
#include "Maybe.h"
#include "AEPixi.h"
#include "AJTouch.h"
#include "AECommon.h"
#include "AJCommon.h"
#include "AERenderer.h"
#include "jsfriendapi.h"
#include "AJBaseCallback.h"
#include "AJTilingSprite.h"

class AJPixi: public AEPixi {
public:
    _ae_property(JSObject*,  Global,  global);
    _ae_property(JSObject*,  JSPIXI,  jspixi);
    _ae_property(JSContext*, Context, context);
    _ae_property(JSRuntime*, Runtime, runtime);
    
    _ae_property(JSObject*, PrototypeNodeBase,     prototypeNodeBase);
    _ae_property(JSObject*, PrototypeRendererBase, prototypeRendererBase);
    _ae_property(JSObject*, PrototypeNode,         prototypeNode);
    _ae_property(JSObject*, PrototypeRope,         prototypeRope);
    _ae_property(JSObject*, PrototypeGraphics,     prototypeGraphics);
    _ae_property(JSObject*, PrototypeSprite,       prototypeSprite);
    _ae_property(JSObject*, PrototypeMovieClip,    prototypeMovieClip);
    _ae_property(JSObject*, PrototypeTilingSprite, prototypeTilingSprite);
    _ae_property(JSObject*, PrototypeText,         prototypeText);
    _ae_property(JSObject*, PrototypeTexture,      prototypeTexture);
    _ae_property(JSObject*, PrototypeRenderer,     prototypeRenderer);
    _ae_property(JSObject*, PrototypeAssertLoader, prototypeAssertLoader);
    
    _ae_property(JSObject*, PrototypeTouch,  prototypeTouch);
    _ae_property(JSObject*, PrototypeMatrix, prototypeMatrix);
    
public:
    _aj_function(_log);
    _aj_function(_setTimeout);
    _aj_function(_addResource);
    _aj_function(_loadResourcesCallback);
    _aj_function(_requestAnimationFrame);
    
    static const JSClass Clazz;
    static const JSPrincipals TrustedPrincipals;
    static const JSSecurityCallbacks SecurityCallbacks;
    static bool  checkAuthAccess(JSContext* context);
    static void  report(JSContext* cx, const char* message,  JSErrorReport* report);
    
public:
    ~AJPixi();
    AJPixi();
    AJPixi(std::string pixifile);
    
    void onLoop();
    void onTouch(AEPointList& points, const char* name);
    void loadGame(std::string pathfile);
    void evaluate(std::string pathfile);
    void addCallback(JSContext* cx, JS::HandleValue function, GLuint timeout);
    
protected:
    std::vector<AJBaseCallback*> callbacks;
    
protected:
    JSObject* globalObject();
    void bindingPixi();
    void runCallback();
    void runRequestAnimFrame();
};

#endif /* defined(__AEPixi__AJPixi__) */
