#pragma once

#ifndef ENGINE_MATHS_VECTOR_2_HPP_
#define ENGINE_MATHS_VECTOR_2_HPP_

#include "Engine/Maths/Constants.hpp"

#include <cmath>

namespace Engine {

namespace Math {

class Vector2 {
    public:
        float x;
        float y;

        // Constructor to create a 3D vector with zero vector components.
        Vector2();

        // Creates a vector with the given x, yand z components
        Vector2(float uX, float uY);

        // Vector desctructor
        ~Vector2();

        // Copies the values of the vector
        Vector2(const Vector2& v);

        // Copies the values of the vector
        Vector2& operator=(const Vector2& v);

        // Resultant of two vectors.
        void operator+=(const Vector2& v);
        // Returns a third vector representing the addition of two 3D vectors
        Vector2 operator+(const Vector2& v)const;

        // Subtraction result of two vectors
        void operator-=(const Vector2& v);
        // Returns a third vector representing the subtraction of two 3D vectors
        Vector2 operator-(const Vector2& v)const;

        // Product of multiplication
        void operator*=(const float s);
        // Vector representing product
        Vector2 operator*(const float s)const;

        // Quotient of division
        void operator /=(const float s);
        // Quotient of division
        Vector2 operator/(const float s)const;

        // dot product
        float operator*(const Vector2& v) const;
        float dot(const Vector2& v) const;

        bool operator == (const Vector2 & other) const noexcept;

        // Returns the angle between vectors in degrees
        float angle(const Vector2& v);

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

        void setX(const float _x) { x = _x; }
        void setY(const float _y) { y = _y; }
}; /* class Vector2 */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_VECTOR_2_HPP_ */
