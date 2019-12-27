//
//  AETexture.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AETexture.h"

using namespace std;

_ae_synthesize(AETexture, AESize,         Size,        size);
_ae_synthesize(AETexture, AERect,         Crop,        crop);
_ae_synthesize(AETexture, AERect,         Trim,        trim);
_ae_synthesize(AETexture, AEBaseTexture*, BaseTexture, baseTexture);

AETexture::~AETexture() {
}

AETexture::AETexture() {
    _size = AESizeZero;
    _crop = _trim = AERectZero;
    _baseTexture = nullptr;
}

AETexture::AETexture(AEBaseTexture* baseTexture): AETexture() {
    _baseTexture = baseTexture;
    _size = baseTexture->getSize();
    _crop = AERectMake(0, 0, _size.width, _size.height);
    _trim = AERectMake(0, 0, _size.width, _size.height);
}
AETexture::AETexture(AEBaseTexture* baseTexture, AESize size, AERect crop, AERect trim): AETexture() {
    _baseTexture = baseTexture;
    _size = size;
    _crop = crop;
    _trim = trim;
}

GLfloat AETexture::getWidth() {
    return _size.width;
}
GLvoid AETexture::setWidth(GLfloat width) {
    _size.width = width;
}
GLfloat AETexture::getHeight() {
    return _size.height;
}
GLvoid AETexture::setHeight(GLfloat height) {
    _size.height = height;
}