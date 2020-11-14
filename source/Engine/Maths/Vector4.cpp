#include "Engine/Maths/Vector4.hpp"

#include "Engine/Maths/Constants.hpp"

#include <cassert>
#include <cstdlib>

#include <cstdio> // TODO remove this and specialize fmt::formatter
#include <iostream> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

	// constructors
	Vector4::Vector4(void) : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Vector4::Vector4(float setting) : x(setting), y(setting), z(setting), w(setting) {}
	Vector4::Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

	// deconstructor
	Vector4::~Vector4() {}

	const Vector4 Vector4::ZERO_VECTOR(0, 0, 0, 0);

	// constructor that makes a Vector4 from a Vector3
	Vector4::Vector4(const Vector3& val) : x(val.getX()), y(val.getY()), z(val.getZ()), w(1) {}

	// addition operator for vectors
	Vector4& Vector4::operator+=(const Vector4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	// calculates the angle in radians between a and b
	float Vector4::angleBetween(const Vector4& a, const Vector4& b) {
		float dotProd = a.dotProduct(b);
		float aLength = a.magnitude();
		float bLength = b.magnitude();

		// They've passed in the zero vector.
		if (BasicMath::approxEqual(aLength, 0.0f) ||
			BasicMath::approxEqual(bLength, 0.0f)) {
			return 0.0f;
		}
		else {
			return acos(dotProd / (aLength * bLength));
		}
	}

	// addition operator
	const Vector4 Vector4::operator+(const Vector4& rhs) const {
		// Make a copy
		Vector4 result = *this;
		result += rhs;
		return result;
	}

	// subtraction operator
	Vector4& Vector4::operator-=(const Vector4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	// subtraction operator
	const Vector4 Vector4::operator-(const Vector4& rhs) const {
		// Make a copy
		Vector4 result = *this;
		result -= rhs;
		return result;
	}



	// multiplication operator for scalar and vector
	Vector4& Vector4::operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	// two vectors are the same if they have the same x, y, z, and w magnitude.
	const bool Vector4::operator==(const Vector4& other) const {
		return	BasicMath::approxEqual(x, other.x) &&
			BasicMath::approxEqual(y, other.y) &&
			BasicMath::approxEqual(z, other.z) &&
			BasicMath::approxEqual(w, other.w);
	}

	const bool Vector4::operator!=(const Vector4& other) const {
		return !((*this) == other);
	}

	// dot product between two vectors.
	const float Vector4::dotProduct(const Vector4& rhs) const {
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
	}

	// return the length (magnitude) of the vector.
	const float Vector4::magnitude() const {
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	// return a vector of unit length that points in the same direction as this vector.
	const Vector4 Vector4::normalize() {
		float length = magnitude();
		assert(length != 0.0f);
		return Vector4(x / length,
			y / length,
			z / length,
			w / length);
	}

	// show
	void Vector4::show()
	{
		std::printf("vec3(%.6f, %.6f, %.6f, , %.6f)\n", x, y, z, w);
	}

	void Vector4::show(char coordinate)
	{
		if (coordinate == 'x') {
			std::printf("vec3.x = %.6f\n", x);
		}
		else if (coordinate == 'y') {
			std::printf("vec3.y = %.6f\n", y);
		}
		else if (coordinate == 'z') {
			std::printf("vec3.z = %.6f\n", z);
		}
		else if (coordinate == 'w') {
			std::printf("vec3.w = %.6f\n", w);
		}
		else {
			std::printf("Out of vector scope\n");
		}
	}
} /* namespace Math */

} /* namespace Engine */
