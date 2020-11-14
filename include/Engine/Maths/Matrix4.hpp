#pragma once

#ifndef ENGINE_MATHS_MATRIX_4_HPP_
#define ENGINE_MATHS_MATRIX_4_HPP_

#include "Engine/Maths/Vector3.hpp"
#include "Engine/Maths/Vector4.hpp"

#include <cmath>

namespace Engine {

namespace Math {

class Matrix4 {
	public:
		float matrixData[16] = { 0.0f };
		Matrix4();
		Matrix4(float m0);
		Matrix4(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15);

		Matrix4& operator=(const Matrix4& value);

		~Matrix4();

		Matrix4 operator+(const Matrix4& m) const;
		void operator+=(const Matrix4& m);

		Matrix4 operator*(const float s) const;
		void operator*=(const float s);

		Vector4 operator*(const Vector4& v) const;
		Vector4 transformVectorByMatrix(const Vector4& v) const;

		Matrix4 operator*(const Matrix4& m) const;
		void operator*=(const Matrix4& m);

		void setMatrixAsIdentityMatrix();

		/*void setMatrixAsInverseOfGivenMatrix(const Matrix4& m);
		Matrix4 getInverseOfMatrix() const;
		void invertMatrix();

		float getMatrixDeterminant() const;

		void setMatrixAsTransposeOfGivenMatrix(const Matrix4& m);
		Matrix4 getTransposeOfMatrix() const;

		void invertAndTransposeMatrix();

		void makeRotationMatrixAboutXAxisByAngle(float uAngle);
		void makeRotationMatrixAboutYAxisByAngle(float uAngle);
		void makeRotationMatrixAboutZAxisByAngle(float uAngle);

		void transformMatrixAboutXAxisByAngle(float uAngle);
		void transformMatrixAboutYAxisByAngle(float uAngle);
		void transformMatrixAboutZAxisByAngle(float uAngle);*/

		void show();
		void show(int row);
}; /* class Matrix4 */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_MATRIX_4_HPP_ */
