#include "not_glm_matrix4x3.hpp"
#include "Constants.hpp"

#include <assert.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

namespace NotGLM {
    Matrix4x3::Matrix4x3() {
        for (int i = 0; i < 12; i++) {
            matrixData[i] = 0.0f;
        }
    };

    Matrix4x3::Matrix4x3(float m0) {
        for (int i = 0; i < 12; i++) {
            matrixData[i] = 0.0f;
        }
        matrixData[0] = matrixData[4] = matrixData[8] = m0;
    };

    Matrix4x3::Matrix4x3(float m0, float m3, float m6, float m9, float m1, float m4, float m7, float m10, float m2, float m5, float m8, float m11) {
        matrixData[0] = m0;
        matrixData[3] = m3;
        matrixData[6] = m6;
        matrixData[9] = m9;

        matrixData[1] = m1;
        matrixData[4] = m4;
        matrixData[7] = m7;
        matrixData[10] = m10;

        matrixData[2] = m2;
        matrixData[5] = m5;
        matrixData[8] = m8;
        matrixData[11] = m11;
    };

    Matrix4x3& Matrix4x3::operator=(const Matrix4x3& value) {
        for (int i = 0; i < 12; i++) {
            matrixData[i] = value.matrixData[i];
        }

        return *this;
    };

    Matrix4x3::~Matrix4x3() {

    };

    Matrix4x3 Matrix4x3::operator+(const Matrix4x3& m) const {
        Matrix4x3 n;

        n.matrixData[0] = matrixData[0] + m.matrixData[0];
        n.matrixData[3] = matrixData[3] + m.matrixData[3];
        n.matrixData[6] = matrixData[6] + m.matrixData[6];
        n.matrixData[9] = matrixData[9] + m.matrixData[9];

        n.matrixData[1] = matrixData[1] + m.matrixData[1];
        n.matrixData[5] = matrixData[5] + m.matrixData[5];
        n.matrixData[9] = matrixData[9] + m.matrixData[9];
        n.matrixData[13] = matrixData[13] + m.matrixData[13];

        n.matrixData[2] = matrixData[2] + m.matrixData[2];
        n.matrixData[6] = matrixData[6] + m.matrixData[6];
        n.matrixData[10] = matrixData[10] + m.matrixData[10];
        n.matrixData[14] = matrixData[14] + m.matrixData[14];

        return n;
    };

    void Matrix4x3::operator+=(const Matrix4x3& m) {
        matrixData[0] += m.matrixData[0];
        matrixData[3] += m.matrixData[3];
        matrixData[6] += m.matrixData[6];
        matrixData[9] += m.matrixData[9];

        matrixData[1] += m.matrixData[1];
        matrixData[4] += m.matrixData[4];
        matrixData[7] += m.matrixData[7];
        matrixData[10] += m.matrixData[10];

        matrixData[2] += m.matrixData[2];
        matrixData[5] += m.matrixData[5];
        matrixData[8] += m.matrixData[8];
        matrixData[11] += m.matrixData[11];
    };

    Matrix4x3 Matrix4x3::operator*(const float s) const {
        Matrix4x3 n;

        n.matrixData[0] = matrixData[0] * s;
        n.matrixData[3] = matrixData[3] * s;
        n.matrixData[6] = matrixData[6] * s;
        n.matrixData[9] = matrixData[9] * s;

        n.matrixData[1] = matrixData[1] * s;
        n.matrixData[4] = matrixData[4] * s;
        n.matrixData[7] = matrixData[7] * s;
        n.matrixData[10] = matrixData[10] * s;

        n.matrixData[2] = matrixData[2] * s;
        n.matrixData[5] = matrixData[5] * s;
        n.matrixData[8] = matrixData[8] * s;
        n.matrixData[11] = matrixData[11] * s;

        return n;
    };

    void Matrix4x3::operator*=(const float s) {
        matrixData[0] *= s;
        matrixData[3] *= s;
        matrixData[6] *= s;
        matrixData[9] *= s;

        matrixData[1] *= s;
        matrixData[4] *= s;
        matrixData[7] *= s;
        matrixData[10] *= s;

        matrixData[2] *= s;
        matrixData[5] *= s;
        matrixData[8] *= s;
        matrixData[11] *= s;
    };

    Vector4 Matrix4x3::operator*(const Vector4& v) const {
        return Vector4(
            matrixData[0] * v.x + matrixData[4] * v.y + matrixData[8] * v.z,
            matrixData[1] * v.x + matrixData[5] * v.y + matrixData[9] * v.z,
            matrixData[2] * v.x + matrixData[6] * v.y + matrixData[10] * v.z,
            matrixData[3] * v.x + matrixData[7] * v.y + matrixData[11] * v.z);
    }

    Vector4 Matrix4x3::transformVectorByMatrix(const Vector4& v) const {
        return(*this) * v;
    }

    void Matrix4x3::setMatrixAsIdentityMatrix() {
        for (int i = 0; i < 12; i++) {
            matrixData[i] = 0.0f;
        }
        matrixData[0] = matrixData[4] = matrixData[8] = 1.0f;
    }

    void Matrix4x3::show() {
        printf("mat4x3((%.6f, %.6f, %.6f), (%.6f, %.6f, %.6f), (%.6f, %.6f, %.6f), (%.6f, %.6f, %.6f))\n",
            matrixData[0], matrixData[1], matrixData[2],
            matrixData[3], matrixData[4], matrixData[5],
            matrixData[6], matrixData[7], matrixData[8],
            matrixData[9], matrixData[10], matrixData[11]);
    }

    void Matrix4x3::show(int row) {
        if (row == 1) {
            printf("mat4x3 matrixData[%d] = (%.6f, %.6f, %.6f)\n", row, matrixData[0], matrixData[1], matrixData[2]);
        }
        else if (row == 2) {
            printf("mat4x3 matrixData[%d] = (%.6f, %.6f, %.6f)\n", row, matrixData[3], matrixData[4], matrixData[5]);
        }
        else if (row == 3) {
            printf("mat4x3 matrixData[%d] = (%.6f, %.6f, %.6f)\n", row, matrixData[6], matrixData[7], matrixData[8]);
        }
        else if (row == 4) {
            printf("mat4x3 matrixData[%d] = (%.6f, %.6f, %.6f)\n", row, matrixData[9], matrixData[10], matrixData[11]);
        }
        else {
            printf("Outside of matrix scope\n");
        }
    }
}