#pragma once

#ifndef ENGINE_MATHS_VECTOR_4_HPP_
#define ENGINE_MATHS_VECTOR_4_HPP_

#include "Engine/Maths/Vector3.hpp"

#include <iostream>

namespace Engine {

namespace Math {

    class Vector4
    {
    private:

    public:
        float x;
        float y;
        float z;
        float w;

        // Constructor to create a 3D vector with zero vector components.
        Vector4();

        Vector4(float setting);

        // Creates a vector with the given x, yand z components
        Vector4(float uX, float uY, float uZ, float uW);

        // Vector desctructor
        ~Vector4();

        // Copies the values of the vector
        Vector4(const Vector4& v);

        // Copies the values of the vector
        Vector4& operator=(const Vector4& v);

        // Resultant of two vectors.
        void operator+=(const Vector4& v);
        // Returns a third vector representing the addition of two 3D vectors
        Vector4 operator+(const Vector4& v)const;

        // Subtraction result of two vectors
        void operator-=(const Vector4& v);
        // Returns a third vector representing the subtraction of two 3D vectors
        Vector4 operator-(const Vector4& v)const;

        // Product of multiplication
        void operator*=(const float s);
        // Vector representing product
        Vector4 operator*(const float s)const;

        // Quotient of division
        void operator /=(const float s);
        // Quotient of division
        Vector4 operator/(const float s)const;

        // dot product
        float operator*(const Vector4& v) const;
        float dot(const Vector4& v) const;

        // Returns the angle between vectors in degrees
        float angle(const Vector4& v);

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
        const float getW() const { return w; }

        void setX(const float _x) { x = _x; }
        void setY(const float _y) { y = _y; }
        void setZ(const float _z) { z = _z; }
        void setW(const float _w) { w = _w; }
    };

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_VECTOR_4_HPP_ */