#include "Engine/Maths/Matrix4.hpp"

#include "Engine/Maths/Constants.hpp"

#include <cassert>
#include <cstdlib>

#include <cstdio> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

    Matrix4::Matrix4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrixData[i][j] = 0.0f;
            }
        }
    };

    Matrix4::Matrix4(float m0) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrixData[i][j] = 0.0f;
            }
        }
        matrixData[0][0] = matrixData[1][1] = matrixData[2][2] = matrixData[3][3] = m0;
    };

    Matrix4::Matrix4(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15) {
        matrixData[0][0] = m0;
        matrixData[1][0] = m4;
        matrixData[2][0] = m8;
        matrixData[3][0] = m12;

        matrixData[0][1] = m1;
        matrixData[1][1] = m5;
        matrixData[2][1] = m9;
        matrixData[3][1] = m13;

        matrixData[0][2] = m2;
        matrixData[1][2] = m6;
        matrixData[2][2] = m10;
        matrixData[3][2] = m14;

        matrixData[0][3] = m3;
        matrixData[1][3] = m7;
        matrixData[2][3] = m11;
        matrixData[3][3] = m15;
    };

    Matrix4& Matrix4::operator=(const Matrix4& value) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrixData[i][j] = value.matrixData[i][j];
            }
        }

        return *this;
    };

    Matrix4::~Matrix4() {

    };

    Matrix4 Matrix4::operator+(const Matrix4& m) const {
        Matrix4 n;

        n.matrixData[0][0] = matrixData[0][0] + m.matrixData[0][0];
        n.matrixData[1][0] = matrixData[1][0] + m.matrixData[1][0];
        n.matrixData[2][0] = matrixData[2][0] + m.matrixData[2][0];
        n.matrixData[3][0] = matrixData[3][0] + m.matrixData[3][0];

        n.matrixData[0][1] = matrixData[1][1] + m.matrixData[1][1];
        n.matrixData[1][1] = matrixData[1][1] + m.matrixData[1][1];
        n.matrixData[2][1] = matrixData[2][1] + m.matrixData[2][1];
        n.matrixData[3][1] = matrixData[3][1] + m.matrixData[3][1];

        n.matrixData[0][2] = matrixData[0][2] + m.matrixData[0][2];
        n.matrixData[1][2] = matrixData[1][2] + m.matrixData[1][2];
        n.matrixData[2][2] = matrixData[2][2] + m.matrixData[2][2];
        n.matrixData[3][2] = matrixData[3][2] + m.matrixData[3][2];

        n.matrixData[0][3] = matrixData[0][3] + m.matrixData[0][3];
        n.matrixData[1][3] = matrixData[1][3] + m.matrixData[1][3];
        n.matrixData[2][3] = matrixData[2][3] + m.matrixData[2][3];
        n.matrixData[3][3] = matrixData[3][3] + m.matrixData[3][3];

        return n;
    };

    void Matrix4::operator+=(const Matrix4& m) {
        matrixData[0][0] += m.matrixData[0][0];
        matrixData[1][0] += m.matrixData[1][0];
        matrixData[2][0] += m.matrixData[2][0];
        matrixData[3][0] += m.matrixData[3][0];

        matrixData[0][1] += m.matrixData[0][1];
        matrixData[1][1] += m.matrixData[1][1];
        matrixData[2][1] += m.matrixData[2][1];
        matrixData[3][1] += m.matrixData[3][1];

        matrixData[0][2] += m.matrixData[0][2];
        matrixData[1][2] += m.matrixData[1][2];
        matrixData[2][2] += m.matrixData[2][2];
        matrixData[3][2] += m.matrixData[3][2];

        matrixData[0][3] += m.matrixData[0][3];
        matrixData[1][3] += m.matrixData[1][3];
        matrixData[2][3] += m.matrixData[2][3];
        matrixData[3][3] += m.matrixData[3][3];
    };

    Matrix4 Matrix4::operator*(const float s) const {
        Matrix4 n;

        n.matrixData[0][0] = matrixData[0][0] * s;
        n.matrixData[1][0] = matrixData[1][0] * s;
        n.matrixData[2][0] = matrixData[2][0] * s;
        n.matrixData[3][0] = matrixData[3][0] * s;

        n.matrixData[0][1] = matrixData[0][1] * s;
        n.matrixData[1][1] = matrixData[1][1] * s;
        n.matrixData[2][1] = matrixData[2][1] * s;
        n.matrixData[3][1] = matrixData[3][1] * s;

        n.matrixData[0][2] = matrixData[0][2] * s;
        n.matrixData[1][2] = matrixData[1][2] * s;
        n.matrixData[2][2] = matrixData[2][2] * s;
        n.matrixData[3][2] = matrixData[3][2] * s;

        n.matrixData[0][3] = matrixData[0][3] * s;
        n.matrixData[1][3] = matrixData[1][3] * s;
        n.matrixData[2][3] = matrixData[2][3] * s;
        n.matrixData[3][3] = matrixData[3][3] * s;

        return n;
    };

    void Matrix4::operator*=(const float s) {
        matrixData[0][0] *= s;
        matrixData[1][0] *= s;
        matrixData[2][0] *= s;
        matrixData[3][0] *= s;

        matrixData[0][1] *= s;
        matrixData[1][1] *= s;
        matrixData[2][1] *= s;
        matrixData[3][1] *= s;

        matrixData[0][2] *= s;
        matrixData[1][2] *= s;
        matrixData[2][2] *= s;
        matrixData[3][2] *= s;

        matrixData[0][3] *= s;
        matrixData[1][3] *= s;
        matrixData[2][3] *= s;
        matrixData[3][3] *= s;
    };

    Vector4 Matrix4::operator*(const Vector4& v) const {
        return Vector4(
            matrixData[0][0] * v.x + matrixData[1][0] * v.y + matrixData[2][0] * v.z + matrixData[3][0] * v.w,
            matrixData[0][1] * v.x + matrixData[1][1] * v.y + matrixData[2][1] * v.z + matrixData[3][1] * v.w,
            matrixData[0][2] * v.x + matrixData[1][2] * v.y + matrixData[2][2] * v.z + matrixData[3][2] * v.w,
            matrixData[0][3] * v.x + matrixData[1][3] * v.y + matrixData[2][3] * v.z + matrixData[3][3] * v.w);
    }

    Vector4 Matrix4::transformVectorByMatrix(const Vector4& v) const {
        return(*this) * v;
    }

    Matrix4 Matrix4::operator*(const Matrix4& m) const {
        return Matrix4(
            matrixData[0][0] * m.matrixData[0][0] + matrixData[1][0] * m.matrixData[0][1] + matrixData[2][0] * m.matrixData[0][2] + matrixData[3][0] * m.matrixData[0][3],
            matrixData[0][0] * m.matrixData[1][0] + matrixData[1][0] * m.matrixData[1][1] + matrixData[2][0] * m.matrixData[1][2] + matrixData[3][0] * m.matrixData[1][3],
            matrixData[0][0] * m.matrixData[2][0] + matrixData[1][0] * m.matrixData[2][1] + matrixData[2][0] * m.matrixData[2][2] + matrixData[3][0] * m.matrixData[2][3],
            matrixData[0][0] * m.matrixData[3][0] + matrixData[1][0] * m.matrixData[3][1] + matrixData[2][0] * m.matrixData[3][2] + matrixData[3][0] * m.matrixData[3][3],

            matrixData[0][1] * m.matrixData[0][0] + matrixData[1][1] * m.matrixData[0][1] + matrixData[2][1] * m.matrixData[0][2] + matrixData[3][1] * m.matrixData[0][3],
            matrixData[0][1] * m.matrixData[1][0] + matrixData[1][1] * m.matrixData[1][1] + matrixData[2][1] * m.matrixData[1][2] + matrixData[3][1] * m.matrixData[1][3],
            matrixData[0][1] * m.matrixData[2][0] + matrixData[1][1] * m.matrixData[2][1] + matrixData[2][1] * m.matrixData[2][2] + matrixData[3][1] * m.matrixData[2][3],
            matrixData[0][1] * m.matrixData[3][0] + matrixData[1][1] * m.matrixData[3][1] + matrixData[2][1] * m.matrixData[3][2] + matrixData[3][1] * m.matrixData[3][3],

            matrixData[0][2] * m.matrixData[0][0] + matrixData[1][2] * m.matrixData[0][1] + matrixData[2][2] * m.matrixData[0][2] + matrixData[3][2] * m.matrixData[0][3],
            matrixData[0][2] * m.matrixData[1][0] + matrixData[1][2] * m.matrixData[1][1] + matrixData[2][2] * m.matrixData[1][2] + matrixData[3][2] * m.matrixData[1][3],
            matrixData[0][2] * m.matrixData[2][0] + matrixData[1][2] * m.matrixData[2][1] + matrixData[2][2] * m.matrixData[2][2] + matrixData[3][2] * m.matrixData[2][3],
            matrixData[0][2] * m.matrixData[3][0] + matrixData[1][2] * m.matrixData[3][1] + matrixData[2][2] * m.matrixData[3][2] + matrixData[3][2] * m.matrixData[3][3],

            matrixData[0][3] * m.matrixData[0][0] + matrixData[1][3] * m.matrixData[0][1] + matrixData[2][3] * m.matrixData[0][2] + matrixData[3][3] * m.matrixData[0][3],
            matrixData[0][3] * m.matrixData[1][0] + matrixData[1][3] * m.matrixData[1][1] + matrixData[2][3] * m.matrixData[1][2] + matrixData[3][3] * m.matrixData[1][3],
            matrixData[0][3] * m.matrixData[2][0] + matrixData[1][3] * m.matrixData[2][1] + matrixData[2][3] * m.matrixData[2][2] + matrixData[3][3] * m.matrixData[2][3],
            matrixData[0][3] * m.matrixData[3][0] + matrixData[1][3] * m.matrixData[3][1] + matrixData[2][3] * m.matrixData[3][2] + matrixData[3][3] * m.matrixData[3][3]);
    }

    void Matrix4::operator*=(const Matrix4& m) {
        float t1;
        float t2;
        float t3;
        float t4;

        t1 = matrixData[0][0] * m.matrixData[0][0] + matrixData[1][0] * m.matrixData[0][1] + matrixData[2][0] * m.matrixData[0][2] + matrixData[3][0] * m.matrixData[0][3];
        t2 = matrixData[0][0] * m.matrixData[1][0] + matrixData[1][0] * m.matrixData[1][1] + matrixData[2][0] * m.matrixData[1][2] + matrixData[3][0] * m.matrixData[1][3];
        t3 = matrixData[0][0] * m.matrixData[2][0] + matrixData[1][0] * m.matrixData[2][1] + matrixData[2][0] * m.matrixData[2][2] + matrixData[3][0] * m.matrixData[2][3];
        t4 = matrixData[0][0] * m.matrixData[3][0] + matrixData[1][0] * m.matrixData[3][1] + matrixData[2][0] * m.matrixData[3][2] + matrixData[3][0] * m.matrixData[3][3];

        matrixData[0][0] = t1;
        matrixData[1][0] = t2;
        matrixData[2][0] = t3;
        matrixData[3][0] = t4;

        t1 = matrixData[0][1] * m.matrixData[0][0] + matrixData[1][1] * m.matrixData[0][1] + matrixData[2][1] * m.matrixData[0][2] + matrixData[3][1] * m.matrixData[0][3];
        t2 = matrixData[0][1] * m.matrixData[1][0] + matrixData[1][1] * m.matrixData[1][1] + matrixData[2][1] * m.matrixData[1][2] + matrixData[3][1] * m.matrixData[1][3];
        t3 = matrixData[0][1] * m.matrixData[2][0] + matrixData[1][1] * m.matrixData[2][1] + matrixData[2][1] * m.matrixData[2][2] + matrixData[3][1] * m.matrixData[2][3];
        t4 = matrixData[0][1] * m.matrixData[3][0] + matrixData[1][1] * m.matrixData[3][1] + matrixData[2][1] * m.matrixData[3][2] + matrixData[3][1] * m.matrixData[3][3];

        matrixData[0][1] = t1;
        matrixData[1][1] = t2;
        matrixData[2][1] = t3;
        matrixData[3][1] = t4;


        t1 = matrixData[0][2] * m.matrixData[0][0] + matrixData[1][2] * m.matrixData[0][1] + matrixData[2][2] * m.matrixData[0][2] + matrixData[3][2] * m.matrixData[0][3];
        t2 = matrixData[0][2] * m.matrixData[1][0] + matrixData[1][2] * m.matrixData[1][1] + matrixData[2][2] * m.matrixData[1][2] + matrixData[3][2] * m.matrixData[1][3];
        t3 = matrixData[0][2] * m.matrixData[2][0] + matrixData[1][2] * m.matrixData[2][1] + matrixData[2][2] * m.matrixData[2][2] + matrixData[3][2] * m.matrixData[2][3];
        t4 = matrixData[0][2] * m.matrixData[3][0] + matrixData[1][2] * m.matrixData[3][1] + matrixData[2][2] * m.matrixData[3][2] + matrixData[3][2] * m.matrixData[3][3];

        matrixData[0][2] = t1;
        matrixData[1][2] = t2;
        matrixData[2][2] = t3;
        matrixData[3][2] = t4;

        t1 = matrixData[0][3] * m.matrixData[0][0] + matrixData[1][3] * m.matrixData[0][1] + matrixData[2][3] * m.matrixData[0][2] + matrixData[3][3] * m.matrixData[0][3];
        t2 = matrixData[0][3] * m.matrixData[1][0] + matrixData[1][3] * m.matrixData[1][1] + matrixData[2][3] * m.matrixData[1][2] + matrixData[3][3] * m.matrixData[1][3];
        t3 = matrixData[0][3] * m.matrixData[2][0] + matrixData[1][3] * m.matrixData[2][1] + matrixData[2][3] * m.matrixData[2][2] + matrixData[3][3] * m.matrixData[2][3];
        t4 = matrixData[0][3] * m.matrixData[3][0] + matrixData[1][3] * m.matrixData[3][1] + matrixData[2][3] * m.matrixData[3][2] + matrixData[3][3] * m.matrixData[3][3];

        matrixData[0][3] = t1;
        matrixData[1][3] = t2;
        matrixData[2][3] = t3;
        matrixData[3][3] = t4;
    }

    void Matrix4::setMatrixAsIdentityMatrix() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrixData[i][j] = 0.0f;
            }
        }

        matrixData[0][0] = matrixData[1][1] = matrixData[2][2] = matrixData[3][3] = 1.0f;
    }

    void Matrix4::show() {
        printf("mat4x4((%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f), (%.6f, %.6f, %.6f, %.6f))\n",
            matrixData[0][0], matrixData[0][1], matrixData[0][2], matrixData[0][3],
            matrixData[1][0], matrixData[1][1], matrixData[1][2], matrixData[1][3],
            matrixData[2][0], matrixData[2][1], matrixData[2][2], matrixData[2][3],
            matrixData[3][0], matrixData[3][1], matrixData[3][2], matrixData[3][3]);
    }

    void Matrix4::show(int row) {
        if (row == 0) {
            printf("vec4 row[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[0][0], matrixData[0][1], matrixData[0][2], matrixData[0][3]);
        }
        else if (row == 1) {
            printf("vec4 row[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[1][0], matrixData[1][1], matrixData[1][2], matrixData[1][3]);
        }
        else if (row == 2) {
            printf("vec4 row[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[2][0], matrixData[2][1], matrixData[2][2], matrixData[2][3]);
        }
        else if (row == 3) {
            printf("vec4 row[%d] = (%.6f, %.6f, %.6f, %.6f)\n", row, matrixData[3][0], matrixData[3][1], matrixData[3][2], matrixData[3][3]);
        }
        else {
            printf("Outside of matrix scope\n");
        }
    }

} /* namespace Math */

} /* namespace Engine */
