//
//  AEGraphicsPath.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/10.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEGraphics.h"
#include "AEGraphicsPath.h"

using namespace std;

_ae_synthesize(AEGraphicsPath, GLuint,  Type,   type);
_ae_synthesize(AEGraphicsPath, GLfloat, X,      x);
_ae_synthesize(AEGraphicsPath, GLfloat, Y,      y);
_ae_synthesize(AEGraphicsPath, GLfloat, Width,  width);
_ae_synthesize(AEGraphicsPath, GLfloat, Height, height);
_ae_synthesize(AEGraphicsPath, GLfloat, Radius, radius);

_ae_synthesize(AEGraphicsPath, GLbool,  Filling,   filling);
_ae_synthesize(AEGraphicsPath, GLfloat, FillAlpha, fillAlpha);
_ae_synthesize(AEGraphicsPath, GLuint,  FillColor, fillColor);
_ae_synthesize(AEGraphicsPath, GLfloat, LineAlpha, lineAlpha);
_ae_synthesize(AEGraphicsPath, GLuint,  LineColor, lineColor);
_ae_synthesize(AEGraphicsPath, GLuint,  LineWidth, lineWidth);

AEGraphicsPath* AEGraphicsPath::circle(GLfloat x, GLfloat y, GLfloat radius) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::CIRC);
    path->_x = x;
    path->_y = y;
    path->_radius = radius;
    return path;
}
AEGraphicsPath* AEGraphicsPath::ellipse(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::ELIP);
    path->_x = x;
    path->_y = y;
    path->_width  = width;
    path->_height = height;
    return path;
}
AEGraphicsPath* AEGraphicsPath::polygon(AEPoint pt) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::POLY);
    path->pointList.push_back(pt);
    return path;
}
AEGraphicsPath* AEGraphicsPath::polygon(AEPointList& pts) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::POLY);
    for (AEPoint& pt : pts) {
        path->pointList.push_back(pt);
    }
    return path;
}
AEGraphicsPath* AEGraphicsPath::rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::RECT);
    path->_x = x;
    path->_y = y;
    path->_width  = width;
    path->_height = height;
    return path;
}
AEGraphicsPath* AEGraphicsPath::roundedRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat radius) {
    AEGraphicsPath* path = new AEGraphicsPath(AEGraphics::RREC);
    path->_x = x;
    path->_y = y;
    path->_width  = width;
    path->_height = height;
    path->_radius = radius;
    return path;
}


AEGraphicsPath::~AEGraphicsPath() {
}

AEGraphicsPath::AEGraphicsPath(GLuint type) {
    _type = type;
    reset();
}

GLvoid AEGraphicsPath::apply(AEGraphics* graphics) {
    _fillAlpha = graphics->fillAlpha();
    _fillColor = graphics->fillColor();
    _lineAlpha = graphics->lineAlpha();
    _lineColor = graphics->lineColor();
    _lineWidth = graphics->lineWidth();
}
GLuint AEGraphicsPath::size() {
    return (GLuint)pointList.size();
}
GLvoid AEGraphicsPath::reset() {
    _filling   = GL_FALSE;
    _fillAlpha = 1;
    _fillColor = ClearColor;
    _lineAlpha = 1;
    _lineColor = ClearColor;
    _lineWidth = 0;
    pointList.clear();
}
GLvoid AEGraphicsPath::closeIfNeed() {
    if (_filling) {
        AEPoint pt1 = pointList.front();
        AEPoint pt2 = pointList.back();
        if (pt1.x != pt2.x || pt1.y != pt2.y) {
            pointList.push_back(pt1);
        }
    }
}
GLvoid AEGraphicsPath::resetPoints() {
    GLfloat x = _x;
    GLfloat y = _y;
    GLfloat w = _width;
    GLfloat h = _height;
    if (_type == AEGraphics::RECT) {
        pointList.clear();
        pointList.push_back({x  , y });
        pointList.push_back({x+w, y });
        pointList.push_back({x+w, y+h});
        pointList.push_back({x  , y+h});
        pointList.push_back({x  , y});
    }
    else if (_type == AEGraphics::CIRC || _type == AEGraphics::ELIP) {
        if (_type == AEGraphics::CIRC) {
            w = h = _radius;
        }
        GLuint count = 40;
        GLfloat segmt = M_PI * 2 / count;
        pointList.clear();
        for (GLuint i = 0; i <= count; i++) {
            pointList.push_back({x + sinf(segmt*i) * w, y + cosf(segmt*i) * h});
        }
    }
}
GLbool AEGraphicsPath::pointInside(AEPoint pt) {
    if (_type == AEGraphics::CIRC) {
        if (_radius <= 0) {
            return GL_FALSE;
        }
        else {
            GLfloat dx = _x - pt.x;
            GLfloat dy = _y - pt.y;
            return dx*dx + dy*dy <= _radius*_radius;
        }
    }
    else if (_type == AEGraphics::ELIP) {
        if (_width <= 0 || _height <= 0) {
            return GL_FALSE;
        }
        else {
            GLfloat nx = (pt.x - _x) / _width;
            GLfloat ny = (pt.y - _y) / _height;
            return nx*nx + ny*ny <= 1;
        }
    }
    else if (_type == AEGraphics::RECT) {
        if (_width <= 0 || _height <= 0) {
            return GL_FALSE;
        }
        else {
            return pt.x >= _x && pt.x <= _x+_width && pt.y >= _y && pt.y <= _y+_height;
        }
    }
    else if (_type == AEGraphics::RREC) {
        if (_width <= 0 || _height <= 0) {
            return GL_FALSE;
        }
        else {
            return pt.x >= _x && pt.x < _x+_width && pt.y >= _y && pt.y < _y+_height;
        }
    }
    else {
        GLbool inside = GL_FALSE;
        GLuint length = (GLuint)pointList.size();
        for (GLuint i = 0, j = length - 1; i < length; j = i++) {
            AEPoint& pi = pointList[i];
            AEPoint& pj = pointList[j];
            GLbool  intersect = ((pi.y > pt.y) != (pj.y > pt.y)) && (pt.x < (pj.x - pi.x) * (pt.y - pi.y) / (pj.y - pi.y) + pi.x);
            if (intersect) {
                inside = !inside;
            }
        }
        return inside;
    }
}
AEGraphicsPath* AEGraphicsPath::clone() {
    AEGraphicsPath* path = new AEGraphicsPath(_type);
    path->_x      = _x;
    path->_y      = _y;
    path->_width  = _width;
    path->_height = _height;
    path->_radius = _radius;
    
    path->_filling   = _filling;
    path->_fillAlpha = _fillAlpha;
    path->_fillColor = _fillColor;
    path->_lineAlpha = _lineAlpha;
    path->_lineColor = _lineColor;
    path->_lineWidth = _lineWidth;
    for (AEPoint& pt : pointList) {
        path->pointList.push_back(pt);
    }
    return path;
}

