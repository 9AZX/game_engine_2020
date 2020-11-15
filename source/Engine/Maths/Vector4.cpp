#include "Engine/Maths/Vector4.hpp"

#include "Engine/Maths/Constants.hpp"

#include <cassert>
#include <cstdlib>

#include <cstdio> // TODO remove this and specialize fmt::formatter
#include <iostream> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

    // constructor
    Vector4::Vector4() :x(0.0), y(0.0), z(0.0), w(1.0) {};
    Vector4::Vector4(float content) : x(content), y(content), z(content), w(content) {};
    Vector4::Vector4(float uX, float uY, float uZ, float uW) :x(uX), y(uY), z(uZ), w(uW) {}

    // destructor
    Vector4::~Vector4() {}

    // copy constructors 
    Vector4::Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    Vector4& Vector4::operator=(const Vector4& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;

        return *this;
    }

    // add
    void Vector4::operator+=(const Vector4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }

    Vector4 Vector4::operator+(const Vector4& v)const
    {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    // subtract
    void Vector4::operator-=(const Vector4& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
    }

    Vector4 Vector4::operator-(const Vector4& v)const
    {
        return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    // multiply
    void Vector4::operator*=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
    }

    Vector4 Vector4::operator*(const float s) const
    {
        return Vector4(s * x, s * y, s * z, s * w);
    }

    // divide
    void Vector4::operator /=(const float s)
    {
        x = x / s;
        y = y / s;
        z = z / s;
        w = w / s;
    }

    Vector4 Vector4::operator/(const float s)const
    {
        return Vector4(x / s, y / s, z / s, w / s);
    }

    // dot product
    float Vector4::operator*(const Vector4& v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    float Vector4::dot(const Vector4& v) const
    {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    // Angle between vectors
    float Vector4::angle(const Vector4& v)
    {

        float theta;

        Vector4 u = v;
        Vector4 m = *this;

        theta = dot(u) / (m.magnitude() * u.magnitude());

        theta = RadToDegrees(acos(theta));

        return theta;

    }

    // conjugate
    void Vector4::conjugate()
    {
        x = -1 * x;
        y = -1 * y;
        z = -1 * z;
        w = -1 * w;
    }

    // normalize
    void Vector4::normalize()
    {
        float mag = std::sqrt(x * x + y * y + z * z + w * w);

        if (mag > 0.0f)
        {
            float oneOverMag = 1.0f / mag;

            x = x * oneOverMag;
            y = y * oneOverMag;
            z = z * oneOverMag;
            w = w * oneOverMag;

        }
    }

    // magnitude
    float Vector4::magnitude()
    {
        float magnitude = std::sqrt(x * x + y * y + z * z + w * w);

        return magnitude;

    }

    float Vector4::magnitudeSquare()
    {
        float magnitude = x * x + y * y + z * z + w * w;

        return magnitude;
    }

    // clear
    void Vector4::zero()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    void Vector4::absolute()
    {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);
        w = std::abs(w);
    }

    // show
    void Vector4::show()
    {
        printf("vec4(%.6f, %.6f, %.6f, %.6f)\n", x, y, z, w);
    }

    void Vector4::show(char coordinate)
    {
        if (coordinate == 'x') {
            printf("vec4.x = %.6f\n", x);
        }
        else if (coordinate == 'y') {
            printf("vec4.y = %.6f\n", y);
        }
        else if (coordinate == 'z') {
            printf("vec4.z = %.6f\n", z);
        }
        else if (coordinate == 'w') {
            printf("vec4.w = %.6f\n", w);
        }
        else {
            printf("Out of vector scope\n");
        }
    }

    void Vector4::negate()
    {
        x = -1 * x;
        y = -1 * y;
        z = -1 * z;
        w = -1 * w;
    }
} /* namespace Math */

} /* namespace Engine */
