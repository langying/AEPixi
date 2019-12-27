//
//  AEGraphicsPath.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/10.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEGraphicsPath__
#define __AEPixi__AEGraphicsPath__

#include "AECommon.h"

class AEGraphics;

class AEGraphicsPath {
public:
    static AEGraphicsPath* circle(GLfloat x, GLfloat y, GLfloat radius);
    static AEGraphicsPath* ellipse(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    static AEGraphicsPath* polygon(AEPoint pt);
    static AEGraphicsPath* polygon(AEPointList& pts);
    static AEGraphicsPath* rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    static AEGraphicsPath* roundedRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat radius);
    
public:
    AEPointList pointList;
    
    _ae_property(GLuint,  Type,  type);
    _ae_property(GLfloat, X,      x);
    _ae_property(GLfloat, Y,      y);
    _ae_property(GLfloat, Width,  width);
    _ae_property(GLfloat, Height, height);
    _ae_property(GLfloat, Radius, radius);
    
    _ae_property(GLbool,  Filling,   filling);
    _ae_property(GLfloat, FillAlpha, fillAlpha);
    _ae_property(GLuint,  FillColor, fillColor);
    _ae_property(GLfloat, LineAlpha, lineAlpha);
    _ae_property(GLuint,  LineColor, lineColor);
    _ae_property(GLuint,  LineWidth, lineWidth);
    
public:
    ~AEGraphicsPath();
    AEGraphicsPath(GLuint type);
    GLvoid apply(AEGraphics* graphics);
    GLuint size();
    GLvoid reset();
    GLvoid closeIfNeed();
    GLvoid resetPoints();
    GLbool pointInside(AEPoint pt);
    AEGraphicsPath* clone();
};

#endif /* defined(__AEPixi__AEGraphicsPath__) */
