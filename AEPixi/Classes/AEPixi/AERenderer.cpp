//
//  AERenderer.cpp
//  TBBusiness
//
//  Created by hanqiong on 15/1/16.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#include "AEPixi.h"
#include "AERope.h"
#include "AEGraphics.h"
#include "AERenderer.h"
#include "AEGraphicsPath.h"
#include "AETilingSprite.h"

using namespace std;

_ae_synthesize(AERenderer, AESize,         Size,             size);
_ae_synthesize(AERenderer, AEColor,        BgColor,          bgColor);
_ae_synthesize(AERenderer, GLfloat,        DeltaTime,        deltaTime);
_ae_synthesize(AERenderer, GLuint,         FrameBuffer,      frameBuffer);
_ae_synthesize(AERenderer, GLuint,         StencilBuffer,    stencilBuffer);
_ae_synthesize(AERenderer, GLint,          SavedFrameBuffer, savedFrameBuffer);
_ae_synthesize(AERenderer, GLuint,         VertexSize,       vertexSize);
_ae_synthesize(AERenderer, GLuint,         VertexIndex,      vertexIndex);
_ae_synthesize(AERenderer, AEVertex*,      VertexBuffer,     vertexBuffer);
_ae_synthesize(AERenderer, AEBaseTexture*, Texture,          texture);
_ae_synthesize(AERenderer, AEBaseTexture*, BaseTexture,      baseTexture);
_ae_synthesize(AERenderer, AEBaseProgram*, CurrentProgram,   currentProgram);

AERenderer::~AERenderer() {
    deleteFrameBuffer();
    _ae_free(_vertexBuffer);
    _ae_delete(_baseProgram);
    _ae_delete(_tilingProgram);
    _ae_delete(_textureProgram);
}
AERenderer::AERenderer() {
    _size             = AESizeZero;
    _bgColor          = { LightBlueColor };
    _deltaTime        = 0;
    _frameBuffer      = 0;
    _stencilBuffer    = 0;
    _savedFrameBuffer = 0;
    _vertexSize       = AERenderVertexSize;
    _vertexIndex      = 0;
    _textureFilter    = GL_LINEAR;
    _vertexBuffer     = (AEVertex*)malloc(_vertexSize * sizeof(AEVertex));
    _texture          = nullptr;
    _baseTexture      = nullptr;
    _currentProgram   = nullptr;
    
    _baseProgram    = nullptr;
    _tilingProgram  = nullptr;
    _textureProgram = nullptr;
}

AERenderer::AERenderer(GLuint width, GLuint height): AERenderer() {
    this->resize(width, height);
}
GLvoid AERenderer::resize(GLuint width, GLuint height) {
    if (width < 1 || height < 1) {
        return;
    }
    if (width == _size.width && height == _size.height) {
        return;
    }
    
    flush();
    deleteFrameBuffer();
    _size = AESizeMake(width, height);
    
    glGenFramebuffers(1, &_frameBuffer);
    bindFrameBuffer();
    
    _texture = new AEBaseTexture(_size, _frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getTextureId(), 0);
    
    if (AEPixi::sharedInstance()->isPackedDepthStencil()) {
        glGenRenderbuffers(1, &_stencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _stencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, _size.width, _size.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,   GL_RENDERBUFFER, _stencilBuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _stencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    else {
        glGenRenderbuffers(1, &_stencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _stencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, _size.width, _size.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _stencilBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    
    clear();
    CheckGlError();
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "glCheckFramebufferStatus error:0x%X", status);
    }
    unbindFrameBuffer();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, _size.width, _size.height);
    bindVertexBuffer();
    CheckGlError();
}

GLvoid AERenderer::clear() {
    static GLlong last = 0;
    if (last == 0) {
        last = AECurrentTime();
    }
    GLlong current = AECurrentTime();
    _deltaTime = (current - last) * 0.06;
    last = current;
    glClearColor(_bgColor.rgba.r/255.0, _bgColor.rgba.g/255.0, _bgColor.rgba.b/255.0, _bgColor.rgba.a/255.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
GLvoid AERenderer::flush() {
    if (_vertexIndex <= 0) {
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, _vertexIndex);
    _vertexIndex = 0;
}
GLvoid AERenderer::renderRope(AERope* rope) {
    if (!rope->valid()) {
        return;
    }
    
    GLuint    size = rope->size();
    AEPoint*    pt = rope->pts();
    AEPoint*    uv = rope->uvs();
    AEVertex*   vb = &_vertexBuffer[_vertexIndex];
    AETransform wt = rope->getWorldTransform();
    GLboolean flag = AETransformIsIdentity(wt);
    
    useProgram(textureProgram());
    useTexture(rope->texture()->baseTexture());
    if (_vertexIndex >= _vertexSize - size*6) {
        flush();
    }
    
    for (GLuint i = 0, idx = 0, index = 0; i < (size-1); i++) {
        idx   = i * 2;
        index = i * 6;
        if (flag) {
            vb[index+0] = {pt[idx+0], uv[idx+0], WhiteColor};
            vb[index+1] = {pt[idx+2], uv[idx+2], WhiteColor};
            vb[index+2] = {pt[idx+1], uv[idx+1], WhiteColor};
            vb[index+3] = {pt[idx+2], uv[idx+2], WhiteColor};
            vb[index+4] = {pt[idx+1], uv[idx+1], WhiteColor};
            vb[index+5] = {pt[idx+3], uv[idx+3], WhiteColor};
        }
        else {
            vb[index+0] = {AEVectorApplyTransform(pt[idx+0], wt), uv[idx+0], WhiteColor};
            vb[index+1] = {AEVectorApplyTransform(pt[idx+2], wt), uv[idx+2], WhiteColor};
            vb[index+2] = {AEVectorApplyTransform(pt[idx+1], wt), uv[idx+1], WhiteColor};
            vb[index+3] = {AEVectorApplyTransform(pt[idx+2], wt), uv[idx+2], WhiteColor};
            vb[index+4] = {AEVectorApplyTransform(pt[idx+1], wt), uv[idx+1], WhiteColor};
            vb[index+5] = {AEVectorApplyTransform(pt[idx+3], wt), uv[idx+3], WhiteColor};
        }
    }
    _vertexIndex = _vertexIndex + 6 * (size-1);
}
GLvoid AERenderer::renderSprite(AESprite* sprite) {
    if (!sprite->isValid()) {
        return;
    }
    
    AETexture* texture = sprite->getTexture();
    useProgram(textureProgram());
    useTexture(texture->getBaseTexture());
    if (_vertexIndex >= _vertexSize - 6) {
        flush();
    }
    AESize      size      = texture->getSize();
    AESize      base      = texture->getBaseTexture()->getSize();
    AERect      crop      = texture->getCrop();
    AERect      trim      = texture->getTrim();
    AEPoint     anchor    = sprite->getAnchor();
    AETransform transform = sprite->getWorldTransform();
    
    GLfloat dx = trim.x - anchor.x * size.width;
    GLfloat dy = trim.y - anchor.y * size.height;
    GLfloat dw = crop.width;
    GLfloat dh = crop.height;
    AEVector d11 = {dx   , dy   };
    AEVector d21 = {dx+dw, dy   };
    AEVector d12 = {dx   , dy+dh};
    AEVector d22 = {dx+dw, dy+dh};

    GLfloat tx = crop.x      / base.width;
    GLfloat ty = crop.y      / base.height;
    GLfloat tw = crop.width  / base.width;
    GLfloat th = crop.height / base.height;
    AEVector t11 = {tx   , ty   };
    AEVector t21 = {tx+tw, ty   };
    AEVector t12 = {tx   , ty+th};
    AEVector t22 = {tx+tw, ty+th};
    
    GLuint color = sprite->getBackgroundColor();
    if (AETransformIsNotIdentity(transform)) {
        d11 = AEVectorApplyTransform(d11, transform);
        d21 = AEVectorApplyTransform(d21, transform);
        d12 = AEVectorApplyTransform(d12, transform);
        d22 = AEVectorApplyTransform(d22, transform);
    }
    
    AEVertex* vb = &_vertexBuffer[_vertexIndex];
    vb[0] = {d11, t11, color};
    vb[1] = {d21, t21, color};
    vb[2] = {d12, t12, color};
    vb[3] = {d21, t21, color};
    vb[4] = {d12, t12, color};
    vb[5] = {d22, t22, color};
    
    _vertexIndex += 6;
}
GLvoid AERenderer::renderTilingSprite(AETilingSprite* sprite) {
    if (!sprite->isValid()) {
        return;
    }
    
    AETexture* texture = sprite->getTexture();
    useProgram(tilingProgram());
    useTexture(texture->getBaseTexture());
    if (_vertexIndex >= _vertexSize - 6) {
        flush();
    }
    AESize      size      = texture->getSize();
    AESize      base      = texture->getBaseTexture()->getSize();
    AERect      crop      = texture->getCrop();
    AERect      trim      = texture->getTrim();
    AEPoint     anchor    = sprite->getAnchor();
    AETransform transform = sprite->getWorldTransform();
    
    {
        AESize      tile      = sprite->getTileSize();
        AEPoint     origin    = sprite->getTilePosition();
        AEPoint     tscale    = sprite->getTileScale();
        
        GLfloat px = 1 / base.width;
        GLfloat py = 1 / base.height;
        
        GLfloat fx = crop.x / base.width;
        GLfloat fy = crop.y / base.height;
        GLfloat fw = crop.width  / base.width;
        GLfloat fh = crop.height / base.height;
        
        GLfloat tx = fmodf(origin.x, size.width *tscale.x) / tile.width;
        GLfloat ty = fmodf(origin.y, size.height*tscale.y) / tile.height;
        GLfloat tw = (base.width  / tile.width ) * tscale.x;
        GLfloat th = (base.height / tile.height) * tscale.y;
        glUniform4f(_tilingProgram->getFrame(),     fx, fy, fw, fh);
        glUniform4f(_tilingProgram->getTransform(), tx, ty, tw, th);
        glUniform2f(_tilingProgram->getPixelSize(), px, py);
    }
    
    GLfloat dx = trim.x - anchor.x * size.width;
    GLfloat dy = trim.y - anchor.y * size.height;
    GLfloat dw = crop.width;
    GLfloat dh = crop.height;
    AEVector d11 = {dx   , dy   };
    AEVector d21 = {dx+dw, dy   };
    AEVector d12 = {dx   , dy+dh};
    AEVector d22 = {dx+dw, dy+dh};
    
    GLfloat tx = crop.x      / base.width;
    GLfloat ty = crop.y      / base.height;
    GLfloat tw = crop.width  / base.width;
    GLfloat th = crop.height / base.height;
    AEVector t11 = {tx   , ty   };
    AEVector t21 = {tx+tw, ty   };
    AEVector t12 = {tx   , ty+th};
    AEVector t22 = {tx+tw, ty+th};
    
    GLuint color = sprite->getBackgroundColor();
    if (AETransformIsNotIdentity(transform)) {
        d11 = AEVectorApplyTransform(d11, transform);
        d21 = AEVectorApplyTransform(d21, transform);
        d12 = AEVectorApplyTransform(d12, transform);
        d22 = AEVectorApplyTransform(d22, transform);
    }
    
    AEVertex* vb = &_vertexBuffer[_vertexIndex];
    vb[0] = {d11, t11, color};
    vb[1] = {d21, t21, color};
    vb[2] = {d12, t12, color};
    vb[3] = {d21, t21, color};
    vb[4] = {d12, t12, color};
    vb[5] = {d22, t22, color};
    
    _vertexIndex += 6;
}
GLvoid AERenderer::renderLine(AEGraphicsPath* path, AETransform& t) {
    flush();
    useProgram(baseProgram());
    
    GLuint index = 0;
    GLuint count = path->size();
    GLuint color = path->lineColor();
    GLuint width = path->lineWidth();
    
    if (width <= 2) {
        flush();
        glLineWidth(width);
        for (GLuint i = 0; i < count; i++) {
            _vertexBuffer[i] = {AEVectorApplyTransform(path->pointList[i], t), AEPointZero, color};
        }
        glDrawArrays(GL_LINE_STRIP, 0, count);
        return;
    }
    
    AEPoint pt1, pt2, pt3;
    AEPoint pp1, pp2, pp3;
    GLfloat a1, b1, c1, a2, b2, c2, dis, denom;
    AEPointList points(path->pointList);
    AEVertex* vb = &_vertexBuffer[_vertexIndex];
    
    if (AEPointIsEqual(points.front(), points.back())) {
        points.pop_back();
        pt1 = AEPointMiddle(points.front(), points.back());
        points.push_back(pt1);
        points.insert(points.begin(), pt1);
        count = (GLuint)points.size();
    }
    
    pt1 = points[0];
    pt2 = points[1];
    pp1 = AEPointPerp(pt1, pt2, width);
    vb[index++] = {{pt1.x-pp1.x, pt1.y-pp1.y}, AEPointZero, color};
    vb[index++] = {{pt1.x+pp1.x, pt1.y+pp1.y}, AEPointZero, color};
    for (GLuint i = 1, size = count-1; i < size; i++) {
        pt1 = points[i-1];
        pt2 = points[i+0];
        pt3 = points[i+1];
        
        pp1 = AEPointPerp(pt1, pt2, width);
        pp2 = AEPointPerp(pt2, pt3, width);
        
        a1 = (-pp1.y + pt1.y) - (-pp1.y + pt2.y);
        b1 = (-pp1.x + pt2.x) - (-pp1.x + pt1.x);
        c1 = (-pp1.x + pt1.x) * (-pp1.y + pt2.y) - (-pp1.x + pt2.x) * (-pp1.y + pt1.y);
        a2 = (-pp2.y + pt3.y) - (-pp2.y + pt2.y);
        b2 = (-pp2.x + pt2.x) - (-pp2.x + pt3.x);
        c2 = (-pp2.x + pt3.x) * (-pp2.y + pt2.y) - (-pp2.x + pt2.x) * (-pp2.y + pt3.y);
    
        denom = a1*b2 - a2*b1;
        if (fabsf(denom) < 0.1) {
            vb[index++] = {{pt2.x-pp1.x, pt2.y-pp1.y}, AEPointZero, color};
            vb[index++] = {{pt2.x+pp1.x, pt2.y+pp1.y}, AEPointZero, color};
            continue;
        }
        
        pt1 = {(b1*c2-b2*c1)/denom, (a2*c1-a1*c2)/denom};
        dis = (pt1.x-pt2.x) * (pt1.x-pt2.x) + (pt1.y-pt2.y) * (pt1.y-pt2.y);
        
        if (dis > 140 * 140) {
            GLfloat x = pp1.y - pp2.y;
            GLfloat y = pp1.x - pp2.x;
            GLfloat d = sqrt(x*x + y*y);
            pp3 = {x/d*width/2, y/d*width/2};
            
            vb[index++] = {{pt2.x-pp3.x, pt2.y-pp3.y}, AEPointZero, color};
            vb[index++] = {{pt2.x+pp3.x, pt2.y+pp3.y}, AEPointZero, color};
            vb[index++] = {{pt2.x-pp3.x, pt2.y-pp3.y}, AEPointZero, color};
        }
        else {
            vb[index++] = {pt1, AEPointZero, color};
            vb[index++] = {{pt2.x-(pt1.x-pt2.x), pt2.y-(pt1.y-pt2.y)}, AEPointZero, color};
        }
    }
    
    pt1 = points[count-2];
    pt2 = points[count-1];
    pp1 = AEPointPerp(pt1, pt2, width);
    vb[index++] = {{pt2.x-pp1.x, pt2.y-pp1.y}, AEPointZero, color};
    vb[index++] = {{pt2.x+pp1.x, pt2.y+pp1.y}, AEPointZero, color};
    
    for (GLuint i = 0; i < index; i++) {
        AEVertex& v = vb[i];
        v.pt = AEVectorApplyTransform(v.pt, t);
    }
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, index);
}
GLvoid AERenderer::renderPolygon(AEGraphicsPath* path, AETransform& t) {
    flush();
    useProgram(baseProgram());
    
    GLuint color = path->fillColor();
    GLbool ident = AETransformIsIdentity(t);
    AEVertex* vb = &_vertexBuffer[_vertexIndex];
    for (size_t i = 0, size = path->pointList.size(); i < size; i++) {
        if (ident) {
            vb[i] = {path->pointList[i], AEPointZero, color};
        }
        else {
            vb[i] = {AEVectorApplyTransform(path->pointList[i], t), AEPointZero, color};
        }
    }
    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)path->pointList.size());
}
GLvoid AERenderer::renderRect(AEGraphicsPath* path, AETransform& transform) {
    useProgram(baseProgram());
    
    if (_vertexIndex >= _vertexSize - 6) {
        flush();
    }
    
    GLfloat x = path->x();
    GLfloat y = path->y();
    GLfloat w = path->width();
    GLfloat h = path->height();
    
    AEPoint d11 = {x  , y  };
    AEPoint d21 = {x+w, y  };
    AEPoint d12 = {x  , y+h};
    AEPoint d22 = {x+w, y+h};
    GLuint  color = path->lineColor();
    
    if(!AETransformIsIdentity(transform)) {
        d11 = AEVectorApplyTransform(d11, transform);
        d21 = AEVectorApplyTransform(d21, transform);
        d12 = AEVectorApplyTransform(d12, transform);
        d22 = AEVectorApplyTransform(d22, transform);
    }
    
    AEVertex *vb = &_vertexBuffer[_vertexIndex];
    vb[0] = {d11, AEPointZero, color};	// top left
    vb[1] = {d21, AEPointZero, color};	// top right
    vb[2] = {d12, AEPointZero, color};	// bottom left
    vb[3] = {d21, AEPointZero, color};	// top right
    vb[4] = {d12, AEPointZero, color};	// bottom left
    vb[5] = {d22, AEPointZero, color};	// bottom right
    
    _vertexIndex += 6;
}
GLvoid AERenderer::renderRRec(AEGraphicsPath* path, AETransform& transform) {
}

GLvoid AERenderer::renderCircle(AEGraphicsPath* path, AETransform& t) {
    flush();
    useProgram(baseProgram());
    
    
    GLfloat x = path->x();
    GLfloat y = path->y();
    GLfloat w = path->width();
    GLfloat h = path->height();
    GLuint  count = 40;
    GLfloat segmt = M_PI * 2 / count;
    AEVertex* vb = &_vertexBuffer[_vertexIndex];
    
    if (path->type() == AEGraphics::CIRC) {
        w = h = path->radius();
    }
    
    GLuint index = 0;
    GLuint color = path->fillColor();
    GLbool ident = AETransformIsIdentity(t);
    vb[index++] = {AEVectorApplyTransform({x, y}, t), AEPointZero, color};
    for (GLuint i = 0; i <= count; i++) {
        if (ident) {
            vb[index++] = {{x+sinf(segmt*i)*w, y+cosf(segmt*i)*h}, AEPointZero, color};
        }
        else {
            vb[index++] = {AEVectorApplyTransform({x+sinf(segmt*i)*w, y+cosf(segmt*i)*h}, t), AEPointZero, color};
        }
    }
    glDrawArrays(GL_TRIANGLE_FAN, 0, index);
}

GLfloat AERenderer::getWidth() {
    return _size.width;
}
GLvoid AERenderer::setWidth(GLfloat  width) {
    _size.width = width;
}
GLfloat AERenderer::getHeight() {
    return _size.height;
}
GLvoid AERenderer::setHeight(GLfloat height) {
    _size.height = height;
}

// ---------------------Private_Methods-------------------------
GLvoid AERenderer::finsh() {
    glFinish();
}
GLvoid AERenderer::bindFrameBuffer() {
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_savedFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
}
GLvoid AERenderer::unbindFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, _savedFrameBuffer);
}
GLvoid AERenderer::deleteFrameBuffer() {
    if (_frameBuffer) {
        glDeleteFramebuffers(1, &_frameBuffer);
        _frameBuffer = 0;
    }
    if (_stencilBuffer) {
        glDeleteBuffers(1, &_stencilBuffer);
        _stencilBuffer = 0;
    }
    _ae_delete(_texture);
    
}
GLvoid AERenderer::bindVertexBuffer() {
    glEnableVertexAttribArray(kAEProgramAttributePt);
    glVertexAttribPointer(kAEProgramAttributePt, 2, GL_FLOAT, GL_FALSE, sizeof(AEVertex), (GLchar*)_vertexBuffer + offsetof(AEVertex, pt));
    
    glEnableVertexAttribArray(kAEProgramAttributeUV);
    glVertexAttribPointer(kAEProgramAttributeUV, 2, GL_FLOAT, GL_FALSE, sizeof(AEVertex), (GLchar*)_vertexBuffer + offsetof(AEVertex, uv));
    
    glEnableVertexAttribArray(kAEProgramAttributeColor);
    glVertexAttribPointer(kAEProgramAttributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(AEVertex), (GLchar*)_vertexBuffer + offsetof(AEVertex, color));
}
GLvoid AERenderer::useProgram(AEBaseProgram* program) {
    if (_currentProgram == program) {
        return;
    }
    flush();
    _currentProgram = program;
    glUseProgram(_currentProgram->getProgram());
    glUniform2f(_currentProgram->getScreen(), _size.width, _size.height);
}
GLvoid AERenderer::useTexture(AEBaseTexture* texture) {
    if (_baseTexture == texture) {
        return;
    }
    flush();
    _baseTexture = texture;
    _baseTexture->setFilter(_textureFilter);
}

// ----------------------GetterAndSetterMethods---------------------
AEBaseProgram* AERenderer::baseProgram() {
    if (_baseProgram == nullptr) {
        _baseProgram = new AEBaseProgram(Shader_Vertex, Shader_Flat);
    }
    return _baseProgram;
}
AETilingProgram* AERenderer::tilingProgram() {
    if (_tilingProgram == nullptr) {
        _tilingProgram = new AETilingProgram(TilingShader, TilingFragment);
    }
    return _tilingProgram;
}
AEBaseProgram* AERenderer::textureProgram() {
    if (_textureProgram == nullptr) {
        _textureProgram = new AEBaseProgram(Shader_Vertex, Shader_Texture);
    }
    return _textureProgram;
}
