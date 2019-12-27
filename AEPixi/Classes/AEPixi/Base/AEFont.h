//
//  AEFont.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/14.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEFont__
#define __AEPixi__AEFont__

#include "AECommon.h"
#include "ft2build.h"
#include FT_STROKER_H
#include FT_FREETYPE_H

class AEFont {
public:
    _ae_property(FT_Face, Face,      face);
    _ae_property(String,  Pathfile,  pathfile);
    _ae_property(GLuint,  FontSize,  fontSize);
    _ae_property(GLuint,  FontColor, fontColor);
    
public:
    ~AEFont();
    AEFont(String& pathfile);
    
    GLbool setupFont();
    GLint* kerningForText(std::u16string& text);
    GLvoid drawTextToBitmap(AEBitmap& image, String& text);
    GLvoid drawGlyphToBitmap(AEBitmap& image, FT_Bitmap& bitmap, GLint x, GLint y);
    
public:
    static GLbool setup();
    static GLvoid close();
    static FT_Library ftLibrary();
    static AEFont* create(String name);
    
    static FT_Library _ftLibrary;
    static std::map<String, AEData> fonts;
};

#endif /* defined(__AEPixi__AEFont__) */
