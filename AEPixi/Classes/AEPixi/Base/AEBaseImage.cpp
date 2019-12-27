//
//  AEBaseImage.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/28.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "png.h"
#include "pngconf.h"
#include "pnglibconf.h"
#include "AEBaseImage.h"

#define PNGSIGSIZE 8
#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

_ae_synthesize(AEBaseImage, GLint,     Width,              width);
_ae_synthesize(AEBaseImage, GLint,     Height,             height);
_ae_synthesize(AEBaseImage, size_t,    Length,             length);
_ae_synthesize(AEBaseImage, GLuchar*,  Bytes,              bytes);
_ae_synthesize(AEBaseImage, AEFormat,  Format,             format);
_ae_synthesize(AEBaseImage, GLboolean, PremultipliedAlpha, premultipliedAlpha);

typedef struct {
    const GLuchar* data;
    size_t size;
    size_t offset;
} tImageSource;
static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length) {
    tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);
    if ((isource->offset + length) <= isource->size) {
        memcpy(data, isource->data+isource->offset, length);
        isource->offset += length;
    }
    else {
        png_error(png_ptr, "pngReaderCallback failed");
    }
}

AEBaseImage::~AEBaseImage() {
    _ae_free(_bytes)
}

AEBaseImage::AEBaseImage() {
    _width = _height = _length = 0;
    _bytes = NULL;
    _premultipliedAlpha = GL_FALSE;
}

AEBaseImage::AEBaseImage(std::string pathfile): AEBaseImage() {
    AEData file = AEDataWithPathfile(pathfile);
    this->initPNG((GLuchar*)file.bytes, file.size);
    _ae_free(file.bytes);
}

AESize AEBaseImage::getSize() {
    return AESizeMake(_width, _height);
}

GLboolean AEBaseImage::initPNG(const GLuchar* data, size_t dataLen) {
    if (dataLen < PNGSIGSIZE) {
        return GL_FALSE;
    }
    
    GLboolean ret = GL_FALSE;
    png_byte    header[PNGSIGSIZE] = {0};
    png_structp png_ptr   = 0;
    png_infop   info_ptr  = 0;
    
    do {
        memcpy(header, data, PNGSIGSIZE);
        _ae_break(png_sig_cmp(header, 0, PNGSIGSIZE));
        
        png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        _ae_break(!png_ptr);
        
        info_ptr = png_create_info_struct(png_ptr);
        _ae_break(!info_ptr);
        
        _ae_break(setjmp(png_jmpbuf(png_ptr)));
        
        // set the read call back function
        tImageSource imageSource;
        imageSource.data   = data;
        imageSource.size   = dataLen;
        imageSource.offset = 0;
        png_set_read_fn(png_ptr, &imageSource, pngReadCallback);
        
        png_read_info(png_ptr, info_ptr);
        _width  = png_get_image_width(png_ptr,  info_ptr);
        _height = png_get_image_height(png_ptr, info_ptr);
        png_byte    bit_depth  = png_get_bit_depth(png_ptr,  info_ptr);
        png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);
        
        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png_ptr);
        }
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
            bit_depth = 8;
            png_set_expand_gray_1_2_4_to_8(png_ptr);
        }
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
            png_set_tRNS_to_alpha(png_ptr);
        }
        if (bit_depth == 16) {
            png_set_strip_16(png_ptr);
        }
        if (bit_depth < 8) {
            png_set_packing(png_ptr);
        }
        png_read_update_info(png_ptr, info_ptr);
        bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        
        switch (color_type) {
            case PNG_COLOR_TYPE_GRAY:
                _format = AEFormat::I8;
                break;
            case PNG_COLOR_TYPE_GRAY_ALPHA:
                _format = AEFormat::AI88;
                break;
            case PNG_COLOR_TYPE_RGB:
                _format = AEFormat::RGB888;
                break;
            case PNG_COLOR_TYPE_RGB_ALPHA:
                _format = AEFormat::RGBA8888;
                break;
            default:
                break;
        }
        
        png_size_t rowbytes     = png_get_rowbytes(png_ptr, info_ptr);
        png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * _height);
        
        _length = rowbytes * _height;
        _bytes  = static_cast<GLuchar*>(malloc(_length * sizeof(unsigned char)));
        if (!_bytes) {
            if (row_pointers) {
                free(row_pointers);
            }
            break;
        }
        
        for (unsigned short i = 0; i < _height; ++i) {
            row_pointers[i] = _bytes + i * rowbytes;
        }
        png_read_image(png_ptr, row_pointers);
        png_read_end(png_ptr, nullptr);
        
        if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
            onPremultipliedAlpha();
        }
        else {
            _premultipliedAlpha = false;
        }
        if (row_pointers) {
            free(row_pointers);
        }
        ret = GL_TRUE;
    } while (0);
    
    if (png_ptr) {
        png_destroy_read_struct(&png_ptr, (info_ptr ? &info_ptr : nullptr), nullptr);
    }
    return ret;
}

GLvoid AEBaseImage::onPremultipliedAlpha() {
    if (_format != AEFormat::RGBA8888) {
        fprintf(stderr, "The pixel format should be RGBA8888!");
    }
    GLuint* colors = (GLuint*)_bytes;
    for(int i = 0, count = _width * _height; i < count; i++) {
        GLuchar* p = _bytes + i * 4;
        colors[i] = CC_RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
    }
    _premultipliedAlpha = true;
}
