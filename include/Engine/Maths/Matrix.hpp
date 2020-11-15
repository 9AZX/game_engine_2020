#pragma once

#ifndef ENGINE_MATHS_MATRIX_HPP_
#define ENGINE_MATHS_MATRIX_HPP_

#include "Engine/Maths/Vector3.hpp"

#include <cmath>

namespace Engine {

namespace Math {

class Matrix3d {
	public:
		float matrixData[9]={0.0};
		Matrix3d();
		Matrix3d(float m0);
		Matrix3d(float m0, float m3, float m6, float m1, float m4, float m7, float m2, float m5, float m8);

		Matrix3d& operator=(const Matrix3d& value);

		~Matrix3d();

		Matrix3d operator+(const Matrix3d& m) const;
		void operator+=(const Matrix3d& m);

		Matrix3d operator*(const float s) const;
		void operator*=(const float s);

		Vector3 operator*(const Vector3& v) const;
		Vector3 transformVectorByMatrix(const Vector3& v) const;

		Matrix3d operator*(const Matrix3d& m) const;
		void operator*=(const Matrix3d& m);
		
		float* getRow(int row);

		void setMatrixAsIdentityMatrix();

		void setMatrixAsInverseOfGivenMatrix(const Matrix3d& m);
		Matrix3d getInverseOfMatrix() const;
		void invertMatrix();

		float getMatrixDeterminant() const;

		void setMatrixAsTransposeOfGivenMatrix(const Matrix3d& m);
		Matrix3d getTransposeOfMatrix() const;

		void invertAndTransposeMatrix();

		void makeRotationMatrixAboutXAxisByAngle(float uAngle);
		void makeRotationMatrixAboutYAxisByAngle(float uAngle);
		void makeRotationMatrixAboutZAxisByAngle(float uAngle);

		void transformMatrixAboutXAxisByAngle(float uAngle);
		void transformMatrixAboutYAxisByAngle(float uAngle);
		void transformMatrixAboutZAxisByAngle(float uAngle);

		void show();
		void show(int row);
}; /* class Matrix3D */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_MATRIX_HPP_ */
