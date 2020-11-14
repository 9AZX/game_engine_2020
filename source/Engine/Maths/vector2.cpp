#include "Engine/Maths/Vector2.hpp"

#include "Engine/Maths/Quaternions.hpp"

#include <cstdio> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

    // constructor
    Vector2::Vector2() :x(0.0), y(0.0) {};
    Vector2::Vector2(float uX, float uY) :x(uX), y(uY) {}

    // destructor
    Vector2::~Vector2() {}

    // copy constructors
    Vector2::Vector2(const Vector2& v) : x(v.x), y(v.y) {}

    Vector2& Vector2::operator=(const Vector2& v)
    {
        x = v.x;
        y = v.y;

        return *this;
    }

    // add
    void Vector2::operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
    }

    Vector2 Vector2::operator+(const Vector2& v)const
    {
        return Vector2(x + v.x, y + v.y);
    }

    // subtract
    void Vector2::operator-=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
    }

    Vector2 Vector2::operator-(const Vector2& v)const
    {
        return Vector2(x - v.x, y - v.y);
    }

    // multiply
    void Vector2::operator*=(const float s)
    {
        x *= s;
        y *= s;
    }

    Vector2 Vector2::operator*(const float s) const
    {
        return Vector2(s * x, s * y);
    }

    // divide
    void Vector2::operator /=(const float s)
    {
        x = x / s;
        y = y / s;
    }

    Vector2 Vector2::operator/(const float s)const
    {
        return Vector2(x / s, y / s);
    }

    // dot product
    float Vector2::operator*(const Vector2& v) const
    {
        return x * v.x + y * v.y;
    }

    float Vector2::dot(const Vector2& v) const
    {
        return x * v.x + y * v.y;
    }

    bool Vector2::operator == (const Vector2 & other) const noexcept
    {
        return x == other.x && y == other.y;
    }

    // Angle between vectors
    float Vector2::angle(const Vector2& v)
    {

        float theta;

        Vector2 u = v;
        Vector2 m = *this;

        theta = dot(u) / (m.magnitude() * u.magnitude());

        theta = RadToDegrees(acos(theta));

        return theta;

    }

    // conjugate
    void Vector2::conjugate()
    {
        x = -1 * x;
        y = -1 * y;
    }

    // normalize
    void Vector2::normalize()
    {
        float mag = std::sqrt(x * x + y * y);

        if (mag > 0.0f)
        {
            float oneOverMag = 1.0f / mag;

            x = x * oneOverMag;
            y = y * oneOverMag;
        }
    }

    // magnitude
    float Vector2::magnitude()
    {
        float magnitude = std::sqrt(x * x + y * y);

        return magnitude;

    }

    float Vector2::magnitudeSquare()
    {
        float magnitude = x * x + y * y;

        return magnitude;
    }

    // clear
    void Vector2::zero()
    {
        x = 0;
        y = 0;
    }

    void Vector2::absolute()
    {
        x = std::abs(x);
        y = std::abs(y);
    }

    // show
    void Vector2::show()
    {
        std::printf("vec2(%.6f, %.6f)\n", x, y);
    }

    void Vector2::show(char coordinate)
    {
        if (coordinate == 'x') {
            std::printf("vec2.x = %.6f\n", x);
        }
        else if (coordinate == 'y') {
            std::printf("vec2.y = %.6f\n", y);
        }
        else {
            std::printf("Out of vector scope\n");
        }
    }

    void Vector2::negate()
    {
        x = -1 * x;
        y = -1 * y;
    }

} /* namespace Math */

} /* namespace Engine */
