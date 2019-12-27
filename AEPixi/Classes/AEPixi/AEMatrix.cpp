//
//  AEmatrix->cpp
//  AEPixi
//
//  Created by 朗英·韩琼 on 15/9/7.
//  Copyright (c) 2015年 AppEngine. All rights reserved.
//

#include "AEmatrix.h"

_ae_synthesize(AEMatrix, GLfloat, A,  a);
_ae_synthesize(AEMatrix, GLfloat, B,  b);
_ae_synthesize(AEMatrix, GLfloat, C,  c);
_ae_synthesize(AEMatrix, GLfloat, D,  d);
_ae_synthesize(AEMatrix, GLfloat, Tx, tx);
_ae_synthesize(AEMatrix, GLfloat, Ty, ty);

AEMatrix::~AEMatrix() {
}

AEMatrix::AEMatrix() {
    _a  = 1;
    _b  = 0;
    _c  = 0;
    _d  = 1;
    _tx = 0;
    _ty = 0;
}

GLvoid AEMatrix::invert() {
    GLfloat a  = _a;
    GLfloat b  = _b;
    GLfloat c  = _c;
    GLfloat d  = _d;
    GLfloat tx = _tx;
    GLfloat ty = _ty;
    GLfloat value = a * d - b * c;
    
    _a  =  d / value;
    _b  = -b / value;
    _c  = -c / value;
    _d  =  a / value;
    _tx =  (c * ty - d * tx) / value;
    _ty = -(a * ty - b * tx) / value;
}

GLvoid AEMatrix::identity() {
    _a  = 1;
    _b  = 0;
    _c  = 0;
    _d  = 1;
    _tx = 0;
    _ty = 0;
}

GLvoid AEMatrix::scale(GLfloat x, GLfloat y) {
    _a  *= x;
    _d  *= y;
    _c  *= x;
    _b  *= y;
    _tx *= x;
    _ty *= y;
}

GLvoid AEMatrix::rotate(GLfloat angle) {
    GLfloat a  = _a;
    GLfloat c  = _c;
    GLfloat tx = _tx;
    GLfloat cr = cos(angle);
    GLfloat sr = sin(angle);
    
    _a  = a  * cr - _b  * sr;
    _b  = a  * sr + _b  * cr;
    _c  = c  * cr - _d  * sr;
    _d  = c  * sr + _d  * cr;
    _tx = tx * cr - _ty * sr;
    _ty = tx * sr + _ty * cr;
}

GLvoid AEMatrix::append(AEMatrix* m) {
    GLfloat a = _a;
    GLfloat b = _b;
    GLfloat c = _c;
    GLfloat d = _d;
    
    _a  = m->_a  * a + m->_b  * c;
    _b  = m->_a  * b + m->_b  * d;
    _c  = m->_c  * a + m->_d  * c;
    _d  = m->_c  * b + m->_d  * d;
    _tx = m->_tx * a + m->_ty * c + _tx;
    _ty = m->_tx * b + m->_ty * d + _ty;
}

GLvoid AEMatrix::prepend(AEMatrix* m) {
    GLfloat a  = _a;
    GLfloat c  = _c;
    GLfloat tx = _tx;
    if (m->_a != 1 || m->_b != 0 || m->_c != 0 || m->_d != 1) {
        _a  = a * m->_a + _b * m->_c;
        _b  = a * m->_b + _b * m->_d;
        _c  = c * m->_a + _d * m->_c;
        _d  = c * m->_b + _d * m->_d;
    }
    _tx = tx * m->_a + _ty * m->_c + m->_tx;
    _ty = tx * m->_b + _ty * m->_d + m->_ty;
}

GLvoid AEMatrix::translate(GLfloat x, GLfloat y) {
    _tx += x;
    _ty += y;
}

GLvoid AEMatrix::toArray(GLfloat* array, bool transpose) {
    if (transpose) {
        array[0] = _a;
        array[1] = _b;
        array[2] = 0;
        array[3] = _c;
        array[4] = _d;
        array[5] = 0;
        array[6] = _tx;
        array[7] = _ty;
        array[8] = 1;
    }
    else {
        array[0] = _a;
        array[1] = _c;
        array[2] = _tx;
        array[3] = _b;
        array[4] = _d;
        array[5] = _ty;
        array[6] = 0;
        array[7] = 0;
        array[8] = 1;
    }
}
GLvoid AEMatrix::fromArray(GLfloat* array) {
    _a  = array[0];
    _b  = array[1];
    _c  = array[3];
    _d  = array[4];
    _tx = array[2];
    _ty = array[5];
}

GLvoid AEMatrix::copy(AEMatrix* matrix) {
    _a  = matrix->_a;
    _b  = matrix->_b;
    _c  = matrix->_c;
    _d  = matrix->_d;
    _tx = matrix->_tx;
    _ty = matrix->_ty;
}

AEMatrix* AEMatrix::clone() {
    AEMatrix* matrix = new AEMatrix();
    matrix->_a  = _a;
    matrix->_b  = _b;
    matrix->_c  = _c;
    matrix->_d  = _d;
    matrix->_tx = _tx;
    matrix->_ty = _ty;
    return matrix;
}

AEPoint AEMatrix::apply(AEPoint& pt) {
    AEPoint point = {
        _a * pt.x + _c * pt.y + _tx,
        _b * pt.x + _d * pt.y + _ty
    };
    return point;
}

AEPoint AEMatrix::AEMatrix::applyInverse(AEPoint& pt) {
    GLfloat value = 1 / (_a * _d - _c * _b);
    AEPoint point = {
        _d * value * pt.x - _c * value * pt.y + ( _ty * _c - _tx * _d) * value,
        _a * value * pt.y - _b * value * pt.x + (-_ty * _a + _tx * _b) * value
    };
    return point;
}

