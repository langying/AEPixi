//
//  AETilingProgram.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/5.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AETilingProgram.h"

_ae_synthesize(AETilingProgram, GLuint, Frame,     frame);
_ae_synthesize(AETilingProgram, GLuint, Transform, transform);
_ae_synthesize(AETilingProgram, GLuint, PixelSize, pixelSize);

AETilingProgram::AETilingProgram() {
    _frame = _transform = _pixelSize = 0;
}
AETilingProgram::AETilingProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource): AEBaseProgram(vertexShaderSource, fragmentShaderSource) {
    AETilingProgram();
    _frame     = glGetUniformLocation(_program, "uFrame");
    _transform = glGetUniformLocation(_program, "uTransform");
    _pixelSize = glGetUniformLocation(_program, "uPixelSize");
    fprintf(stderr, "Uniform   [frame    ] is %d\n", _frame);
    fprintf(stderr, "Uniform   [transform] is %d\n", _transform);
    fprintf(stderr, "Uniform   [pixelSize] is %d\n", _pixelSize);
}
