//
//  AEFont.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/14.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEFont.h"
#include "AEPixi.h"
#include "ft2build.h"

using namespace std;

_ae_synthesize(AEFont, FT_Face, Face,      face);
_ae_synthesize(AEFont, String,  Pathfile,  pathfile);
_ae_synthesize(AEFont, GLuint,  FontSize,  fontSize);
_ae_synthesize(AEFont, GLuint,  FontColor, fontColor);

FT_Library AEFont::_ftLibrary;
map<String, AEData> AEFont::fonts;

AEFont::~AEFont() {
    if (_face) {
        FT_Done_Face(_face);
        _face = nullptr;
    }
}

AEFont::AEFont(string& pathfile) {
    _pathfile = pathfile;
}

GLbool AEFont::setupFont() {
    GLboolean success = GL_FALSE;
    do {
        map<string, AEData>::iterator it = fonts.find(_pathfile);
        if (it == fonts.end()) {
            AEData data = AEDataWithPathfile(_pathfile);
            _ae_break(data.size <= 0);
            fonts[_pathfile] = data;
        }
        
        FT_Long  size = (FT_Long )fonts[_pathfile].size;
        FT_Byte* buff = (FT_Byte*)fonts[_pathfile].bytes;
        
        _ae_break(FT_New_Memory_Face(ftLibrary(), buff, size, 0, &_face));
        _ae_break(FT_Select_Charmap(_face, FT_ENCODING_UNICODE));
        _ae_break(FT_Set_Char_Size(_face, _fontSize << 6, 0, 72, 0));
        success = GL_TRUE;
    } while (0);
    
    return success;
}

GLint* AEFont::kerningForText(u16string& text) {
    if (!_face || text.length() <= 0) {
        return nullptr;
    }
    
    size_t count = text.length();
    GLint* sizes = (GLint*)calloc(count, sizeof(GLint));
    if (FT_HAS_KERNING(_face)) {
        return sizes;
    }
    for (size_t i = 1; i < count; ++i) {
        do {
            GLint index1 = FT_Get_Char_Index(_face, text[i-1]);
            if (!index1) {
                break;
            }
            GLint index2 = FT_Get_Char_Index(_face, text[i]);
            if (!index2) {
                break;
            }
            
            FT_Vector kerning;
            if (FT_Get_Kerning(_face, index1, index2, FT_KERNING_DEFAULT, &kerning)) {
                break;
            }
            sizes[i] = (GLint)(kerning.x >> 6);
        } while(0);
    }
    return sizes;
}

GLvoid AEFont::drawTextToBitmap(AEBitmap& image, string& text) {
    GLuint x = 0, y = 0;
    u16string word = AEU16StringFromStdString(text);
    for (size_t i = 0, length = word.length(); i < length; i++) {
        do {
            _ae_break(!_face);
            _ae_break(FT_Load_Char(_face, word[i], FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING));
            drawGlyphToBitmap(image, _face->glyph->bitmap, x, y);
            x += (_face->glyph->advance.x >> 6);
        } while (0);
    }
}

GLvoid AEFont::drawGlyphToBitmap(AEBitmap& image, FT_Bitmap& bitmap, GLint x, GLint y) {
    AEColor  color;
    GLfloat  alpha;
    GLint    maxX = x + bitmap.width;
    GLint    maxY = y + bitmap.rows;
    GLuint*  dest = image.bytes;
    GLuchar* buff = bitmap.buffer;
    for (GLint i = x, p = 0; i < maxX; i++, p++) {
        for (GLint j = y, q = 0; j < maxY; j++, q++) {
            if (i >= 0 && j >= 0 && i < image.width && j < image.height) {
                color = { dest[i + image.width * j] };
                alpha = buff[p + bitmap.width * q] / 255.0;
                color.rgba.r *= alpha;
                color.rgba.g *= alpha;
                color.rgba.b *= alpha;
            }
        }
    }
}

GLbool AEFont::setup() {
    if (_ftLibrary == nullptr) {
        if (FT_Init_FreeType(&_ftLibrary)) {
            _ftLibrary = nullptr;
        }
    }
    return _ftLibrary != nullptr;
}

GLvoid AEFont::close() {
    if (_ftLibrary) {
        FT_Done_FreeType(_ftLibrary);
        _ftLibrary = nullptr;
    }
}
FT_Library AEFont::ftLibrary() {
    setup();
    return _ftLibrary;
}

AEFont* AEFont::create(string name) {
    string pathfile = AEPixi::sharedInstance()->basepath() + name;
    AEFont* font = new AEFont(pathfile);
    if (font->setupFont()) {
        return font;
    }
    delete font;
    return nullptr;
}
