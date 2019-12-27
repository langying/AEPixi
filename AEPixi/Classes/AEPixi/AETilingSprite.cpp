//
//  AETilingSprite.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/4.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AETilingSprite.h"

_ae_synthesize(AETilingSprite, AESize,  TileSize,     tileSize);
_ae_synthesize(AETilingSprite, AEPoint, TileScale,    tileScale);
_ae_synthesize(AETilingSprite, AEPoint, TilePosition, tilePosition);

AETilingSprite::AETilingSprite(AETexture* texture, GLfloat w, GLfloat h): AESprite(texture) {
    _tileSize     = AESizeMake(w, h);
    _tileScale    = AEPointMake(1, 1);
    _tilePosition = AEPointMake(0, 0);
    setWidth(w);  // 缩放
    setHeight(h); // 缩放
}

GLvoid AETilingSprite::applyRender(AERenderer* renderer) {
    if (!_visible || _alpha == 0) {
        return;
    }
    AENode::applyRender(renderer);
    renderer->renderTilingSprite(this);
}

AERect AETilingSprite::getBounds() {
    GLfloat width  = _frame.width;
    GLfloat height = _frame.height;
    
    GLfloat w0 = width * (1 - _anchor.x);
    GLfloat w1 = width * (0 - _anchor.x);
    
    GLfloat h0 = height * (1 - _anchor.y);
    GLfloat h1 = height * (0 - _anchor.y);
    
    GLfloat a  = _worldTransform.a;
    GLfloat b  = _worldTransform.b;
    GLfloat c  = _worldTransform.c;
    GLfloat d  = _worldTransform.d;
    GLfloat tx = _worldTransform.tx;
    GLfloat ty = _worldTransform.ty;
    
    GLfloat x1 = a * w1 + c * h1 + tx;
    GLfloat y1 = d * h1 + b * w1 + ty;
    
    GLfloat x2 = a * w0 + c * h1 + tx;
    GLfloat y2 = d * h1 + b * w0 + ty;
    
    GLfloat x3 = a * w0 + c * h0 + tx;
    GLfloat y3 = d * h0 + b * w0 + ty;
    
    GLfloat x4 =  a * w1 + c * h0 + tx;
    GLfloat y4 =  d * h0 + b * w1 + ty;
    
    GLfloat minX, maxX, minY, maxY;
    
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
    
    AERect bounds;
    
    bounds.x = minX;
    bounds.width = maxX - minX;
    
    bounds.y = minY;
    bounds.height = maxY - minY;
    
    return bounds;
};

GLfloat AETilingSprite::getTileScaleX() {
    return _tileScale.x;
}
GLvoid AETilingSprite::setTileScaleX(GLfloat tileScaleX) {
    _tileScale.x = tileScaleX;
}
GLfloat AETilingSprite::getTileScaleY() {
    return _tileScale.y;
}
GLvoid AETilingSprite::setTileScaleY(GLfloat tileScaleY) {
    _tileScale.y = tileScaleY;
}
GLfloat AETilingSprite::getTilePositionX() {
    return _tilePosition.x;
}
GLvoid AETilingSprite::setTilePositionX(GLfloat tilePositionX) {
    _tilePosition.x = tilePositionX;
}
GLfloat AETilingSprite::getTilePositionY() {
    return _tilePosition.y;
}
GLvoid AETilingSprite::setTilePositionY(GLfloat tilePositionY) {
    _tilePosition.y = tilePositionY;
}
