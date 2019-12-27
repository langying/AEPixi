//
//  AEText.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/14.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEText.h"
#include "AEPixi.h"

using namespace std;

string AEText::text() {
    return _text;
}
string AEText::getText() {
    return _text;
}
void AEText::setText(string text) {
    _text = text;
    updateTexture();
}
_ae_synthesize(AEText, AEFont*, Font, font);




AEText::~AEText() {
    _ae_delete(_texture);
}

AEText::AEText(string& text) {
    _text = text;
    _font = AEFont::create("STHeiti Medium.ttc");
    updateTexture();
}

GLvoid AEText::updateTexture() {
    AEBaseTexture* baseTexture = _texture ? _texture->baseTexture() : nullptr;
    _ae_delete(baseTexture);
    _ae_delete(_texture);
    
    AEBitmap bitmap;
    bitmap.width  = 200;
    bitmap.height = 100;
    bitmap.bytes  = (GLuint*)malloc(200 * 100 * sizeof(GLuint));
    AESize size   = AESizeMake(bitmap.width, bitmap.height);
    _font->drawTextToBitmap(bitmap, _text);
    setTexture(new AETexture(new AEBaseTexture(size, *(bitmap.bytes))));
    free(bitmap.bytes);
}
