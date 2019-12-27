//
//  AEGraphics.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/5.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEGraphics.h"
#include "AEGraphicsPath.h"

using namespace std;

_ae_synthesize(AEGraphics, GLuint,  Tint,      tint);
_ae_synthesize(AEGraphics, GLbool,  IsMask,    isMask);
_ae_synthesize(AEGraphics, GLuint,  BlendMode, blendMode);
_ae_synthesize(AEGraphics, GLbool,  Filling,   filling);
_ae_synthesize(AEGraphics, GLbool,  Fillable,  fillable);
_ae_synthesize(AEGraphics, GLfloat, FillAlpha, fillAlpha);
_ae_synthesize(AEGraphics, GLuint,  FillColor, fillColor);
_ae_synthesize(AEGraphics, GLfloat, LineAlpha, lineAlpha);
_ae_synthesize(AEGraphics, GLuint,  LineColor, lineColor);
_ae_synthesize(AEGraphics, GLfloat, LineWidth, lineWidth);
_ae_synthesize(AEGraphics, GLfloat, BoundsPadding, boundsPadding);
_ae_synthesize(AEGraphics, AEGraphicsPath*, CurrentPath, currentPath);

AEGraphics::~AEGraphics() {
    clear();
}

AEGraphics::AEGraphics(): AENode() {
    clear();
}

AEGraphics* AEGraphics::clone() {
    AEGraphics* graphics = new AEGraphics();
    
    graphics->_tint      = _tint;
    graphics->_isMask    = _isMask;
    graphics->_blendMode = _blendMode;
    graphics->_filling   = _filling;
    graphics->_fillable  = _fillable;
    graphics->_fillAlpha = _fillAlpha;
    graphics->_fillColor = _fillColor;
    graphics->_lineAlpha = _lineAlpha;
    graphics->_lineColor = _lineColor;
    graphics->_lineWidth = _lineWidth;
    graphics->_boundsPadding = _boundsPadding;
    for (int i = 0; i < pathList.size(); i++) {
        graphics->pathList.push_back(pathList[i]->clone());
    }
    graphics->_currentPath = graphics->pathList.back();
    return graphics;
}

AEGraphics* AEGraphics::lineStyle(GLfloat lineWidth, GLuint lineColor, GLfloat lineAlpha) {
    _lineAlpha = lineAlpha;
    _lineColor = lineColor;
    _lineWidth = lineWidth;
    if (_currentPath) {
        if (_currentPath->size()) {
            drawShape(AEGraphicsPath::polygon(_currentPath->pointList.back()));
        }
        else {
            _currentPath->setLineWidth(_lineWidth);
            _currentPath->setLineColor(_lineColor);
            _currentPath->setLineAlpha(_lineAlpha);
        }
    }
    return this;
}

AEGraphics* AEGraphics::moveTo(GLfloat x, GLfloat y) {
    drawShape(AEGraphicsPath::polygon({x, y}));
    return this;
}

AEGraphics* AEGraphics::lineTo(GLfloat x, GLfloat y) {
    if (_currentPath) {
        _currentPath->pointList.push_back({x, y});
    }
    return this;
}

AEGraphics* AEGraphics::quadraticCurveTo(GLfloat cpX, GLfloat cpY, GLfloat toX, GLfloat toY) {
    if (_currentPath) {
        if (_currentPath->size() == 0) {
            _currentPath->pointList.push_back(AEPointZero);
        }
    }
    else {
        moveTo(0, 0);
    }
    
    GLfloat xa, ya, n = 20, j = 0;
    if (_currentPath->size() == 0) {
        moveTo(0, 0);
    }
    AEPoint from = _currentPath->pointList.back();
    for (GLuint i = 1; i <= n; ++i) {
        j = i / n;
        xa = from.x + ( (cpX - from.x) * j );
        ya = from.y + ( (cpY - from.y) * j );
        _currentPath->pointList.push_back({
            xa + ( ((cpX + ( (toX - cpX) * j )) - xa) * j ),
            ya + ( ((cpY + ( (toY - cpY) * j )) - ya) * j )
        });
    }
    return this;
}

AEGraphics* AEGraphics::bezierCurveTo(GLfloat cpX, GLfloat cpY, GLfloat cpX2, GLfloat cpY2, GLfloat toX, GLfloat toY) {
    if (_currentPath) {
        if (_currentPath->size() == 0) {
            _currentPath->pointList.push_back(AEPointZero);
        }
    }
    else {
        moveTo(0, 0);
    }
    
    GLfloat j = 0, n = 20, dt, dt2, dt3, t2, t3;
    AEPoint from = _currentPath->pointList.back();
    for (GLuint i = 1; i <= n; ++i) {
        j = i / n;
        dt  = (1 - j);
        dt2 = dt  * dt;
        dt3 = dt2 * dt;
        
        t2 = j  * j;
        t3 = t2 * j;
        _currentPath->pointList.push_back({
            dt3 * from.x + 3 * dt2 * j * cpX + 3 * dt * t2 * cpX2 + t3 * toX,
            dt3 * from.y + 3 * dt2 * j * cpY + 3 * dt * t2 * cpY2 + t3 * toY
        });
    }
    return this;
}

AEGraphics* AEGraphics::arcTo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat radius) {
    if (_currentPath) {
        if (_currentPath->size() == 0) {
            _currentPath->pointList.push_back(AEPointMake(x1, y1));
        }
    }
    else {
        moveTo(x1, y1);
    }
    
    AEPoint from = _currentPath->pointList.back();
    GLfloat a1 = from.y - y1;
    GLfloat b1 = from.x - x1;
    GLfloat a2 = y2 - y1;
    GLfloat b2 = x2 - x1;
    GLfloat mm = fabsf(a1 * b2 - b1 * a2);
    
    if (mm < 1.0e-8 || radius == 0) {
        if (from.x != x1 || from.y != y1) {
            _currentPath->pointList.push_back({x1, y1});
        }
    }
    else {
        GLfloat dd = a1 * a1 + b1 * b1;
        GLfloat cc = a2 * a2 + b2 * b2;
        GLfloat tt = a1 * a2 + b1 * b2;
        GLfloat k1 = radius * sqrt(dd) / mm;
        GLfloat k2 = radius * sqrt(cc) / mm;
        GLfloat j1 = k1 * tt / dd;
        GLfloat j2 = k2 * tt / cc;
        GLfloat cx = k1 * b2 + k2 * b1;
        GLfloat cy = k1 * a2 + k2 * a1;
        GLfloat px = b1 * (k2 + j1);
        GLfloat py = a1 * (k2 + j1);
        GLfloat qx = b2 * (k1 + j2);
        GLfloat qy = a2 * (k1 + j2);
        GLfloat startAngle = atan2(py - cy, px - cx);
        GLfloat endAngle   = atan2(qy - cy, qx - cx);
        arc(cx + x1, cy + y1, radius, startAngle, endAngle, b1 * a2 > b2 * a1);
    }
    return this;
}

AEGraphics* AEGraphics::arc(GLfloat cx, GLfloat cy, GLfloat radius, GLfloat startAngle, GLfloat endAngle, GLboolean anticlockwise) {
    if (startAngle == endAngle) {
        return this;
    }
    
    if (!anticlockwise && endAngle <= startAngle) {
        endAngle += M_PI * 2;
    }
    else if (anticlockwise && startAngle <= endAngle) {
        startAngle += M_PI * 2;
    }
    
    GLfloat sweep = anticlockwise ? (startAngle - endAngle) * -1 : (endAngle - startAngle);
    GLint   segs  = ceil(fabsf(sweep) / (M_PI * 2)) * 40;
    
    if(sweep == 0) {
        return this;
    }
    
    GLfloat startX = cx + cos(startAngle) * radius;
    GLfloat startY = cy + sin(startAngle) * radius;
    
    if (_currentPath) {
        if (anticlockwise && _filling) {
            _currentPath->pointList.push_back({cx, cy});
        }
        else {
            _currentPath->pointList.push_back({startX, startY});
        }
    }
    else {
        if (anticlockwise && _filling) {
            moveTo(cx, cy);
        }
        else {
            moveTo(startX, startY);
        }
    }
    
    GLfloat theta  = sweep / (segs * 2);
    GLfloat theta2 = theta * 2;
    GLfloat cTheta = cos(theta);
    GLfloat sTheta = sin(theta);
    
    GLint segMinus  = segs - 1;
    GLint remainder = (segMinus % 1) / segMinus;
    
    for (GLint i = 0; i <= segMinus; i++) {
        GLfloat real  = i + remainder * i;
        GLfloat angle = (theta + startAngle + theta2 * real);
        GLfloat c =  cos(angle);
        GLfloat s = -sin(angle);
        _currentPath->pointList.push_back({
            ( (cTheta *  c) + (sTheta * s) ) * radius + cx,
            ( (cTheta * -s) + (sTheta * c) ) * radius + cy
        });
    }
    return this;
}

AEGraphics* AEGraphics::beginFill(GLuint fillColor, GLfloat fillAlpha) {
    _filling   = GL_TRUE;
    _fillAlpha = fillAlpha;
    _fillColor = fillColor;
    if (_currentPath && _currentPath->size() <= 2) {
        _currentPath->setFilling(_filling);
        _currentPath->setFillAlpha(_fillAlpha);
        _currentPath->setFillColor(_fillColor);
    }
    return this;
}

AEGraphics* AEGraphics::endFill() {
    _filling   = GL_FALSE;
    _fillAlpha = 1;
    _fillColor = ClearColor;
    return this;
}

AEGraphics* AEGraphics::drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    drawShape(AEGraphicsPath::rectangle(x, y, width, height));
    return this;
}

AEGraphics* AEGraphics::drawRoundedRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat radius) {
    drawShape(AEGraphicsPath::roundedRectangle(x, y, width, height, radius));
    return this;
}

AEGraphics* AEGraphics::drawCircle(GLfloat x, GLfloat y, GLfloat radius) {
    drawShape(AEGraphicsPath::circle(x, y, radius));
    return this;
}

AEGraphics* AEGraphics::drawEllipse(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    drawShape(AEGraphicsPath::ellipse(x, y, width, height));
    return this;
}

AEGraphics* AEGraphics::drawPolygon(AEPointList& pts) {
    drawShape(AEGraphicsPath::polygon(pts));
    return this;
}

AEGraphics* AEGraphics::clear() {
    for (AEGraphicsPath* path : pathList) {
        delete path;
    }
    pathList.clear();
    
    _tint        = WhiteColor;
    _isMask      = GL_FALSE;
    _blendMode   = (GLuint)AEBlendMode::NORMAL;
    _filling     = GL_FALSE;
    _fillable    = GL_FALSE;
    _fillAlpha   = 1;
    _fillColor   = ClearColor;
    _lineAlpha   = 1;
    _lineColor   = ClearColor;
    _lineWidth   = 0;
    _boundsPadding = 0;
    _currentPath = nullptr;
    return this;
}

AERect AEGraphics::toBounds(AETransform& matrix) {
    AERect bounds = updateLocalBounds();
    GLfloat w0 = bounds.x;
    GLfloat w1 = bounds.width  + bounds.x;
    GLfloat h0 = bounds.y;
    GLfloat h1 = bounds.height + bounds.y;
    AETransform worldTransform = matrix;
    
    GLfloat a  = worldTransform.a;
    GLfloat b  = worldTransform.b;
    GLfloat c  = worldTransform.c;
    GLfloat d  = worldTransform.d;
    GLfloat tx = worldTransform.tx;
    GLfloat ty = worldTransform.ty;
    
    GLfloat x1 = a * w1 + c * h1 + tx;
    GLfloat y1 = d * h1 + b * w1 + ty;
    
    GLfloat x2 = a * w0 + c * h1 + tx;
    GLfloat y2 = d * h1 + b * w0 + ty;
    
    GLfloat x3 = a * w0 + c * h0 + tx;
    GLfloat y3 = d * h0 + b * w0 + ty;
    
    GLfloat x4 = a * w1 + c * h0 + tx;
    GLfloat y4 = d * h0 + b * w1 + ty;
    
    GLfloat maxX = x1;
    GLfloat maxY = y1;
    
    GLfloat minX = x1;
    GLfloat minY = y1;
    
    minX = x2 < minX ? x2 : minX;
    minX = x3 < minX ? x3 : minX;
    minX = x4 < minX ? x4 : minX;
    
    minY = y2 < minY ? y2 : minY;
    minY = y3 < minY ? y3 : minY;
    minY = y4 < minY ? y4 : minY;
    
    maxX = x2 > maxX ? x2 : maxX;
    maxX = x3 > maxX ? x3 : maxX;
    maxX = x4 > maxX ? x4 : maxX;
    
    maxY = y2 > maxY ? y2 : maxY;
    maxY = y3 > maxY ? y3 : maxY;
    maxY = y4 > maxY ? y4 : maxY;
    
    return AERectMake(minX, minY, maxX - minX, maxY - minY);
}

GLbool AEGraphics::pointInside(AEPoint pt) {
    pt = AEVectorApplyInvertTransform(pt, _worldTransform);
    for (AEGraphicsPath* path : pathList) {
        if (path->pointInside(pt)) {
            return GL_TRUE;
        }
    }
    return GL_FALSE;
}

AERect AEGraphics::updateLocalBounds() {
    GLfloat minX =  INFINITY;
    GLfloat maxX = -INFINITY;
    GLfloat minY =  INFINITY;
    GLfloat maxY = -INFINITY;
    
    if (pathList.size()) {
        AEPointList points;
        GLfloat x, y, w, h;
        
        for (GLuint i = 0; i < pathList.size(); i++) {
            AEGraphicsPath* path = pathList[i];
            GLuint type = path->type();
            GLuint lineWidth = path->lineWidth();
            
            if (type == AEGraphics::RECT || type == AEGraphics::RREC) {
                x = path->x() - lineWidth / 2;
                y = path->y() - lineWidth / 2;
                w = path->width()  + lineWidth;
                h = path->height() + lineWidth;
                
                minX = x   < minX ? x   : minX;
                maxX = x+w > maxX ? x+w : maxX;
                minY = y   < minY ? y   : minY;
                maxY = y+h > maxY ? y+h : maxY;
            }
            else if (type == AEGraphics::CIRC) {
                x = path->x();
                y = path->y();
                w = path->radius() + lineWidth / 2;
                h = path->radius() + lineWidth / 2;
                
                minX = x-w < minX ? x-w : minX;
                maxX = x+w > maxX ? x+w : maxX;
                minY = y-h < minY ? y-h : minY;
                maxY = y+h > maxY ? y+h : maxY;
            }
            else if (type == AEGraphics::ELIP) {
                x = path->x();
                y = path->y();
                w = path->width()  + lineWidth / 2;
                h = path->height() + lineWidth / 2;
                
                minX = x-w < minX ? x-w : minX;
                maxX = x+w > maxX ? x+w : maxX;
                minY = y-h < minY ? y-h : minY;
                maxY = y+h > maxY ? y+h : maxY;
            }
            else {
                for (AEPoint& pt : path->pointList) {
                    x = pt.x;
                    y = pt.y;
                    minX = x-lineWidth < minX ? x-lineWidth : minX;
                    maxX = x+lineWidth > maxX ? x+lineWidth : maxX;
                    minY = y-lineWidth < minY ? y-lineWidth : minY;
                    maxY = y+lineWidth > maxY ? y+lineWidth : maxY;
                }
            }
        }
    }
    else {
        minX = 0;
        maxX = 0;
        minY = 0;
        maxY = 0;
    }
    
    AERect bounds;
    bounds.x = minX - _boundsPadding;
    bounds.y = minY - _boundsPadding;
    bounds.width  = (maxX - minX) + _boundsPadding * 2;
    bounds.height = (maxY - minY) + _boundsPadding * 2;
    return bounds;
}

GLvoid AEGraphics::drawShape(AEGraphicsPath* path) {
    if (_currentPath) {
        if (_currentPath->size() <= 1) {
            delete _currentPath;
            pathList.pop_back();
        }
        _currentPath = nullptr;
    }
    path->apply(this);
    pathList.push_back(path);
    if (path->type() == AEGraphics::POLY) {
        path->setFilling(_filling);
        _currentPath = path;
    }
}
GLvoid AEGraphics::applyRender(AERenderer* renderer) {
    AENode::applyRender(renderer);
    for (AEGraphicsPath* path : pathList) {
        if (path->type() == AEGraphics::POLY) {
            path->closeIfNeed();
            if (path->size() >= 3 && path->filling()) {
                renderer->renderPolygon(path, _worldTransform);
            }
            if (path->size() >= 2 && path->lineWidth()) {
                renderer->renderLine(path, _worldTransform);
            }
        }
        else if (path->type() == AEGraphics::RECT) {
            if (path->filling()) {
                renderer->renderRect(path, _worldTransform);
            }
            if (path->lineWidth()) {
                path->resetPoints();
                renderer->renderLine(path, _worldTransform);
            }
        }
        else if (path->type() == AEGraphics::CIRC || path->type() == AEGraphics::ELIP) {
            if (path->filling()) {
                renderer->renderCircle(path, _worldTransform);
            }
            if (path->lineWidth()) {
                path->resetPoints();
                renderer->renderLine(path, _worldTransform);
            }
        }
        else if (path->type() == AEGraphics::RREC) {
            if (path->filling()) {
                renderer->renderRRec(path, _worldTransform);
            }
            if (path->lineWidth()) {
                path->resetPoints();
                renderer->renderLine(path, _worldTransform);
            }
        }
    }
}
