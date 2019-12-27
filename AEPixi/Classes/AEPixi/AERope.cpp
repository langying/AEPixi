//
//  AERope.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AERope.h"

using namespace std;

_ae_synthesize(AERope, GLuint,     Size, size);
_ae_synthesize(AERope, AEPoint*,   PTs,  pts);
_ae_synthesize(AERope, AEPoint*,   UVs,  uvs);
_ae_synthesize(AERope, AETexture*, Texture, texture);

AERope::~AERope() {
    _ae_free(_pts);
    _ae_free(_uvs);
}
AERope::AERope(AETexture* texture, AEPointList& points): AENode() {
    _size = (GLuint)points.size();
    _texture = texture;
    _pts     = (AEPoint*)malloc(2 * _size * sizeof(AEPoint));
    _uvs     = (AEPoint*)malloc(2 * _size * sizeof(AEPoint));
    AERect crop = _texture->crop();
    AESize base = _texture->baseTexture()->getSize();
    AERect edge = {crop.x/base.width, crop.y/base.height, (crop.x+crop.width)/base.width, (crop.y+crop.height)/base.height}; // 4个边界值
    
    GLfloat amout;
    for (GLuint i = 0, idx = 0; i < _size; i++) {
        idx = i * 2;
        amout = edge.x + i / (GLfloat)(_size-1);
        _uvs[idx+0] = {amout, edge.y};
        _uvs[idx+1] = {amout, edge.height};
    }
    update(points);
}

GLbool AERope::valid() {
    return _texture && _texture->baseTexture() && _texture->baseTexture()->valid();
}

GLvoid AERope::update(AEPointList& points) {
    AEPoint pt1, pt2, last = points[0];
    GLfloat sin, cos, len, mid = _texture->getHeight() / 2;
    for (GLuint i = 0; i < _size; i++) {
        pt1 = points[i];
        pt2 = (i < _size-1) ? points[i+1] : pt1;
        
        len = AEPointLength(pt2, last);
        sin = (pt2.y - last.y) / len * mid;
        cos = (pt2.x - last.x) / len * mid;
        
        _pts[i*2 + 0] = {pt1.x + sin, pt1.y - cos};
        _pts[i*2 + 1] = {pt1.x - sin, pt1.y + cos};
        
        last = pt1;
    }
}

GLvoid AERope::applyRender(AERenderer* renderer) {
    if (valid()) {
        AENode::applyRender(renderer);
        renderer->renderRope(this);
    }
}
