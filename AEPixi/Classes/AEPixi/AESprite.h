//
//  AESprite.h
//  TBBusiness
//
//  Created by hanqiong on 15/1/16.
//  Copyright (c) 2015年 Taobao. All rights reserved.
//

#ifndef __AEPixi__AESprite__
#define __AEPixi__AESprite__

#include "AENode.h"
#include "AETexture.h"

class AESprite: public AENode {
public:
    _ae_property(GLuint,     Tint,          tint);
    _ae_property(GLuint,     CachedTint,    cachedTint);
    _ae_property(AETexture*, Texture,       texture);
    _ae_property(AETexture*, TintedTexture, tintedTexture);
    
public:
    ~AESprite();
    AESprite(AETexture* texture);
    GLbool isValid();
    GLvoid applyRender(AERenderer* renderer);
    AERect toBounds(AETransform& transform);
    
protected:
    AESprite();
};

#endif /* defined(__AEPixi__AESprite__) */
