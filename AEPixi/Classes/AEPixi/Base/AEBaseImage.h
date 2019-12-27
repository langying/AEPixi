//
//  AEBaseImage.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/28.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEBaseImage__
#define __AEPixi__AEBaseImage__

#include "AECommon.h"

enum class AEFormat {
    //! auto detect the type
    AUTO,
    //! 32-bit texture: BGRA8888
    BGRA8888,
    //! 32-bit texture: RGBA8888
    RGBA8888,
    //! 24-bit texture: RGBA888
    RGB888,
    //! 16-bit texture without Alpha channel
    RGB565,
    //! 8-bit textures used as masks
    A8,
    //! 8-bit intensity texture
    I8,
    //! 16-bit textures used as masks
    AI88,
    //! 16-bit textures: RGBA4444
    RGBA4444,
    //! 16-bit textures: RGB5A1
    RGB5A1,
    //! 4-bit PVRTC-compressed texture: PVRTC4
    PVRTC4,
    //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
    PVRTC4A,
    //! 2-bit PVRTC-compressed texture: PVRTC2
    PVRTC2,
    //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
    PVRTC2A,
    //! ETC-compressed texture: ETC
    ETC,
    //! S3TC-compressed texture: S3TC_Dxt1
    S3TC_DXT1,
    //! S3TC-compressed texture: S3TC_Dxt3
    S3TC_DXT3,
    //! S3TC-compressed texture: S3TC_Dxt5
    S3TC_DXT5,
    //! ATITC-compressed texture: ATC_RGB
    ATC_RGB,
    //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
    ATC_EXPLICIT_ALPHA,
    //! ATITC-compresed texture: ATC_INTERPOLATED_ALPHA
    ATC_INTERPOLATED_ALPHA,
    //! Default texture format: AUTO
    DEFAULT = AUTO,
    
    NONE = -1
};

typedef unsigned char uchar;

class AEBaseImage {
public:
    _ae_property(GLint,     Width,              width);
    _ae_property(GLint,     Height,             height);
    _ae_property(size_t,    Length,             length);
    _ae_property(GLuchar*,  Bytes,              bytes);
    _ae_property(AEFormat,  Format,             format);
    _ae_property(GLboolean, PremultipliedAlpha, premultipliedAlpha);
public:
    ~AEBaseImage();
    AEBaseImage();
    AEBaseImage(std::string pathfile);
    AESize getSize();
protected:
    GLboolean initPNG(const GLuchar* data, size_t dataLen);
    GLvoid onPremultipliedAlpha();
};

#endif /* defined(__AEPixi__AEBaseImage__) */
