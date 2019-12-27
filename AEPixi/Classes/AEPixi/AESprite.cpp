//
//  AESprite.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/1/16.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AESprite.h"

_ae_synthesize(AESprite, GLuint,     Tint,          tint);
_ae_synthesize(AESprite, GLuint,     CachedTint,    cachedTint);
AETexture* AESprite::getTexture() { return _texture; }
GLvoid AESprite::setTexture(AETexture* texture) {
    _texture      = texture;
    _cachedTint   = WhiteColor;
    _frame.width  = _texture->getWidth();
    _frame.height = _texture->getHeight();
}
_ae_synthesize(AESprite, AETexture*, TintedTexture, tintedTexture);


AESprite::~AESprite() {
    _ae_delete(_tintedTexture);
}

AESprite::AESprite(): AENode() {
    _tint    = _cachedTint    = WhiteColor;
    _texture = _tintedTexture = nullptr;
}

AESprite::AESprite(AETexture* texture): AESprite() {
    _texture = texture;
    _frame   = AERectMake(0, 0, texture->getWidth(), texture->getHeight());
}

GLboolean AESprite::isValid() {
    return _texture && _texture->getBaseTexture() && _texture->getBaseTexture()->getValid();
}

GLvoid AESprite::applyRender(AERenderer* renderer) {
    if (!_visible || _alpha == 0) {
        return;
    }
    AENode::applyRender(renderer);
    renderer->renderSprite(this);
}

AERect AESprite::toBounds(AETransform& transform) {
    AETransform wt = transform;    
    GLfloat minX, maxX, minY, maxY;
    
    GLfloat width  = _texture->getWidth();
    GLfloat height = _texture->getHeight();
    
    GLfloat w0 = width  * (1 - _anchor.x);
    GLfloat w1 = width  * (0 - _anchor.x);
    GLfloat h0 = height * (1 - _anchor.y);
    GLfloat h1 = height * (0 - _anchor.y);
    
    if (wt.b == 0 && wt.c == 0) {
        wt.a = fabsf(wt.a);
        wt.d = fabsf(wt.d);
        minX = wt.a * w1 + wt.tx;
        maxX = wt.a * w0 + wt.tx;
        minY = wt.d * h1 + wt.ty;
        maxY = wt.d * h0 + wt.ty;
    }
    else {
        GLfloat x1 = wt.a * w1 + wt.c * h1 + wt.tx;
        GLfloat y1 = wt.d * h1 + wt.b * w1 + wt.ty;
        
        GLfloat x2 = wt.a * w0 + wt.c * h1 + wt.tx;
        GLfloat y2 = wt.d * h1 + wt.b * w0 + wt.ty;
        
        GLfloat x3 = wt.a * w0 + wt.c * h0 + wt.tx;
        GLfloat y3 = wt.d * h0 + wt.b * w0 + wt.ty;
        
        GLfloat x4 = wt.a * w1 + wt.c * h0 + wt.tx;
        GLfloat y4 = wt.d * h0 + wt.b * w1 + wt.ty;
        
        minX = x1;
        minX = x2 < minX ? x2 : minX;
        minX = x3 < minX ? x3 : minX;
        minX = x4 < minX ? x4 : minX;
        
        minY = y1;
        minY = y2 < minY ? y2 : minY;
        minY = y3 < minY ? y3 : minY;
        minY = y4 < minY ? y4 : minY;
        
        maxX = x1;
        maxX = x2 > maxX ? x2 : maxX;
        maxX = x3 > maxX ? x3 : maxX;
        maxX = x4 > maxX ? x4 : maxX;
        
        maxY = y1;
        maxY = y2 > maxY ? y2 : maxY;
        maxY = y3 > maxY ? y3 : maxY;
        maxY = y4 > maxY ? y4 : maxY;
    }
    
    AERect bounds = {minX, minY, maxX - minX, maxY - minY};
    return bounds;
}
