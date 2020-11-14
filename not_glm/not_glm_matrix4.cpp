#include "not_glm_matrix4.hpp"
#include "Constants.hpp"

#include <assert.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

namespace NotGLM {
    Matrix4::Matrix4() {
        for (int i = 0; i < 16; i++) {
            matrixData[i] = 0.0f;
        }
    };

    Matrix4::Matrix4(float m0) {
        for (int i = 0; i < 16; i++) {
            matrixData[i] = 0.0f;
        }
        matrixData[0] = matrixData[5] = matrixData[10] = matrixData[15] = m0;
    };

    Matrix4::Matrix4(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15) {
        matrixData[0] = m0;
        matrixData[4] = m4;
        matrixData[8] = m8;
        matrixData[12] = m12;

        matrixData[1] = m1;
        matrixData[5] = m5;
        matrixData[9] = m9;
        matrixData[13] = m13;

        matrixData[2] = m2;
        matrixData[6] = m6;
        matrixData[10] = m10;
        matrixData[14] = m14;

        matrixData[3] = m3;
        matrixData[7] = m7;
        matrixData[11] = m11;
        matrixData[15] = m15;
    };

    Matrix4& Matrix4::operator=(const Matrix4& value) {
        for (int i = 0; i < 16; i++) {
            matrixData[i] = value.matrixData[i];
        }

        return *this;
    };

    Matrix4::~Matrix4() {

    };

    Matrix4 Matrix4::operator+(const Matrix4& m) const {
        Matrix4 n;

        n.matrixData[0] = matrixData[0] + m.matrixData[0];
        n.matrixData[4] = matrixData[4] + m.matrixData[4];
        n.matrixData[8] = matrixData[8] + m.matrixData[8];
        n.matrixData[12] = matrixData[12] + m.matrixData[12];

        n.matrixData[1] = matrixData[1] + m.matrixData[1];
        n.matrixData[5] = matrixData[5] + m.matrixData[5];
        n.matrixData[9] = matrixData[9] + m.matrixData[9];
        n.matrixData[13] = matrixData[13] + m.matrixData[13];

        n.matrixData[2] = matrixData[2] + m.matrixData[2];
        n.matrixData[6] = matrixData[6] + m.matrixData[6];
        n.matrixData[10] = matrixData[10] + m.matrixData[10];
        n.matrixData[14] = matrixData[14] + m.matrixData[14];

        n.matrixData[3] = matrixData[3] + m.matrixData[3];
        n.matrixData[7] = matrixData[7] + m.matrixData[7];
        n.matrixData[11] = matrixData[11] + m.matrixData[11];
        n.matrixData[15] = matrixData[15] + m.matrixData[15];

        return n;
    };

    void Matrix4::operator+=(const Matrix4& m) {
        matrixData[0] += m.matrixData[0];
        matrixData[4] += m.matrixData[4];
        matrixData[8] += m.matrixData[8];
        matrixData[12] += m.matrixData[12];

        matrixData[1] += m.matrixData[1];
        matrixData[5] += m.matrixData[5];
        matrixData[9] += m.matrixData[9];
        matrixData[13] += m.matrixData[13];

        matrixData[2] += m.matrixData[2];
        matrixData[6] += m.matrixData[6];
        matrixData[10] += m.matrixData[10];
        matrixData[14] += m.matrixData[14];

        matrixData[3] += m.matrixData[3];
        matrixData[7] += m.matrixData[7];
        matrixData[11] += m.matrixData[11];
        matrixData[15] += m.matrixData[15];
    };

    Matrix4 Matrix4::operator*(const float s) const {
        Matrix4 n;

        n.matrixData[0] = matrixData[0] * s;
        n.matrixData[4] = matrixData[4] * s;
        n.matrixData[8] = matrixData[8] * s;
        n.matrixData[12] = matrixData[12] * s;

        n.matrixData[1] = matrixData[1] * s;
        n.matrixData[5] = matrixData[8] * s;
        n.matrixData[9] = matrixData[9] * s;
        n.matrixData[13] = matrixData[13] * s;

        n.matrixData[2] = matrixData[2] * s;
        n.matrixData[6] = matrixData[6] * s;
        n.matrixData[10] = matrixData[10] * s;
        n.matrixData[14] = matrixData[14] * s;
        
        n.matrixData[3] = matrixData[3] * s;
        n.matrixData[7] = matrixData[7] * s;
        n.matrixData[11] = matrixData[11] * s;
        n.matrixData[15] = matrixData[15] * s;

        return n;
    };

    void Matrix4::operator*=(const float s) {
        matrixData[0] *= s;
        matrixData[4] *= s;
        matrixData[8] *= s;
        matrixData[12] *= s;

        matrixData[1] *= s;
        matrixData[5] *= s;
        matrixData[9] *= s;
        matrixData[13] *= s;

        matrixData[2] *= s;
        matrixData[6] *= s;
        matrixData[10] *= s;
        matrixData[14] *= s;

        matrixData[3] *= s;
        matrixData[7] *= s;
        matrixData[11] *= s;
        matrixData[15] *= s;
    };

    Vector4 Matrix4::operator*(const Vector4& v) const {
        return Vector4(
            matrixData[0] * v.x + matrixData[4] * v.y + matrixData[8] * v.z + matrixData[12] * v.w,
            matrixData[1] * v.x + matrixData[5] * v.y + matrixData[9] * v.z + matrixData[13] * v.w,
            matrixData[2] * v.x + matrixData[6] * v.y + matrixData[10] * v.z + matrixData[14] * v.w,
            matrixData[3] * v.x + matrixData[7] * v.y + matrixData[11] * v.z + matrixData[15] * v.w);
    }

    Vector4 Matrix4::transformVectorByMatrix(const Vector4& v) const {
        return(*this) * v;
    }

    Matrix4 Matrix4::operator*(const Matrix4& m) const {
        return Matrix4(
            matrixData[0] * m.matrixData[0] + matrixData[4] * m.matrixData[1] + matrixData[8] * m.matrixData[2] + matrixData[12] * m.matrixData[3],
            matrixData[0] * m.matrixData[4] + matrixData[4] * m.matrixData[5] + matrixData[8] * m.matrixData[6] + matrixData[12] * m.matrixData[7],
            matrixData[0] * m.matrixData[8] + matrixData[4] * m.matrixData[9] + matrixData[8] * m.matrixData[10] + matrixData[12] * m.matrixData[11],
            matrixData[0] * m.matrixData[12] + matrixData[4] * m.matrixData[13] + matrixData[8] * m.matrixData[14] + matrixData[12] * m.matrixData[15],

            matrixData[1] * m.matrixData[0] + matrixData[5] * m.matrixData[1] + matrixData[9] * m.matrixData[2] + matrixData[13] * m.matrixData[3],
            matrixData[1] * m.matrixData[4] + matrixData[5] * m.matrixData[5] + matrixData[9] * m.matrixData[6] + matrixData[13] * m.matrixData[7],
            matrixData[1] * m.matrixData[8] + matrixData[5] * m.matrixData[9] + matrixData[9] * m.matrixData[10] + matrixData[13] * m.matrixData[11],
            matrixData[1] * m.matrixData[12] + matrixData[5] * m.matrixData[13] + matrixData[9] * m.matrixData[14] + matrixData[13] * m.matrixData[15],

            matrixData[2] * m.matrixData[0] + matrixData[6] * m.matrixData[1] + matrixData[10] * m.matrixData[2] + matrixData[14] * m.matrixData[3],
            matrixData[2] * m.matrixData[4] + matrixData[6] * m.matrixData[5] + matrixData[10] * m.matrixData[6] + matrixData[14] * m.matrixData[7],
            matrixData[2] * m.matrixData[8] + matrixData[6] * m.matrixData[9] + matrixData[10] * m.matrixData[10] + matrixData[14] * m.matrixData[11],
            matrixData[2] * m.matrixData[12] + matrixData[6] * m.matrixData[13] + matrixData[10] * m.matrixData[14] + matrixData[14] * m.matrixData[15],

            matrixData[3] * m.matrixData[0] + matrixData[7] * m.matrixData[1] + matrixData[11] * m.matrixData[2] + matrixData[15] * m.matrixData[3],
            matrixData[3] * m.matrixData[4] + matrixData[7] * m.matrixData[5] + matrixData[11] * m.matrixData[6] + matrixData[15] * m.matrixData[7],
            matrixData[3] * m.matrixData[8] + matrixData[7] * m.matrixData[9] + matrixData[11] * m.matrixData[10] + matrixData[15] * m.matrixData[11],
            matrixData[3] * m.matrixData[12] + matrixData[7] * m.matrixData[13] + matrixData[11] * m.matrixData[14] + matrixData[15] * m.matrixData[15]);
    }

    void Matrix4::operator*=(const Matrix4& m) {
        float t1;
        float t2;
        float t3;
        float t4;

        t1 = matrixData[0] * m.matrixData[0] + matrixData[4] * m.matrixData[1] + matrixData[8] * m.matrixData[2] + matrixData[12] * m.matrixData[3];
        t2 = matrixData[0] * m.matrixData[4] + matrixData[4] * m.matrixData[5] + matrixData[8] * m.matrixData[6] + matrixData[12] * m.matrixData[7];
        t3 = matrixData[0] * m.matrixData[8] + matrixData[4] * m.matrixData[9] + matrixData[8] * m.matrixData[10] + matrixData[12] * m.matrixData[11];
        t4 = matrixData[0] * m.matrixData[12] + matrixData[4] * m.matrixData[13] + matrixData[8] * m.matrixData[14] + matrixData[12] * m.matrixData[15];

        matrixData[0] = t1;
        matrixData[4] = t2;
        matrixData[8] = t3;
        matrixData[12] = t4;

        t1 = matrixData[1] * m.matrixData[0] + matrixData[5] * m.matrixData[1] + matrixData[9] * m.matrixData[2] + matrixData[13] * m.matrixData[3];
        t2 = matrixData[1] * m.matrixData[4] + matrixData[5] * m.matrixData[5] + matrixData[9] * m.matrixData[6] + matrixData[13] * m.matrixData[7];
        t3 = matrixData[1] * m.matrixData[8] + matrixData[5] * m.matrixData[9] + matrixData[9] * m.matrixData[10] + matrixData[13] * m.matrixData[11];
        t4 = matrixData[1] * m.matrixData[12] + matrixData[5] * m.matrixData[13] + matrixData[9] * m.matrixData[14] + matrixData[13] * m.matrixData[15];

        matrixData[1] = t1;
        matrixData[5] = t2;
        matrixData[9] = t3;
        matrixData[13] = t4;


        t1 = matrixData[2] * m.matrixData[0] + matrixData[6] * m.matrixData[1] + matrixData[10] * m.matrixData[2] + matrixData[14] * m.matrixData[3];
        t2 = matrixData[2] * m.matrixData[4] + matrixData[6] * m.matrixData[5] + matrixData[10] * m.matrixData[6] + matrixData[14] * m.matrixData[7];
        t3 = matrixData[2] * m.matrixData[8] + matrixData[6] * m.matrixData[9] + matrixData[10] * m.matrixData[10] + matrixData[14] * m.matrixData[11];
        t4 = matrixData[2] * m.matrixData[12] + matrixData[6] * m.matrixData[13] + matrixData[10] * m.matrixData[14] + matrixData[14] * m.matrixData[15];

        matrixData[2] = t1;
        matrixData[6] = t2;
        matrixData[10] = t3;
        matrixData[14] = t4;

        t1 = matrixData[3] * m.matrixData[0] + matrixData[7] * m.matrixData[1] + matrixData[11] * m.matrixData[2] + matrixData[15] * m.matrixData[3];
        t2 = matrixData[3] * m.matrixData[4] + matrixData[7] * m.matrixData[5] + matrixData[11] * m.matrixData[6] + matrixData[15] * m.matrixData[7];
        t3 = matrixData[3] * m.matrixData[8] + matrixData[7] * m.matrixData[9] + matrixData[11] * m.matrixData[10] + matrixData[15] * m.matrixData[11];
        t4 = matrixData[3] * m.matrixData[12] + matrixData[7] * m.matrixData[13] + matrixData[11] * m.matrixData[14] + matrixData[15] * m.matrixData[15];

        matrixData[3] = t1;
        matrixData[7] = t2;
        matrixData[11] = t3;
        matrixData[15] = t4;
    }

    void Matrix4::setMatrixAsIdentityMatrix() {
        for (int i = 0; i < 16; i++) {
            matrixData[i] = 0.0f;
        }

        matrixData[0] = matrixData[5] = matrixData[10] = matrixData[15] = 1.0f;
    }

    // --- TO DO
    /*void Matrix4::setMatrixAsInverseOfGivenMatrix(const Matrix4& m) {
        float t1 = m.matrixData[0] * m.matrixData[4];
        float t2 = m.matrixData[0] * m.matrixData[7];
        float t3 = m.matrixData[3] * m.matrixData[1];
        float t4 = m.matrixData[6] * m.matrixData[1];
        float t5 = m.matrixData[3] * m.matrixData[2];
        float t6 = m.matrixData[6] * m.matrixData[2];

        float det = (t1 * m.matrixData[8] - t2 * m.matrixData[5] - t3 * m.matrixData[8] + t4 * m.matrixData[5] + t5 * m.matrixData[7] - t6 * m.matrixData[4]);

        if (det == 0.0) return;

        float invd = 1.0f / det;

        float m0 = (m.matrixData[4] * m.matrixData[8] - m.matrixData[7] * m.matrixData[5]) * invd;
        float m3 = -(m.matrixData[3] * m.matrixData[8] - m.matrixData[6] * m.matrixData[5]) * invd;

        float m6 = (m.matrixData[3] * m.matrixData[7] - m.matrixData[6] * m.matrixData[4]) * invd;

        float m1 = -(m.matrixData[1] * m.matrixData[8] - m.matrixData[7] * m.matrixData[2]) * invd;

        float m4 = (m.matrixData[0] * m.matrixData[8] - t6) * invd;

        float m7 = -(t2 - t4) * invd;

        float m2 = (m.matrixData[1] * m.matrixData[5] - m.matrixData[4] * m.matrixData[2]) * invd;

        float m5 = -(m.matrixData[0] * m.matrixData[5] - t5) * invd;

        float m8 = (t1 - t3) * invd;

        matrixData[0] = m0;
        matrixData[3] = m3;
        matrixData[6] = m6;

        matrixData[1] = m1;
        matrixData[4] = m4;
        matrixData[7] = m7;

        matrixData[2] = m2;
        matrixData[5] = m5;
        matrixData[8] = m8;
    }

    Matrix4 Matrix4::getInverseOfMatrix() const {
        Matrix4 result;
        result.setMatrixAsInverseOfGivenMatrix(*this);
        return result;
    }

    void Matrix4::invertMatrix() {
        setMatrixAsInverseOfGivenMatrix(*this);
    }

    float Matrix4::getMatrixDeterminant() const {
        float t1 = matrixData[0] * matrixData[4];
        float t2 = matrixData[0] * matrixData[7];
        float t3 = matrixData[3] * matrixData[1];
        float t4 = matrixData[6] * matrixData[1];
        float t5 = matrixData[3] * matrixData[2];
        float t6 = matrixData[6] * matrixData[2];

        float det = (t1 * matrixData[8] - t2 * matrixData[5] - t3 * matrixData[8] + t4 * matrixData[5] + t5 * matrixData[7] - t6 * matrixData[4]);

        return det;
    }

    void Matrix4::setMatrixAsTransposeOfGivenMatrix(const Matrix4& m) {
        matrixData[0] = m.matrixData[0];
        matrixData[3] = m.matrixData[1];
        matrixData[6] = m.matrixData[2];

        matrixData[1] = m.matrixData[3];
        matrixData[4] = m.matrixData[4];
        matrixData[7] = m.matrixData[5];

        matrixData[2] = m.matrixData[6];
        matrixData[5] = m.matrixData[7];
        matrixData[8] = m.matrixData[8];
    }

    Matrix4 Matrix4::getTransposeOfMatrix() const {
        Matrix4 result;
        result.setMatrixAsTransposeOfGivenMatrix(*this);
        return result;
    }

    void Matrix4::invertAndTransposeMatrix() {
        float det = matrixData[0] * (matrixData[4] * matrixData[8] - matrixData[5] * matrixData[7]) - matrixData[3] * (matrixData[1] * matrixData[8] - matrixData[2] * matrixData[7]) + matrixData[6] * (matrixData[1] * matrixData[5] - matrixData[2] * matrixData[4]);

        Matrix4 transpose;

        transpose.matrixData[0] = matrixData[0];
        transpose.matrixData[1] = matrixData[3];
        transpose.matrixData[2] = matrixData[6];

        transpose.matrixData[3] = matrixData[1];
        transpose.matrixData[4] = matrixData[4];
        transpose.matrixData[5] = matrixData[7];

        transpose.matrixData[6] = matrixData[2];
        transpose.matrixData[7] = matrixData[5];
        transpose.matrixData[8] = matrixData[8];

        float m11, m12, m13, m21, m22, m23, m31, m32, m33;

        m11 = +(transpose.matrixData[4] * transpose.matrixData[8] - transpose.matrixData[5] * transpose.matrixData[7]) / det;
        m12 = -(transpose.matrixData[1] * transpose.matrixData[8] - transpose.matrixData[2] * transpose.matrixData[7]) / det;
        m13 = +(transpose.matrixData[1] * transpose.matrixData[5] - transpose.matrixData[2] * transpose.matrixData[4]) / det;

        m21 = -(transpose.matrixData[3] * transpose.matrixData[8] - transpose.matrixData[5] * transpose.matrixData[6]) / det;
        m22 = +(transpose.matrixData[0] * transpose.matrixData[8] - transpose.matrixData[2] * transpose.matrixData[6]) / det;
        m23 = -(transpose.matrixData[0] * transpose.matrixData[5] - transpose.matrixData[2] * transpose.matrixData[3]) / det;

        m31 = +(transpose.matrixData[3] * transpose.matrixData[7] - transpose.matrixData[4] * transpose.matrixData[6]) / det;
        m32 = -(transpose.matrixData[0] * transpose.matrixData[7] - transpose.matrixData[1] * transpose.matrixData[6]) / det;
        m33 = +(transpose.matrixData[0] * transpose.matrixData[4] - transpose.matrixData[1] * transpose.matrixData[3]) / det;

        Matrix4 preResult;

        preResult.matrixData[0] = m11;
        preResult.matrixData[1] = m21;
        preResult.matrixData[2] = m31;

        preResult.matrixData[3] = m12;
        preResult.matrixData[4] = m22;
        preResult.matrixData[5] = m32;

        preResult.matrixData[6] = m13;
        preResult.matrixData[7] = m23;
        preResult.matrixData[8] = m33;

        matrixData[0] = preResult.matrixData[0];
        matrixData[1] = preResult.matrixData[3];
        matrixData[2] = preResult.matrixData[6];

        matrixData[3] = preResult.matrixData[1];
        matrixData[4] = preResult.matrixData[4];
        matrixData[5] = preResult.matrixData[7];

        matrixData[6] = preResult.matrixData[2];
        matrixData[7] = preResult.matrixData[5];
        matrixData[8] = preResult.matrixData[8];
    }

    void Matrix4::makeRotationMatrixAboutXAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);

        (*this).setMatrixAsIdentityMatrix();

        Matrix4 m(1.0, 0.0, 0.0,
            0.0, cos(uAngle), -sin(uAngle),
            0.0, sin(uAngle), cos(uAngle));

        *this = m * (*this);
    }

    void Matrix4::makeRotationMatrixAboutYAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);
        (*this).setMatrixAsIdentityMatrix();

        Matrix4 m(cos(uAngle), 0.0, sin(uAngle),
            0.0, 1.0, 0.0,
            -sin(uAngle), 0.0, cos(uAngle));

        *this = m * (*this);
    }

    void Matrix4::makeRotationMatrixAboutZAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);
        (*this).setMatrixAsIdentityMatrix();

        Matrix4 m(cos(uAngle), -sin(uAngle), 0.0,
            sin(uAngle), cos(uAngle), 0.0,
            0.0, 0.0, 1.0);

        *this = m * (*this);
    }

    void Matrix4::transformMatrixAboutXAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);

        Matrix4 m(1.0, 0.0, 0.0,
            0.0, cos(uAngle), -sin(uAngle),
            0.0, sin(uAngle), cos(uAngle));

        *this = m * (*this);
    }

    void Matrix4::transformMatrixAboutYAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);

        Matrix4 m(cos(uAngle), 0.0, sin(uAngle),
            0.0, 1.0, 0.0,
            -sin(uAngle), 0.0, cos(uAngle));

        *this = m * (*this);
    }

    void Matrix4::transformMatrixAboutZAxisByAngle(float uAngle) {
        uAngle = DegreesToRad(uAngle);

        Matrix4 m(cos(uAngle), -sin(uAngle), 0.0,
            sin(uAngle), cos(uAngle), 0.0,
            0.0, 0.0, 1.0);

        *this = m * (*this);
    }*/

    void Matrix4::show() {
        printf("mat4x4((%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f))\n",
            matrixData[0], matrixData[1], matrixData[2], matrixData[3],
            matrixData[4], matrixData[5], matrixData[6], matrixData[7],
            matrixData[8], matrixData[9], matrixData[10], matrixData[11],
            matrixData[12], matrixData[13], matrixData[14], matrixData[15]);
    }

    void Matrix4::show(int row) {
        if (row == 1) {
            printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[0], matrixData[1], matrixData[2], matrixData[3]);
        }
        else if (row == 2) {
            printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[4], matrixData[5], matrixData[6], matrixData[7]);
        }
        else if (row == 3) {
            printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[8], matrixData[9], matrixData[10], matrixData[11]);
        }
        else if (row == 4) {
            printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[12], matrixData[13], matrixData[14], matrixData[15]);
        }
        else {
            printf("Outside of matrix scope\n");
        }
    }
}