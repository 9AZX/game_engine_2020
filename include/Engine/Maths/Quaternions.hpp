#pragma once

#ifndef ENGINE_MATHS_QUATERNIONS_HPP_
#define ENGINE_MATHS_QUATERNIONS_HPP_

#include "Engine/Maths/Vector3.hpp"

#include <cmath>

namespace Engine {

namespace Math {

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
}; /* namespace Quaternion */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_QUATERNIONS_HPP_ */
