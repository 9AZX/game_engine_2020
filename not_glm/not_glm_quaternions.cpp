#include "not_glm_quaternions.hpp"
//#include "not_glm_vector.hpp"

namespace NotGLM {
	Quaternion::Quaternion(float uS, Vector3& uV) :s(uS), v(uV) {}

	Quaternion::Quaternion(const Quaternion& value) {
		s = value.s;
		v = value.v;
	};

	Quaternion::~Quaternion() {

	}

	Quaternion& Quaternion::operator=(const Quaternion& value) {

		s = value.s;
		v = value.v;

		return *this;
	};

	void Quaternion::operator+=(const Quaternion& q) {
		s += q.s;
		v += q.v;
	}

	Quaternion Quaternion::operator+(const Quaternion& q)const {
		float scalar = s + q.s;
		Vector3 imaginary = v + q.v;

		return Quaternion(scalar, imaginary);
	}

	void Quaternion::operator-=(const Quaternion& q) {
		s -= q.s;
		v -= q.v;
	}

	Quaternion Quaternion::operator-(const Quaternion& q)const {
		float scalar = s - q.s;
		Vector3 imaginary = v - q.v;

		return Quaternion(scalar, imaginary);
	}

	void Quaternion::operator*=(const Quaternion& q) {
		(*this) = multiply(q);
	}

	Quaternion Quaternion::operator*(const Quaternion& q)const {
		float scalar = s * q.s - v.dot(q.v);

		Vector3 imaginary = q.v * s + v * q.s + v.cross(q.v);

		return Quaternion(scalar, imaginary);
	}

	Quaternion Quaternion::multiply(const Quaternion& q)const {
		float scalar = s * q.s - v.dot(q.v);

		Vector3 imaginary = q.v * s + v * q.s + v.cross(q.v);

		return Quaternion(scalar, imaginary);
	}

	void Quaternion::operator*=(const float value) {
		s *= value;
		v *= value;
	}

	Quaternion Quaternion::operator*(const float value)const {
		float scalar = s * value;
		Vector3 imaginary = v * value;

		return Quaternion(scalar, imaginary);
	}

	float Quaternion::norm() {
		float scalar = s * s;
		float imaginary = v * v;

		return sqrt(scalar + imaginary);
	}

	void Quaternion::normalize() {
		if (norm() != 0) {
			float normValue = 1 / norm();
			s *= normValue;
			v *= normValue;
		}
	}

	Quaternion Quaternion::conjugate() {
		float scalar = s;
		Vector3 imaginary = v * (-1);

		return Quaternion(scalar, imaginary);
	}

	Quaternion Quaternion::inverse() {
		float absoluteValue = norm();
		absoluteValue *= absoluteValue;
		absoluteValue = 1 / absoluteValue;

		Quaternion conjugateValue = conjugate();

		float scalar = conjugateValue.s * absoluteValue;
		Vector3 imaginary = conjugateValue.v * absoluteValue;

		return Quaternion(scalar, imaginary);
	}

	void Quaternion::convertToUnitNormQuaternion() {
		float angle = DegreesToRad(s);
		v.normalize();
		s = cosf(angle * 0.5);
		v = v * sinf(angle * 0.5);
	}
}