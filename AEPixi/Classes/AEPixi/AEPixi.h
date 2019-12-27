//
//  AEPixi.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 14/12/27.
//  Copyright (c) 2014年 Taobao. All rights reserved.
//

#ifndef __AEPixi_AEPixi__
#define __AEPixi_AEPixi__

#include "AECommon.h"
#include "AETexture.h"

class AEPixi {
public:
    _ae_property(std::string, Basepath,  basepath);
    _ae_property(std::string, FontPath,  fontPath);
    _ae_property(std::string, Pixifile,  pixifile);
    _ae_property(std::string, Cachepath, cachepath);
    
    _ae_property(GLlong, Last, last);
    _ae_property(GLuint, Time, time);
    
    _ae_readonly(GLint,   depthBits);             // 深度缓存面的数量
    _ae_readonly(GLint,   stencilBits);           // 模版缓存面的数量
    _ae_readonly(GLint,   maxTextureSize);        // 纹理的最大尺寸
    _ae_readonly(GLint,   maxVertexAttribs);      // 顶点属性的最大数量
    _ae_readonly(GLint,   maxVaryingVectors);     // 可变向量的最大数量
    _ae_readonly(GLint,   maxTextureImageUnits);  // 在一个片段着色器上纹理单元的最大数量
    _ae_readonly(GLint,   maxVertexUniformVectors);   // 统一顶点向量的最大数量
    _ae_readonly(GLint,   maxFragmentUniformVectors); // 统一片段向量的最大数量
    _ae_readonly(GLint,   maxVertexTextureImageUnits);// 在一个顶点着色器上纹理单元的最大数量
    _ae_readonly(GLbool,  isPackedDepthStencil);     // 是否支持深度和模板缓存共享数据缓存
    
public:
    static AEPixi* sharedInstance();
    ~AEPixi();
    AEPixi();
    
    GLvoid     addResource(std::string& filename);
    GLvoid     loadAllResouces();
    GLvoid     loadJsonTexture(std::string& pathfile);
    std::string pathfile(std::string& filename);
    
    AETexture* textureWithFrame(std::string& frame);
    AETexture* textureWithImage(std::string& image);
    
protected:
    std::vector<std::string>              _resources;    // 可以理解为Loader
    std::map<std::string, AETexture*>     _textures;     // 全局的纹理缓存
    std::map<std::string, AEBaseTexture*> _baseTextures; // 全局的纹理缓存
};

#endif /* defined(__AEPixi_AEPixi__) */
