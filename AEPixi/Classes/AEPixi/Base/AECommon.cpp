//
//  AECommon.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/22.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AECommon.h"
#include "ANManager.h"

const GLchar* Shader_Vertex = ""
"attribute vec2 pt;"
"attribute vec2 uv;"
"attribute vec4 color;"
"varying highp vec2 vUv;"
"varying lowp  vec4 vColor;"
"uniform highp vec2 uScreen;"
"void main() {"
"   vUv         = uv;"
"   vColor      = color;"
"   gl_Position = vec4(pt * (vec2(2, -2) / uScreen) + vec2(-1.0, 1.0), 0.0, 1.0);"
"}";
const GLchar* Shader_Flat = ""
"varying lowp vec4 vColor;"
"varying highp vec2 vUv;"
"void main() {"
"    gl_FragColor = vColor;"
"}";
const GLchar* Shader_Pattern = ""
"varying lowp vec4 vColor;"
"varying highp vec2 vUv;"
"uniform sampler2D texture;"
"void main() {"
"    gl_FragColor = texture2D(texture, mod(vUv, vec2(1.0, 1.0)) ) * vColor;"
"}";
const GLchar* Shader_Texture = ""
"varying highp vec2 vUv;"
"varying lowp  vec4 vColor;"
"uniform sampler2D uTexture;"
"void main() {"
"    gl_FragColor = texture2D(uTexture, vUv) * vColor;"
"}";
const GLchar* Shader_Gradient = ""
"precision highp float;"
"varying highp vec2 vUv;"
"varying lowp vec4 vColor;"
"uniform mediump vec3 inner; // x, y, z=radius"
"uniform mediump vec3 diff; // x, y, z=radius"
"uniform sampler2D texture;"
"void main() {"
"    vec2 p2 = vUv - inner.xy;"
"    float A = dot(diff.xy, diff.xy) - diff.z * diff.z;"
"    float B = dot(p2.xy, diff.xy) + inner.z * diff.z;"
"    float C = dot(p2, p2) - (inner.z * inner.z);"
"    float D = (B * B) - (A * C);"
"    float DA = sqrt(D) / A;"
"    float BA = B / A;"
"    float t = max(BA+DA, BA-DA);"
"    lowp float keep = sign(diff.z * t + inner.z); // discard if < 0.0"
"    gl_FragColor = texture2D(texture, vec2(t, 0.0)) * vColor * keep;"
"}";

const GLchar* Shader_AlphaTextures = ""
"varying lowp vec4 vColor;"
"varying highp vec2 vUv;"
"uniform sampler2D texture;"
"void main() {"
"    gl_FragColor = texture2D(texture, vUv).aaaa * vColor;"
"}";


const GLchar* TilingShader = ""
"precision lowp float;"
"attribute vec2 pt;"
"attribute vec2 uv;"
"attribute vec4 color;"
"varying highp vec2 vUv;"
"varying lowp  vec4 vColor;"
"uniform highp vec2 uScreen;"
"uniform highp vec4 uFrame;"
"uniform highp vec4 uTransform;"
"uniform highp vec2 uPixelSize;"
"void main(void){"
"   gl_Position = vec4(pt * (vec2(2, -2) / uScreen) + vec2(-1.0, 1.0), 0.0, 1.0);"
"   vec2 coord = uv;"
"   coord -= uTransform.xy;"
"   coord /= uTransform.zw;"
"   vUv    = coord;"
"   vColor = vec4(color.rgb * color.a, color.a);"
"}";
const GLchar* TilingFragment = ""
"precision lowp float;"
"varying highp vec2 vUv;"
"varying lowp  vec4 vColor;"
"uniform highp vec4 uFrame;"
"uniform highp vec2 uPixelSize;"
"uniform sampler2D uSampler;"
"void main(void){"
"   vec2 coord = mod(vUv, uFrame.zw);"
"   coord = clamp(coord, uPixelSize, uFrame.zw - uPixelSize);"
"   coord += uFrame.xy;"
"   gl_FragColor = texture2D(uSampler, coord) * vColor;"
"}";


GLuint GetBytesPerPixel(GLenum type, GLenum format) {
    int bytesPerComponent = 0;
    switch(type) {
        case GL_UNSIGNED_BYTE:
            bytesPerComponent = 1;
            break;
        case GL_FLOAT:
            bytesPerComponent = 4;
            break;
        case GL_HALF_FLOAT_OES:
            bytesPerComponent = 2;
            break;
        case GL_UNSIGNED_SHORT_5_6_5:
        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_5_5_5_1:
            return 2;
    }
    
    switch(format) {
        case GL_LUMINANCE:
        case GL_ALPHA:
            return 1 * bytesPerComponent;
        case GL_LUMINANCE_ALPHA:
            return 2 * bytesPerComponent;
        case GL_RGB:
            return 3 * bytesPerComponent;
        case GL_RGBA:
            return 4 * bytesPerComponent;
    }
    return 0;
}

GLlong AECurrentTime() {
    static struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
GLbool AEURLIsWeb(std::string& url) {
    std::string scheme = AEURLScheme(url);
    return scheme == "http" || scheme == "https";
}
GLulong AEHashCode(std::string& str) {
    std::hash<std::string> HASH;
    return HASH(str);
}

std::string AEURLExt(std::string& url) {
    size_t index = url.find_last_of(".");
    return index == std::string::npos ? "" : url.substr(index + 1);
}
std::string AEURLPath(std::string& url) {
    size_t index = url.find_last_of("/");
    return url.substr(0, index + 1);
}
std::string AEURLName(std::string& url) {
    size_t index = url.find_last_of("/") + 1;
    return url.substr(index, url.length());
}
std::string AEURLScheme(std::string& url) {
    size_t index = url.find("://");
    if (index == std::string::npos) {
        return "";
    }
    return url.substr(0, index);
}
std::string AEHashString(std::string& url) {
    char buff[32] = {0};
    GLulong code = AEHashCode(url);
    sprintf(buff, "%ld", code);
    return buff;
}

std::u16string AEU16StringFromStdString(std::string& source) {
    GLuint  length = (GLuint)source.length();
    GLchar* buffer = (GLchar*)source.c_str();
    
    unsigned ch;
    GLuint     indx = 0;
    GLchar*    buff = buffer;
    GLchar*    last = buffer + length;
    char16_t*  bytes = new char16_t[length + 1];
    
    for (indx = 0; buff < last; indx++) {
        if ((*buff & 0x80) == 0) {
            bytes[indx] = (*buff);
            ++buff;
        } else if ((*buff & 0x20) == 0) {
            ch = *buff & 0x1f;
            ++buff;
            ch <<= 6;
            ch += *buff & 0x3f;
            bytes[indx] = ch;
            ++buff;
        } else if ((*buff & 0x10) == 0) {
            ch = *buff & 0x0f;
            ++buff;
            ch <<= 6;
            ch += *buff & 0x3f;
            ++buff;
            ch <<= 6;
            ch += *buff & 0x3f;
            bytes[indx] = ch;
            ++buff;
        } else {
            bytes[indx] = 'X';
            buff += 4;
        }
    }
    bytes[length] = '\0';
    std::u16string ret = bytes;
    free(bytes);
    return ret;
}

AEData AEDataWithPathfile(std::string& pathfile) {
    AEData data;
    if (AEURLIsWeb(pathfile)) {
        ANManager* manager = ANManager::sharedInstance();
        ANRequest* request = ANRequest::create(pathfile, 3000, 5000);
        ANResponse* response = manager->sendSynchronousRequest(request);
        ANData* ret = response->getResponseData();
        data.size = (GLuint)ret->size();
        data.bytes = (GLchar*)malloc(data.size);
        memcpy(data.bytes, &(ret->front()), data.size);
        _ae_delete(request);
        _ae_delete(response);
        return data;
    }
    
    FILE* file = fopen(pathfile.c_str(), "rb");
    if (file == NULL) {
        return data;
    }
    fseek(file, 0, SEEK_END);
    data.size = (GLuint)ftell(file);
    fseek(file, 0, SEEK_SET);
    data.bytes = (GLchar*)malloc(sizeof(GLchar) * (data.size + 1));
    data.bytes[data.size] = '\0';
    fread(data.bytes, sizeof(GLchar), data.size, file);
    fclose(file);
    return data;
}

GLbool AEFileIsAbsolutePath(std::string& pathfile) {
    return pathfile[0] == '/';
}
