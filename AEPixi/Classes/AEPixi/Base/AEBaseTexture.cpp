//
//  AEBaseTexture.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//


#include "AENode.h"
#include "AEPixi.h"
#include "AEBaseImage.h"
#include "AEBaseTexture.h"

_ae_synthesize(AEBaseTexture, AESize,    Size,          size);
_ae_synthesize(AEBaseTexture, GLint,     SavedId,       savedId);
_ae_synthesize(AEBaseTexture, GLuint,    TextureId,     textureId);
_ae_synthesize(AEBaseTexture, GLuint,    FrameBufferId, frameBufferId);
_ae_synthesize(AEBaseTexture, GLenum,    Format,        format);
_ae_synthesize(AEBaseTexture, GLboolean, Valid,         valid);


AEBaseTexture::~AEBaseTexture() {
    deleteTexture();
}
AEBaseTexture::AEBaseTexture(std::string pathfile): AEBaseTexture() {
    AEBaseImage png(pathfile);
    _size = png.getSize();
    create(GL_TEXTURE_2D, GL_RGBA, png.getBytes());
}
AEBaseTexture::AEBaseTexture(AESize size, GLuint fbo): AEBaseTexture() {
    _size = size;
    _frameBufferId = fbo;
    create(GL_TEXTURE_2D, GL_RGBA, NULL);
}
AEBaseTexture::AEBaseTexture(AESize size, GLvoid* pixels): AEBaseTexture() {
    _size = size;
    create(GL_TEXTURE_2D, GL_RGBA, pixels);
}

GLvoid AEBaseTexture::setFilter(GLenum filter) {
    params[AETextureParamMagFilter] = filter;
    params[AETextureParamMinFilter] = filter;
    bindParameters(GL_TEXTURE_2D);
}
GLvoid* AEBaseTexture::pixels(AERect frame) {
    GLint  boundFrameBuffer = 0;
    GLuint tempFramebuffer  = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &boundFrameBuffer);
    if (_frameBufferId == 0) {
        glGenFramebuffers(1, &tempFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, tempFramebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
    }
    
    GLvoid* pixels = malloc(frame.width * frame.height * GetBytesPerPixel(GL_UNSIGNED_BYTE, _format));
    glReadPixels(frame.x, frame.y, frame.width, frame.height, _format, GL_UNSIGNED_BYTE, pixels);
    glBindFramebuffer(GL_FRAMEBUFFER, boundFrameBuffer);
    if (_frameBufferId == 0) {
        glDeleteFramebuffers(1, &tempFramebuffer);
    }
    return pixels;
}

// --------------------------------Priate_Methods-------------------------------------------
AEBaseTexture::AEBaseTexture() {
    _size    = {0, 0};
    _savedId = _textureId = _frameBufferId = 0;
    _format  = GL_RGBA;
    _valid   = GL_FALSE;
}
GLvoid AEBaseTexture::bindTexture() {
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &_savedId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}

GLvoid AEBaseTexture::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, _savedId);
}

GLvoid AEBaseTexture::deleteTexture() {
    if (_textureId) {
        glDeleteTextures(1, &_textureId);
        _textureId = 0;
    }
}

GLvoid AEBaseTexture::bindParameters(GLenum type) {
    glBindTexture(type, _textureId);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, params[AETextureParamMagFilter]);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, params[AETextureParamMinFilter]);
    glTexParameteri(type, GL_TEXTURE_WRAP_S,     params[AETextureParamWrapS]);
    glTexParameteri(type, GL_TEXTURE_WRAP_T,     params[AETextureParamWrapT]);
}

GLvoid AEBaseTexture::create(GLenum type, GLenum texFormat, GLvoid* pixels) {
    deleteTexture();
    
    params[AETextureParamMagFilter] = GL_LINEAR;
    params[AETextureParamMinFilter] = GL_LINEAR;
    params[AETextureParamWrapS]     = GL_CLAMP_TO_EDGE;
    params[AETextureParamWrapT]     = GL_CLAMP_TO_EDGE;
    
    GLint maxTextureSize = AEPixi::sharedInstance()->maxTextureSize();
    if (_size.width > maxTextureSize || _size.height > maxTextureSize) {
        fprintf(stderr, "Warning: ImageWidth %f larger than MAX_TEXTURE_SIZE (%d)", _size.width, maxTextureSize);
        return;
    }
    
    _valid  = GL_TRUE;
    _format = texFormat;
    GLint  savedTextureId = 0;
    GLenum savedType = (type == GL_TEXTURE_2D ? GL_TEXTURE_BINDING_2D : GL_TEXTURE_BINDING_CUBE_MAP);
    glGetIntegerv(savedType, &savedTextureId);
    
    glGenTextures(1, &_textureId);
    glBindTexture(type, _textureId);
    glTexImage2D(type, 0, _format, _size.width, _size.height, 0, _format, GL_UNSIGNED_BYTE, pixels);
    bindParameters(type);
    glBindTexture(type, savedTextureId);
}
