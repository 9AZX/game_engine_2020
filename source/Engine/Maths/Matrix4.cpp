#include "Engine/Maths/Matrix4.hpp"

#include "Engine/Maths/Constants.hpp"

#include <cassert>
#include <cstdlib>

#include <cstdio> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

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

    void Matrix4::show() {
        std::printf("mat4x4((%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f))\n",
            matrixData[0], matrixData[1], matrixData[2], matrixData[3],
            matrixData[4], matrixData[5], matrixData[6], matrixData[7],
            matrixData[8], matrixData[9], matrixData[10], matrixData[11],
            matrixData[12], matrixData[13], matrixData[14], matrixData[15]);
    }

    void Matrix4::show(int row) {
        if (row == 1) {
            std::printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[0], matrixData[1], matrixData[2], matrixData[3]);
        }
        else if (row == 2) {
            std::printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[4], matrixData[5], matrixData[6], matrixData[7]);
        }
        else if (row == 3) {
            std::printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[8], matrixData[9], matrixData[10], matrixData[11]);
        }
        else if (row == 4) {
            std::printf("mat4 matrixData[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[12], matrixData[13], matrixData[14], matrixData[15]);
        }
        else {
            std::printf("Outside of matrix scope\n");
        }
    }

} /* namespace Math */

} /* namespace Engine */
