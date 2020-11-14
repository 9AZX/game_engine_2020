#pragma once
#ifndef not_glm_matrix4_hpp
#define not_glm_matrix4_hpp

#include <cmath>
#include <iostream>
#include "not_glm_vector.hpp"
#include "not_glm_vector4.hpp"

namespace NotGLM {
	
	class Matrix4 {
		private:

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
	};
}

#endif /* not_glm_matrix4.hpp*/
