//
//  AENode.cpp
//  AEPixi
//
//  Created by hanqiong on 15/1/8.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AENode.h"

static GLuint AENodeUUID = 0;

_ae_synthesize(AENode, GLuint, Uuid,  uuid);
_ae_synthesize(AENode, GLuint, State, state);
_ae_synthesize(AENode, GLuint, BackgroundColor, backgroundColor);

_ae_synthesize(AENode, GLfloat, Alpha,      alpha);
_ae_synthesize(AENode, GLfloat, WorldAlpha, worldAlpha);
_ae_synthesize(AENode, GLfloat, Resolution, resolution);
_ae_synthesize(AENode, GLfloat, Rotation,   rotation);

_ae_synthesize(AENode, GLboolean, Visible,       visible);
_ae_synthesize(AENode, GLboolean, Interactive,   interactive);
_ae_synthesize(AENode, GLboolean, CacheAsBitmap, cacheAsBitmap);

_ae_synthesize(AENode, AEPoint, Scale,  scale);
_ae_synthesize(AENode, AEPoint, Pivot,  pivot);
_ae_synthesize(AENode, AEPoint, Anchor, anchor);

_ae_synthesize(AENode, AERect, Frame, frame);

_ae_synthesize(AENode, AETransform, Transform,      transform);
_ae_synthesize(AENode, AETransform, WorldTransform, worldTransform);

AENode::AENode() {
    _uuid  = ++AENodeUUID;
    _state = AEStateNormal;
    _backgroundColor = WhiteColor;
    
    _alpha      = 1;
    _worldAlpha = 1;
    _resolution = 1;
    _rotation   = 0;
    
    _visible       = GL_TRUE;
    _interactive   = GL_FALSE;
    _cacheAsBitmap = GL_FALSE;
    
    _scale  = {1.0, 1.0};
    _pivot  = AEPointZero;
    _anchor = AEPointZero;
    
    _frame  = {0.0, 0.0, 1.0, 1.0};
    
    _transform      = AETransformIdentity;
    _worldTransform = AETransformIdentity;
}
AENode::~AENode() {
}
GLvoid AENode::applyRender(AERenderer* renderer) {
}
GLvoid AENode::applyTransform(AENode* parent) {
    _worldAlpha     = _alpha;
    _worldTransform = _transform;
    
    GLfloat a, b, c, d, tx, ty;
    AETransform& wt = _worldTransform;
    AETransform  pt = AETransformIdentity;
    
    if (parent) {
        pt = parent->_worldTransform;
        _worldAlpha = _worldAlpha * parent->_worldAlpha;
    }
    if (fmodf(_rotation, M_PI_2)) {
        GLfloat sr = sinf(_rotation);
        GLfloat cr = cosf(_rotation);
        a  =  cr * _scale.x;
        b  =  sr * _scale.x;
        c  = -sr * _scale.y;
        d  =  cr * _scale.y;
        tx =  _frame.x;
        ty =  _frame.y;
        if (_pivot.x || _pivot.y) {
            tx -= _pivot.x * a + _pivot.y * c;
            ty -= _pivot.x * b + _pivot.y * d;
        }
        wt.a  =  a * pt.a  +   b * pt.c;
        wt.b  =  a * pt.b  +   b * pt.d;
        wt.c  =  c * pt.a  +   d * pt.c;
        wt.d  =  c * pt.b  +   d * pt.d;
        wt.tx = tx * pt.a  +  ty * pt.c  +  pt.tx;
        wt.ty = tx * pt.b  +  ty * pt.d  +  pt.ty;
    }
    else {
        a  = _scale.x;
        d  = _scale.y;
        tx = _frame.x - _pivot.x * a;
        ty = _frame.y - _pivot.y * d;
        wt.a  = a  * pt.a;
        wt.b  = a  * pt.b;
        wt.c  = d  * pt.c;
        wt.d  = d  * pt.d;
        wt.tx = tx * pt.a + ty * pt.c + pt.tx;
        wt.ty = tx * pt.b + ty * pt.d + pt.ty;
    }
}
GLbool AENode::pointInside(AEPoint pt) {
    GLfloat width  = _frame.width;
    GLfloat height = _frame.height;
    GLfloat x1 = -width * _anchor.x;
    GLfloat y1;
    pt = AEVectorApplyInvertTransform(pt, _worldTransform);
    
    if (pt.x > x1 && pt.x < x1 + width) {
        y1 = -height * _anchor.y;
        if (pt.y > y1 && pt.y < y1 + height) {
            return GL_TRUE;
        }
    }
    return GL_FALSE;
}

AERect AENode::toBounds(AETransform& transform) {
    return _frame;
}
AEPoint AENode::toLocal(AEPoint pt) {
    return AEVectorApplyInvertTransform(pt, _transform);
}
AEPoint AENode::toGlobal(AEPoint pt) {
    return AEVectorApplyTransform(pt, _transform);
}

// --------------Private_Methods------------------
GLfloat AENode::getX() {
    return _frame.x;
}
GLvoid AENode::setX(GLfloat x) {
    _frame.x = x;
}
GLfloat AENode::getY() {
    return _frame.y;
}
GLvoid AENode::setY(GLfloat y) {
    _frame.y = y;
}
GLfloat AENode::getWidth() {
    return _frame.width * _scale.x;
}
GLvoid AENode::setWidth(GLfloat width) {
    if (_frame.width) {
        _scale.x = width / _frame.width;
    }
    else {
        _scale.x = 1;
    }
    _frame.width = width;
}
GLfloat AENode::getHeight() {
    return _frame.height * _scale.x;
}
GLvoid AENode::setHeight(GLfloat height) {
    if (_frame.height) {
        _scale.y = height / _frame.height;
    }
    else {
        _scale.y = 1;
    }
    _frame.height = height;
}
GLfloat AENode::getTop() {
    return _frame.y;
}
GLvoid AENode::setTop(GLfloat top) {
    _frame.y = top;
}
GLfloat AENode::getLeft() {
    return _frame.x;
}
GLvoid AENode::setLeft(GLfloat left) {
    _frame.x = left;
}
GLfloat AENode::getRight() {
    return _frame.x + getWidth();
}
GLvoid AENode::setRight(GLfloat right) {
    _frame.x = right - getWidth();
}
GLfloat AENode::getBottom() {
    return _frame.y + getHeight();
}
GLvoid AENode::setBottom(GLfloat bottom) {
    _frame.y = bottom - getHeight();
}
GLfloat AENode::getScaleX() {
    return _scale.x;
}
GLvoid AENode::setScaleX(GLfloat scaleX) {
    _scale.x = scaleX;
}
GLfloat AENode::getScaleY() {
    return _scale.y;
}
GLvoid AENode::setScaleY(GLfloat scaleY) {
    _scale.y = scaleY;
}
AESize AENode::getSize() {
    return AESizeMake(_frame.width, _frame.height);
}
GLvoid AENode::setSize(AESize size) {
    _frame.width  = size.width;
    _frame.height = size.height;
}
AEPoint AENode::getCenter() {
    AEPoint pt = {_frame.x + _frame.width / 2 + _frame.y + _frame.height / 2};
    return pt;
}
GLvoid AENode::setCenter(AEPoint center) {
    _frame.x = center.x - _frame.width  / 2;
    _frame.y = center.y - _frame.height / 2;
}
AEPoint AENode::getPosition() {
    return AEPointMake(_frame.x, _frame.y);
}
GLvoid AENode::setPosition(AEPoint position) {
    _frame.x = position.x;
    _frame.y = position.y;
}

