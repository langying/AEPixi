//
//  AETexture.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AETexture__
#define __AEPixi__AETexture__

#include "AEBaseTexture.h"

class AETexture {
public:
    _ae_property(AESize,         Size,        size);
    _ae_property(AERect,         Crop,        crop);
    _ae_property(AERect,         Trim,        trim);
    _ae_property(AEBaseTexture*, BaseTexture, baseTexture);
    
public:
    ~AETexture();
    AETexture();
    AETexture(AEBaseTexture* baseTexture);
    AETexture(AEBaseTexture* baseTexture, AESize size, AERect crop, AERect trim);
    
    GLfloat getWidth();  GLvoid setWidth(GLfloat width);
    GLfloat getHeight(); GLvoid setHeight(GLfloat height);
    
protected:
};

#endif /* defined(__AEPixi__AETexture__) */
