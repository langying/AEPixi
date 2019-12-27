//
//  AEGraphics.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/5.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEGraphics__
#define __AEPixi__AEGraphics__

#include "AENode.h"
#include "AEGraphicsPath.h"

typedef std::vector<AEGraphicsPath*> AEGraphicsPathList;

enum class AEBlendMode: GLuint {
    NORMAL      = 0,
    ADD         = 1,
    MULTIPLY    = 2,
    SCREEN      = 3,
    OVERLAY     = 4,
    DARKEN      = 5,
    LIGHTEN     = 6,
    COLOR_DODGE = 7,
    COLOR_BURN  = 8,
    HARD_LIGHT  = 9,
    SOFT_LIGHT  = 10,
    DIFFERENCE  = 11,
    EXCLUSION   = 12,
    HUE         = 13,
    SATURATION  = 14,
    COLOR       = 15,
    LUMINOSITY  = 16
};

class AEGraphics: public AENode {
public:
    static const GLuint POLY = 0;
    static const GLuint RECT = 1;
    static const GLuint CIRC = 2;
    static const GLuint ELIP = 3;
    static const GLuint RREC = 4;
    
public:
    AEGraphicsPathList pathList;
    _ae_property(GLuint,  Tint,      tint);
    _ae_property(GLbool,  IsMask,    isMask);
    _ae_property(GLuint,  BlendMode, blendMode);
    _ae_property(GLbool,  Filling,   filling);
    _ae_property(GLbool,  Fillable,  fillable);
    _ae_property(GLfloat, FillAlpha, fillAlpha);
    _ae_property(GLuint,  FillColor, fillColor);
    _ae_property(GLfloat, LineAlpha, lineAlpha);
    _ae_property(GLuint,  LineColor, lineColor);
    _ae_property(GLfloat, LineWidth, lineWidth);
    _ae_property(GLfloat, BoundsPadding, boundsPadding);
    _ae_property(AEGraphicsPath*, CurrentPath, currentPath);
    
public:
    ~AEGraphics();
    AEGraphics();
    AEGraphics* clone();
    AEGraphics* lineStyle(GLfloat lineWidth, GLuint color, GLfloat alpha);
    
public:
    AEGraphics* moveTo(GLfloat x, GLfloat y);
    AEGraphics* lineTo(GLfloat x, GLfloat y);
    AEGraphics* quadraticCurveTo(GLfloat cpX, GLfloat cpY, GLfloat toX, GLfloat toY);
    AEGraphics* bezierCurveTo(GLfloat cpX, GLfloat cpY, GLfloat cpX2, GLfloat cpY2, GLfloat toX, GLfloat toY);
    AEGraphics* arcTo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius);
    AEGraphics* arc(GLfloat x, GLfloat y, GLfloat radius, GLfloat startAngle, GLfloat endAngle, GLboolean anticlockwise);
    
    AEGraphics* beginFill(GLuint color, GLfloat alpha);
    AEGraphics* endFill();
    AEGraphics* drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    AEGraphics* drawRoundedRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat radius);
    AEGraphics* drawCircle(GLfloat x, GLfloat y, GLfloat radius);
    AEGraphics* drawEllipse(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
    AEGraphics* drawPolygon(std::vector<AEPoint>& points);
    
    
    AEGraphics* clear();
    AERect toBounds(AETransform& t);
    GLbool pointInside(AEPoint pt);
    AERect updateLocalBounds();
    GLvoid drawShape(AEGraphicsPath* path);
    GLvoid applyRender(AERenderer* renderer);
};

#endif /* defined(__AEPixi__AEGraphics__) */
