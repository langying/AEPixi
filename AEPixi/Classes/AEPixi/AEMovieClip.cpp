//
//  AEMovieClip.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/3.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEMovieClip.h"

_ae_synthesize(AEMovieClip, GLboolean, Loop,           loop);
_ae_synthesize(AEMovieClip, GLboolean, Playing,        playing);
_ae_synthesize(AEMovieClip, GLfloat,   CurrentTime,    currentTime);
_ae_synthesize(AEMovieClip, GLfloat,   AnimationSpeed, animationSpeed);

AEMovieClip::~AEMovieClip() {
    
}

AEMovieClip::AEMovieClip(AETextureList& textureList): AESprite(textureList[0]) {
    _loop           = GL_TRUE;
    _playing        = GL_FALSE;
    _currentTime    = 0;
    _animationSpeed = 1;
    for (AETexture* texture : textureList) {
        textures.push_back(texture);
    }
}

GLuint AEMovieClip::totalFrames() {
    return (GLuint)textures.size();
}

GLuint AEMovieClip::currentFrame() {
    return (GLuint)_currentTime % textures.size();
}

GLvoid AEMovieClip::stop() {
    _playing = GL_FALSE;
}

GLvoid AEMovieClip::play() {
    _playing = GL_TRUE;
}

GLvoid AEMovieClip::gotoAndStop(GLuint frameNumber) {
    stop();
    _currentTime = frameNumber;
    _texture     = textures[currentFrame()];
}

GLvoid AEMovieClip::gotoAndPlay(GLuint frameNumber) {
    _currentTime = frameNumber;
    play();
}

GLvoid AEMovieClip::applyRender(AERenderer* renderer) {
    _currentTime = _currentTime + _animationSpeed * renderer->deltaTime();
    _texture = textures[((GLuint)_currentTime) % textures.size()];
    AESprite::applyRender(renderer);
}

GLvoid AEMovieClip::applyTransform(AENode* parent) {
    AESprite::applyTransform(parent);
}
