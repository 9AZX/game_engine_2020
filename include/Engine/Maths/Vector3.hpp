#pragma once

#ifndef ENGINE_MATHS_VECTOR_3_HPP_
#define ENGINE_MATHS_VECTOR_3_HPP_

#include "Engine/Maths/Constants.hpp"

#include <cmath>

namespace Engine {

namespace Math {

class Vector3 {
    public:
        float x;
        float y;
        float z;

        // Constructor to create a 3D vector with zero vector components.
        Vector3();
        Vector3(float setting);

        // Creates a vector with the given x, yand z components
        Vector3(float uX, float uY, float uZ);

        // Vector desctructor
        ~Vector3();

        // Copies the values of the vector
        Vector3(const Vector3& v);

        // Copies the values of the vector
        Vector3& operator=(const Vector3& v);

        // Resultant of two vectors.
        void operator+=(const Vector3& v);
        // Returns a third vector representing the addition of two 3D vectors
        Vector3 operator+(const Vector3& v)const;

        // Subtraction result of two vectors
        void operator-=(const Vector3& v);
        // Returns a third vector representing the subtraction of two 3D vectors
        Vector3 operator-(const Vector3& v)const;

        // Product of multiplication
        void operator*=(const float s);
        // Vector representing product
        Vector3 operator*(const float s)const;

        // Quotient of division
        void operator /=(const float s);
        // Quotient of division
        Vector3 operator/(const float s)const;

        // dot product
        float operator*(const Vector3& v) const;
        float dot(const Vector3& v) const;

        bool operator == (const Vector3 & other) const noexcept;

        // Returns the angle between vectors in degrees
        float angle(const Vector3& v);

        // Cross product result
        void operator %=(const Vector3& v);
        // Cross product result
        Vector3 operator %(const Vector3& v) const;
        // Cross product result
        Vector3 cross(const Vector3& v) const;

        // rotate Vector
        Vector3 rotateVectorAboutAngleAndAxis(float uAngle, Vector3& uAxis);

        // Conjugate the vector
        void conjugate();
        //  Normalize the vector
        void normalize();
        // Magnitude value
        float magnitude();
        // Magnitude squared value
        float magnitudeSquare();
        // Convert vector to a zero vector
        void zero();
        // Calculate absolute value of vector
        void absolute();
        //  Print vector components
        void show();
        void show(char coordinate);
        // Negate all components
        void negate();

        const float getX() const { return x; }
        const float getY() const { return y; }
        const float getZ() const { return z; }

        void setX(const float _x) { x = _x; }
        void setY(const float _y) { y = _y; }
        void setZ(const float _z) { z = _z; }
}; /* class Vector3 */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_VECTOR_3_HPP_ */
