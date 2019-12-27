//
//  AEPixi.cpp
//  AEPixi
//
//  Created by 欧元蓉 on 14/12/27.
//  Copyright (c) 2014年 Taobao. All rights reserved.
//

#include "json.h"
#include "AEPixi.h"

using namespace std;

_ae_synthesize(AEPixi, string, Basepath,  basepath);
_ae_synthesize(AEPixi, string, FontPath,  fontPath);
_ae_synthesize(AEPixi, string, Pixifile,  pixifile);
_ae_synthesize(AEPixi, string, Cachepath, cachepath);

_ae_synthesize(AEPixi, GLlong, Last, last);
_ae_synthesize(AEPixi, GLuint, Time, time);


AEPixi* AEPixi::sharedInstance() {
    static AEPixi* instance = nullptr;
    if (instance == nullptr) {
        instance = new AEPixi();
    }
    return instance;
}

AEPixi::~AEPixi() {
    for (map<string, AEBaseTexture*>::iterator it = _baseTextures.begin(); it != _baseTextures.end(); ++it) {
        delete it->second;
    }
    _textures.clear();
    _baseTextures.clear();
}

AEPixi::AEPixi() {
    _time = 0;
    _last = AECurrentTime();
    _fontPath = "/System/Library/Fonts/";
    glGetIntegerv(GL_DEPTH_BITS,                     &_depthBits);
    glGetIntegerv(GL_STENCIL_BITS,                   &_stencilBits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,               &_maxTextureSize);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,             &_maxVertexAttribs);
    glGetIntegerv(GL_MAX_VARYING_VECTORS,            &_maxVaryingVectors);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,        &_maxTextureImageUnits);	
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS,     &_maxVertexUniformVectors);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS,   &_maxFragmentUniformVectors);
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_maxVertexTextureImageUnits);
    _isPackedDepthStencil = strstr((const char*)glGetString(GL_EXTENSIONS), "GL_OES_packed_depth_stencil") != 0;
}

GLvoid AEPixi::addResource(string& filename) {
    _resources.push_back(filename);
}
GLvoid AEPixi::loadAllResouces() {
    for (string name : _resources) {
        string ext  = AEURLExt(name);
        if (ext == "jpg") {
        }
        else if (ext == "png") {
        }
        else if (ext == "json") {
            loadJsonTexture(name);
        }
        else if (ext == "xml") {
        }
        else {
            fprintf(stderr, "[AEPixi::%s] unsupport resource(%s)", __func__, name.c_str());
        }
    }
}
GLvoid AEPixi::loadJsonTexture(string& filename) {
    string pathfile = this->pathfile(filename);
    AEData file = AEDataWithPathfile(pathfile);
    string JSONString(file.bytes);
    
    Json::Value json;
    Json::Reader reader;
    if (!reader.parse(JSONString, json)) {
        free(file.bytes);
        return;
    }
    if (json.isMember("frames") && json.isMember("meta")) {
        string image = json["meta"]["image"].asString();
        AEBaseTexture* baseTexture = _baseTextures[image];
        if (baseTexture == nullptr) {
            baseTexture = new AEBaseTexture(this->pathfile(image));
            _baseTextures[image] = baseTexture;
        }
        Json::Value frames = json["frames"];
        Json::Value::Members names = frames.getMemberNames();
        for (Json::Value::Members::iterator it = names.begin(); it != names.end(); it++) {
            string name = *it;
            Json::Value infos = frames[name];
            Json::Value frame = infos["frame"];
            Json::Value sizes = infos["sourceSize"];
            Json::Value trims = infos["spriteSourceSize"];
            
            AESize SIZE = { sizes["w"].asFloat(), sizes["h"].asFloat() };
            AERect CROP = { frame["x"].asFloat(), frame["y"].asFloat(), frame["w"].asFloat(), frame["h"].asFloat() };
            AERect TRIM = { trims["x"].asFloat(), trims["y"].asFloat(), trims["w"].asFloat(), trims["h"].asFloat() };
            _textures[name] = new AETexture(baseTexture, SIZE, CROP, TRIM);
        }
    }
    free(file.bytes);
}
AETexture* AEPixi::textureWithFrame(string& frame) {
    AETexture* texture = _textures[frame];
    if (texture == nullptr) {
        fprintf(stderr, "%s.%s frame[%s] not exist!", __FILE__, __func__, frame.c_str());
    }
    return texture;
}
AETexture* AEPixi::textureWithImage(string& image) {
    AETexture* texture = _textures[image];
    if (texture == nullptr) {
        AEBaseTexture* baseTexture = _baseTextures[image];
        if (baseTexture == nullptr) {
            baseTexture = new AEBaseTexture(pathfile(image));
            _baseTextures[image] = baseTexture;
        }
        texture = new AETexture(baseTexture);
        _textures[image] = texture;
    }
    return texture;
}
string AEPixi::pathfile(string& filename) {
    return _basepath + filename;
}


GLint AEPixi::depthBits() {
    return _depthBits;
}
GLint AEPixi::stencilBits() {
    return _stencilBits;
}
GLint AEPixi::maxTextureSize() {
    return _maxTextureSize;
}
GLint AEPixi::maxVertexAttribs() {
    return _maxVertexAttribs;
}
GLint AEPixi::maxVaryingVectors() {
    return _maxVaryingVectors;
}
GLint AEPixi::maxTextureImageUnits() {
    return _maxTextureImageUnits;
}
GLint AEPixi::maxVertexUniformVectors() {
    return _maxVertexUniformVectors;
}
GLint AEPixi::maxFragmentUniformVectors() {
    return _maxFragmentUniformVectors;
}
GLint AEPixi::maxVertexTextureImageUnits() {
    return _maxVertexTextureImageUnits;
}
GLbool AEPixi::isPackedDepthStencil() {
    return _isPackedDepthStencil;
}
