//
//  AEBaseProgram.cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/7/26.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEBaseProgram.h"

_ae_synthesize(AEBaseProgram, GLuint, Screen,         screen);
_ae_synthesize(AEBaseProgram, GLuint, Program,        program);
_ae_synthesize(AEBaseProgram, GLuint, VertexShader,   vertexShader);
_ae_synthesize(AEBaseProgram, GLuint, FragmentShader, fragmentShader);

AEBaseProgram::~AEBaseProgram() {
    if (_program) {
        glDeleteProgram(_program);
        _program = 0;
    }
}

AEBaseProgram::AEBaseProgram() {
    _screen = _program = _vertexShader = _fragmentShader = 0;
}

AEBaseProgram::AEBaseProgram(const char* vertexShaderSource, const char* fragmentShaderSource): AEBaseProgram() {
    _vertexShader   = createShader(GL_VERTEX_SHADER,   vertexShaderSource);
    _fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    
    _program = glCreateProgram();
    glAttachShader(_program, _vertexShader);
    glAttachShader(_program, _fragmentShader);
    
    glBindAttribLocation(_program, kAEProgramAttributePt,    "pt");
    glBindAttribLocation(_program, kAEProgramAttributeUV,    "uv");
    glBindAttribLocation(_program, kAEProgramAttributeColor, "color");
    
    GLint status;
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint msgLength = 0;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &msgLength);
        if (msgLength > 0) {
            char* msg = (char*) malloc(msgLength);
            glGetProgramInfoLog(_program, msgLength, NULL, msg);
            printf("Could not link program:\n%s\n", msg);
            free(msg);
        }
        glDeleteProgram (_program);
        return;
    }
    
    _screen = glGetUniformLocation(_program, "uScreen");
    
    glDetachShader(_program, _vertexShader);
    glDeleteShader(_vertexShader);
    _vertexShader = 0;
    
    glDetachShader(_program, _fragmentShader);
    glDeleteShader(_fragmentShader);
    _fragmentShader = 0;
    
    CheckGlError();
    fprintf(stderr, "Program   [program] is %d\n", _program);
    fprintf(stderr, "Attribute [  p t  ] is %d\n", glGetAttribLocation(_program, "pt"));
    fprintf(stderr, "Attribute [  u v  ] is %d\n", glGetAttribLocation(_program, "uv"));
    fprintf(stderr, "Attribute [ color ] is %d\n", glGetAttribLocation(_program, "color"));
    fprintf(stderr, "Uniform   [screen ] is %d\n", _screen);
}

/** ========================Private_Methods======================== */
GLuint AEBaseProgram::createShader(GLenum shaderType, const GLchar* source) {
    GLint compiled;
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        return shader;
    }
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == 0) {
        CheckGlError();
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0) {
            char* infoLog = (char*) malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            fprintf(stderr, "Error Compiling Shader: %s ", infoLog);
            free(infoLog);
            glDeleteShader(shader);
            shader = 0;
        }
        return shader;
    }
    return shader;
}
