//
//  AERope.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AERope__
#define __AEPixi__AERope__

#include "AENode.h"
#include "AETexture.h"

class AERope: public AENode {
public:
    _ae_property(GLuint,   Size,   size);
    _ae_property(AEPoint*, PTs,    pts);
    _ae_property(AEPoint*, UVs,    uvs);
    _ae_property(AETexture*, Texture, texture);
    
public:
    ~AERope();
    AERope();
    AERope(AETexture* texture, AEPointList& points);
    
public:
    GLbool valid();
    GLvoid update(AEPointList& points);
    GLvoid applyRender(AERenderer* renderer);
};

#endif /* defined(__AEPixi__AERope__) */
