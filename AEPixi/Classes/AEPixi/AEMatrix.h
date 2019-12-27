//
//  AEMatrix.h
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#ifndef __AEPixi__AEMatrix__
#define __AEPixi__AEMatrix__

#include "AECommon.h"

class AEMatrix {
public:
    _ae_property(GLfloat, A,  a);
    _ae_property(GLfloat, B,  b);
    _ae_property(GLfloat, C,  c);
    _ae_property(GLfloat, D,  d);
    _ae_property(GLfloat, Tx, tx);
    _ae_property(GLfloat, Ty, ty);
    
public:
    ~AEMatrix();
    AEMatrix();
    GLvoid invert();
    GLvoid identity();
    GLvoid scale(GLfloat x, GLfloat y);
    GLvoid rotate(GLfloat angle);
    GLvoid append(AEMatrix* matrix);
    GLvoid prepend(AEMatrix* matrix);
    GLvoid translate(GLfloat x, GLfloat y);
    GLvoid toArray(GLfloat* array, bool transpose);
    GLvoid fromArray(GLfloat* array);
    GLvoid copy(AEMatrix* matrix);
    AEMatrix* clone();
    AEPoint apply(AEPoint& pt);
    AEPoint applyInverse(AEPoint& pt);
};

#endif /* defined(__AEPixi__AEMatrix__) */
