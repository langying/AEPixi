//
//  AERenderer.h
//  TBBusiness
//
//  Created by hanqiong on 15/1/16.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AERenderer__
#define __AEPixi__AERenderer__

#include "AETexture.h"
#include "AETilingProgram.h"

#define AERenderVertexSize 1800

class AERope;
class AESprite;
class AEGraphics;
class AEGraphicsPath;
class AETilingSprite;

class AERenderer {
public:
    _ae_property(AESize,         Size,             size);
    _ae_property(AEColor,        BgColor,          bgColor);
    _ae_property(GLfloat,        DeltaTime,        deltaTime);
    _ae_property(GLuint,         FrameBuffer,      frameBuffer);
    _ae_property(GLuint,         StencilBuffer,    stencilBuffer);
    _ae_property(GLint,          SavedFrameBuffer, savedFrameBuffer);
    _ae_property(GLuint,         VertexSize,       vertexSize);
    _ae_property(GLuint,         VertexIndex,      vertexIndex);
    _ae_property(GLenum,         TextureFilter,    textureFilter);
    _ae_property(AEVertex*,      VertexBuffer,     vertexBuffer);
    _ae_property(AEBaseTexture*, Texture,          texture);
    _ae_property(AEBaseTexture*, BaseTexture,      baseTexture);
    _ae_property(AEBaseProgram*, CurrentProgram,   currentProgram);
    
    _ae_readonly(AEBaseProgram*,   baseProgram);
    _ae_readonly(AEBaseProgram*,   textureProgram);
    _ae_readonly(AETilingProgram*, tilingProgram);
    
public:
    ~AERenderer();
    AERenderer();
    AERenderer(GLuint width, GLuint height);
    GLvoid resize(GLuint width, GLuint height);
    
    GLvoid clear();
    GLvoid flush();
    GLvoid renderRope(AERope* rope);
    GLvoid renderSprite(AESprite* sprite);
    GLvoid renderTilingSprite(AETilingSprite* sprite);
    GLvoid renderLine(AEGraphicsPath* path, AETransform& t);
    GLvoid renderPolygon(AEGraphicsPath* path, AETransform& t);
    GLvoid renderRect(AEGraphicsPath* path, AETransform& t);
    GLvoid renderRRec(AEGraphicsPath* path, AETransform& t);
    GLvoid renderCircle(AEGraphicsPath* path, AETransform& t);
    
    GLfloat getWidth();  GLvoid setWidth(GLfloat  width);
    GLfloat getHeight(); GLvoid setHeight(GLfloat height);
    
protected:
    GLvoid finsh();
    GLvoid bindFrameBuffer();
    GLvoid unbindFrameBuffer();
    GLvoid deleteFrameBuffer();
    GLvoid bindVertexBuffer();
    GLvoid useProgram(AEBaseProgram* program);
    GLvoid useTexture(AEBaseTexture* texture);
};

#endif /* defined(__AEPixi__AERenderer__) */
