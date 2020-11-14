#pragma once
#ifndef not_glm_matrix4x3_hpp
#define not_glm_matrix4x3_hpp

#include <cmath>
#include <iostream>
#include "not_glm_vector.hpp"
#include "not_glm_vector4.hpp"

namespace NotGLM {

	class Matrix4x3 {
	private:

	public:
		float matrixData[12] = { 0.0f };
		Matrix4x3();
		Matrix4x3(float m0);
		Matrix4x3(float m0, float m3, float m6, float m9, float m1, float m4, float m7, float m10, float m2, float m5, float m8, float m11);

		Matrix4x3& operator=(const Matrix4x3& value);

		~Matrix4x3();

		Matrix4x3 operator+(const Matrix4x3& m) const;
		void operator+=(const Matrix4x3& m);

		Matrix4x3 operator*(const float s) const;
		void operator*=(const float s);

		Vector4 operator*(const Vector4& v) const;
		Vector4 transformVectorByMatrix(const Vector4& v) const;

		void setMatrixAsIdentityMatrix();

		void show();
		void show(int row);
	};
}

#endif /* not_glm_matrix4x3.hpp*/