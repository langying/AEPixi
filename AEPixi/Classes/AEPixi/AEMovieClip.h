//
//  AEMovieClip.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/3.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEMovieClip__
#define __AEPixi__AEMovieClip__

#include "AESprite.h"

typedef std::vector<AETexture*> AETextureList;

class AEMovieClip: public AESprite {
public:
    _ae_property(GLboolean, Loop,           loop);
    _ae_property(GLboolean, Playing,        playing);
    _ae_property(GLfloat,   CurrentTime,    currentTime);
    _ae_property(GLfloat,   AnimationSpeed, animationSpeed);

public:
    ~AEMovieClip();
    AEMovieClip(AETextureList& textureList);
    GLuint totalFrames();
    GLuint currentFrame();
    
    GLvoid stop();
    GLvoid play();
    GLvoid gotoAndStop(GLuint frameNumber);
    GLvoid gotoAndPlay(GLuint frameNumber);
    GLvoid applyRender(AERenderer* renderer);
    GLvoid applyTransform(AENode* parent);
    
protected:
    AETextureList textures;
};

#endif /* defined(__AEPixi__AEMovieClip__) */
