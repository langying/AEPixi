//
//  AEBaseTexture.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEBaseTexture__
#define __AEPixi__AEBaseTexture__

#include "AECommon.h"

typedef enum {
    AETextureParamMagFilter,
    AETextureParamMinFilter,
    AETextureParamWrapS,
    AETextureParamWrapT,
    AETextureParamSize
} AETextureParam;

class AENode;
class AEBaseTexture {
    
    _ae_property(AESize,    Size,          size);
    _ae_property(GLint,     SavedId,       savedId);
    _ae_property(GLuint,    TextureId,     textureId);
    _ae_property(GLuint,    FrameBufferId, frameBufferId);
    _ae_property(GLenum,    Format,        format);
    _ae_property(GLboolean, Valid,         valid);
    
public:
    virtual ~AEBaseTexture();
    AEBaseTexture(std::string pathfile);
    AEBaseTexture(AESize size, GLuint  fbo);
    AEBaseTexture(AESize size, GLvoid* pixels);
    
    GLvoid  setFilter(GLenum filter);
    GLvoid* pixels(AERect frame);
protected:
    AEBaseTexture();
    GLvoid bindTexture();
    GLvoid unbindTexture();
    GLvoid deleteTexture();
    GLvoid bindParameters(GLenum type);
    GLvoid create(GLenum type, GLenum texFormat, GLvoid* data);
    
    GLint params[AETextureParamSize];
};

#endif /* defined(__AEPixi__AEBaseTexture__) */
