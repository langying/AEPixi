//
//  AEBaseProgram.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEBaseProgram__
#define __AEPixi__AEBaseProgram__

#include "AECommon.h"

enum {
    kAEProgramAttributePt,
    kAEProgramAttributeUV,
    kAEProgramAttributeColor
};

class AEBaseProgram {
    _ae_property(GLuint, Screen,         screen);
    _ae_property(GLuint, Program,        program);
    _ae_property(GLuint, VertexShader,   vertexShader);
    _ae_property(GLuint, FragmentShader, fragmentShader);
public:
    ~AEBaseProgram();
    AEBaseProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
protected:
    AEBaseProgram();
    GLuint createShader(GLuint shaderType, const GLchar* source);
};


#endif /* defined(__AEPixi__AEBaseProgram__) */
