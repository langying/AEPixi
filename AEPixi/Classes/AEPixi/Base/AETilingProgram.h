//
//  AETilingProgram.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/8/5.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AETilingProgram__
#define __AEPixi__AETilingProgram__

#include "AEBaseProgram.h"

class AETilingProgram: public AEBaseProgram {
public:
    _ae_property(GLuint, Frame,     frame);
    _ae_property(GLuint, Transform, transform);
    _ae_property(GLuint, PixelSize, pixelSize);

public:
    AETilingProgram();
    AETilingProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
    
protected:
};

#endif /* defined(__AEPixi__AETilingProgram__) */
