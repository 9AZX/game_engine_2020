
#pragma once

#ifndef NOT_GLM_QUATERNIONS_HPP_
#define NOT_GLM_QUATERNIONS_HPP_

#include <cmath>
#include "not_glm_vector.hpp"

class Vector3;
namespace NotGLM {
	class Quaternion {
	public:
		float s;
		Vector3 v;
		Quaternion();
		Quaternion(float uS, Vector3& uV);
		~Quaternion();
		Quaternion(const Quaternion& value);
		Quaternion& operator=(const Quaternion& value);
		void operator+=(const Quaternion& q);
		Quaternion operator+(const Quaternion& q)const;
		void operator-=(const Quaternion& q);
		Quaternion operator-(const Quaternion& q)const;
		void operator*=(const Quaternion& q);
		Quaternion operator*(const Quaternion& q)const;
		Quaternion multiply(const Quaternion& q)const;
		void operator*=(const float value);
		Quaternion operator*(const float value)const;
		float norm();
		void normalize();
		Quaternion conjugate();
		Quaternion inverse();
		void convertToUnitNormQuaternion();
	};
}

#endif /* not_glm_quaternion */