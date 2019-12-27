//
//  AECommon.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/22.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AECommon__
#define __AEPixi__AECommon__

#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <map>
#include <vector>
#include <ostream>


#ifdef __ANDROID__
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <jni.h>
    #include <android/log.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #define _ae_log(tag, msg) __android_log_print(ANDROID_LOG_WARN, tag, msg);
#else
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
    #define _ae_log(tag, msg) fprintf(stderr, "[##tag## %s]:%s", __func__, msg);
#endif

#define BlueColor       0x0000FFFF
#define GrayColor       0x808080FF
#define BlackColor      0x000000FF
#define ClearColor      0x00000000
#define GreenColor      0x00FF00FF
#define WhiteColor      0xFFFFFFFF
#define LightBlueColor  0x2A75E6FF
#define LightGrayColor  0xAAAAAAFF
#define LightGreenColor 0x1AC382FF
#define LightWhiteColor 0xFBFBFBFF

#ifndef BIG_ENDIAN
#if (('1234' >> 24) == '1')
#elif (('4321' >> 24) == '1')
    #define BIG_ENDIAN
#else
    #error "Couldn't determine the endianness!"
#endif
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif

#define _ae_readonly(Type, name)\
protected: \
Type _##name; \
public: \
Type name()

#define _ae_property(Type, Name, name)\
protected: \
Type _##name; \
public: \
Type name(); \
Type get##Name(); \
void set##Name(Type name) 

#define _ae_synthesize(Class, Type, Name, name) \
Type Class::name() { \
    return _##name; \
} \
Type Class::get##Name() { \
    return _##name; \
} \
void Class::set##Name(Type name) { \
    _##name = name;\
}

#define _ae_break(cond) if(cond){break;}
#define _ae_free(ptr)   if(ptr){free(ptr);ptr=nullptr;}
#define _ae_delete(ptr) if(ptr){delete(ptr);ptr=nullptr;}

extern const GLchar* Shader_Vertex;
extern const GLchar* Shader_Flat;
extern const GLchar* Shader_Pattern;
extern const GLchar* Shader_Texture;
extern const GLchar* Shader_Gradient;
extern const GLchar* Shader_AlphaTextures;

extern const GLchar* TilingShader;
extern const GLchar* TilingFragment;

GLuint GetBytesPerPixel(GLenum type, GLenum format);

typedef std::string    String;
typedef std::u16string UString;
typedef GLboolean      GLbool;
typedef long           GLlong;
typedef unsigned long  GLulong;
typedef unsigned char  GLuchar;
typedef double         GLdouble;

typedef struct _AEData {
    _AEData() { size  = 0; bytes = nullptr; }
    GLuint  size;
    GLchar* bytes;
} AEData;

typedef struct _AERect {
    GLfloat x, y, width, height;
} AERect;

typedef struct _AESize {
    GLfloat width, height;
} AESize;

typedef struct _AEPoint {
    GLfloat x, y;
} AEPoint;

typedef AEPoint AEVector;

typedef union _AEColor {
    GLuint  hex;
    GLuchar components[4];
    struct {
#ifdef BIG_ENDIAN
        GLuchar a, r, g, b;
#else
        GLuchar b, g, r, a;
#endif
    } rgba;
} AEColor;

typedef struct _AEVertex {
    AEVector pt;
    AEVector uv;
    AEColor color;
} AEVertex;

typedef struct _AETransform {
    GLfloat a, b, c, d, tx, ty;
} AETransform;

typedef struct _AEBitmap {
    GLuint* bytes;
    GLuint width, height;
} AEBitmap;

typedef std::vector<AEPoint> AEPointList;

const AESize  AESizeZero  = {0, 0};
const AERect  AERectZero  = {0, 0, 0, 0};
const AEPoint AEPointZero = {0, 0};
const AETransform AETransformIdentity = {1, 0, 0, 1, 0, 0};

static inline AESize AESizeMake(GLfloat w, GLfloat h) {
    AESize size = {w, h};
    return size;
}
static inline AEPoint AEPointMake(GLfloat x, GLfloat y) {
    AEPoint pt = {x, y};
    return pt;
}
static inline GLfloat AEPointLength(AEPoint& pt1, AEPoint& pt2) {
    GLfloat dx = pt2.x - pt1.x;
    GLfloat dy = pt2.y - pt1.y;
    return sqrtf(dx*dx + dy*dy);
}
static inline AEPoint AEPointMiddle(AEPoint& pt1, AEPoint& pt2) {
    return { pt1.x + (pt2.x - pt1.x) / 2, pt1.y + (pt2.y - pt1.y) / 2};
}
static inline GLbool AEPointIsEqual(AEPoint& pt1, AEPoint& pt2) {
    return pt1.x == pt2.x && pt1.y == pt2.y;
}
static inline AEPoint AEPointPerp(AEPoint& pt1, AEPoint& pt2, GLuint& width) {
    GLfloat x = -(pt1.y - pt2.y);
    GLfloat y =  (pt1.x - pt2.x);
    GLfloat d = sqrt(x*x + y*y);
    return {x/d*width/2, y/d*width/2};
}
static inline AEVector AEVectorMake(GLfloat x, GLfloat y) {
    AEVector vector = {x, y};
    return vector;
}
static inline AERect AERectMake(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    AERect rect = {x, y, width, height};
    return rect;
}

static inline GLboolean AETransformIsIdentity(AETransform& t) {
    return t.a == 1 && t.b == 0 && t.c == 0 && t.d == 1 && t.tx == 0 && t.ty == 0;
}
static inline GLboolean AETransformIsNotIdentity(AETransform& t) {
    return !(t.a == 1 && t.b == 0 && t.c == 0 && t.d == 1 && t.tx == 0 && t.ty == 0);
}
static inline AETransform AETransformScale(AETransform& t, AEPoint& pt) {
    AETransform transform = t;
    transform.a  *= pt.x;
    transform.d  *= pt.y;
    transform.c  *= pt.x;
    transform.b  *= pt.y;
    transform.tx *= pt.x;
    transform.ty *= pt.y;
    return transform;
}
static inline AETransform AETransformConcat(AETransform& t1, AETransform& t2) {
    AETransform transform;
    transform.a  = t2.a  * t1.a + t2.b  * t1.c;
    transform.b  = t2.a  * t1.b + t2.b  * t1.d;
    transform.c  = t2.c  * t1.a + t2.d  * t1.c;
    transform.d  = t2.c  * t1.b + t2.d  * t1.d;
    transform.tx = t2.tx * t1.a + t2.ty * t1.c + t1.tx;
    transform.ty = t2.tx * t1.b + t2.ty * t1.d + t1.ty;
    return transform;
}
static inline AETransform AETransformInvert(AETransform& t) {
    AETransform transform;
    GLfloat value = t.a * t.d - t.b * t.c;
    transform.a  =  t.d / value;
    transform.b  = -t.b / value;
    transform.c  = -t.c / value;
    transform.d  =  t.a / value;
    transform.tx =  (t.c * t.ty - t.d * t.tx) / value;
    transform.ty = -(t.a * t.ty - t.b * t.tx) / value;
    return transform;
}
static inline AETransform AETransformRotate(AETransform& t, GLfloat angle) {
    GLfloat cr = cos(angle);
    GLfloat sr = sin(angle);
    
    AETransform transform;
    transform.a  = t.a  * cr - t.b  * sr;
    transform.b  = t.a  * sr + t.b  * cr;
    transform.c  = t.c  * cr - t.d  * sr;
    transform.d  = t.c  * sr + t.d  * cr;
    transform.tx = t.tx * cr - t.ty * sr;
    transform.ty = t.tx * sr + t.ty * cr;
    return transform;
}
static inline AETransform AETransformTranslate(AETransform& t, AEPoint& pt) {
    AETransform transform = t;
    transform.tx += pt.x;
    transform.ty += pt.y;
    return transform;
}
static inline AEVector AEVectorApplyTransform(AEVector p, AETransform& t) {
    AEVector pt = {
        t.a * p.x + t.c * p.y + t.tx,
        t.b * p.x + t.d * p.y + t.ty
    };
    return pt;
}
static inline AEVector AEVectorApplyInvertTransform(AEVector p, AETransform& t) {
    GLfloat value = 1 / (t.a * t.d - t.c * t.b);
    AEVector pt = {
        t.d * value * p.x - t.c * value * p.y + ( t.ty * t.c - t.tx * t.d) * value,
        t.a * value * p.y - t.b * value * p.x + (-t.ty * t.a + t.tx * t.b) * value
    };
    return pt;
}

/**
 * http://www.opengl.org/wiki/OpenGL_Error
 * 0x0500, GL_INVALID_ENUM
 * 0x0501, GL_INVALID_VALUE
 * 0x0502, GL_INVALID_OPERATION
 * 0x0503, GL_STACK_OVERFLOW
 * 0x0504, GL_STACK_UNDERFLOW
 * 0x0505, GL_OUT_OF_MEMORY
 * 0x0506, GL_INVALID_FRAMEBUFFER_OPERATION
 * 0x8031, GL_TABLE_TOO_LARGE​1
 */
static inline GLvoid CheckGlError() {
    for (GLint error = glGetError(); error != 0; error = glGetError()) {
        fprintf(stderr, "glError: 0x%x\n", error);
    }
}
static inline GLvoid CheckGlError(const char* msg) {
    GLint error;
    for (error = glGetError(); error; error = glGetError()) {
        fprintf(stderr, "after %s() glError (0x%x)\n", msg, error);
    }
}
static inline GLvoid PrintGLString(const char* name, GLenum s) {
    const char*v = (const char*) glGetString(s);
    fprintf(stderr, "GL %s = %s\n", name, v);
}

GLlong AECurrentTime(); // 从1970开始的毫秒
GLbool AEURLIsWeb(std::string& url);
GLulong AEHashCode(std::string& str);

std::string AEURLExt(std::string& url);
std::string AEURLPath(std::string& url);
std::string AEURLName(std::string& url);
std::string AEURLScheme(std::string& url);
std::string AEHashString(std::string& url);
std::u16string AEU16StringFromStdString(std::string& source);

AEData AEDataWithPathfile(std::string& pathfile);
GLbool AEFileIsAbsolutePath(std::string& pathfile);

#endif /* defined(__AEPixi__AECommon__) */
