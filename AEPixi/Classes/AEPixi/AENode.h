//
//  AENode.h
//  TBBusiness
//
//  Created by hanqiong on 15/1/8.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AENode__
#define __AEPixi__AENode__

#include "AECommon.h"
#include "AERenderer.h"

enum {
    AEStateNormal = 0,
    AEStateSelected,
};

class AENode {
public:
    _ae_property(GLuint, Uuid,  uuid);
    _ae_property(GLuint, State, state);
    _ae_property(GLuint, BackgroundColor, backgroundColor);

    _ae_property(GLfloat, Alpha,      alpha);
    _ae_property(GLfloat, WorldAlpha, worldAlpha);
    _ae_property(GLfloat, Resolution, resolution);
    _ae_property(GLfloat, Rotation,   rotation);

    _ae_property(GLboolean, Visible,       visible);
    _ae_property(GLboolean, Interactive,   interactive);
    _ae_property(GLboolean, CacheAsBitmap, cacheAsBitmap);
        
    _ae_property(AEPoint, Scale,  scale);
    _ae_property(AEPoint, Pivot,  pivot);
    _ae_property(AEPoint, Anchor, anchor);

    _ae_property(AERect, Frame, frame);
    
    _ae_property(AETransform, Transform,      transform);
    _ae_property(AETransform, WorldTransform, worldTransform);
    
public:
    AENode();
    virtual ~AENode();
    virtual GLvoid applyRender(AERenderer* renderer);
    virtual GLvoid applyTransform(AENode* parent);
    virtual GLbool pointInside(AEPoint pt);
    virtual AERect toBounds(AETransform& transform);

public:
    AEPoint toLocal(AEPoint pt);
    AEPoint toGlobal(AEPoint pt);
    
    GLfloat getX();        GLvoid setX(GLfloat x);
    GLfloat getY();        GLvoid setY(GLfloat y);
    GLfloat getWidth();    GLvoid setWidth(GLfloat width);
    GLfloat getHeight();   GLvoid setHeight(GLfloat height);
    GLfloat getTop();      GLvoid setTop(GLfloat top);
    GLfloat getLeft();     GLvoid setLeft(GLfloat left);
    GLfloat getRight();    GLvoid setRight(GLfloat right);
    GLfloat getBottom();   GLvoid setBottom(GLfloat bottom);
    GLfloat getScaleX();   GLvoid setScaleX(GLfloat scaleX);
    GLfloat getScaleY();   GLvoid setScaleY(GLfloat scaleY);
    AESize  getSize();     GLvoid setSize(AESize size);
    AEPoint getCenter();   GLvoid setCenter(AEPoint center);
    AEPoint getPosition(); GLvoid setPosition(AEPoint position);
};

#endif /* defined(__AEPixi__AENode__) */
