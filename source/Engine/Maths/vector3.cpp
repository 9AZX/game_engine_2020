#include "Engine/Maths/Vector3.hpp"

#include "Engine/Maths/quaternions.hpp"

#include <cstdio> // TODO remove this and specialize fmt::formatter

namespace Engine {

namespace Math {

    // constructor
    Vector3::Vector3() :x(0.0), y(0.0), z(0.0) {};
    Vector3::Vector3(float setting) :x(setting), y(setting), z(setting) {}
    Vector3::Vector3(float uX, float uY, float uZ) :x(uX), y(uY), z(uZ) {}

    // destructor
    Vector3::~Vector3() {}

    // copy constructors
    Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    Vector3& Vector3::operator=(const Vector3& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    // add
    void Vector3::operator+=(const Vector3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    Vector3 Vector3::operator+(const Vector3& v)const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    // subtract
    void Vector3::operator-=(const Vector3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    Vector3 Vector3::operator-(const Vector3& v)const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    // multiply
    void Vector3::operator*=(const float s)
    {
        x *= s;
        y *= s;
        z *= s;
    }

    Vector3 Vector3::operator*(const float s) const
    {
        return Vector3(s * x, s * y, s * z);
    }

    // divide
    void Vector3::operator /=(const float s)
    {
        x = x / s;
        y = y / s;
        z = z / s;
    }

    Vector3 Vector3::operator/(const float s)const
    {
        return Vector3(x / s, y / s, z / s);
    }

    // dot product
    float Vector3::operator*(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    float Vector3::dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    bool Vector3::operator == (const Vector3 & other) const noexcept
    {
        return x == other.x && y == other.y && z == other.z;
    }

    // Angle between vectors
    float Vector3::angle(const Vector3& v)
    {

        float theta;

        Vector3 u = v;
        Vector3 m = *this;

        theta = dot(u) / (m.magnitude() * u.magnitude());

        theta = RadToDegrees(acos(theta));

        return theta;

    }

    // cross product
    Vector3 Vector3::cross(const Vector3& v) const
    {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    void Vector3::operator %=(const Vector3& v)
    {
        *this = cross(v);
    }

    Vector3 Vector3::operator %(const Vector3& v) const
    {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    // conjugate
    void Vector3::conjugate()
    {
        x = -1 * x;
        y = -1 * y;
        z = -1 * z;
    }

    // normalize
    void Vector3::normalize()
    {
        float mag = std::sqrt(x * x + y * y + z * z);

        if (mag > 0.0f) 
        {
            float oneOverMag = 1.0f / mag;

            x = x * oneOverMag;
            y = y * oneOverMag;
            z = z * oneOverMag;

        }
    }

    // magnitude
    float Vector3::magnitude()
    {
        float magnitude = std::sqrt(x * x + y * y + z * z);

        return magnitude;

    }

    float Vector3::magnitudeSquare()
    {
        float magnitude = x * x + y * y + z * z;

        return magnitude;
    }

    // clear
    void Vector3::zero()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    void Vector3::absolute()
    {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);
    }

    // show
    void Vector3::show()
    {
        std::printf("vec3(%.6f, %.6f, %.6f)\n", x, y, z);
    }

    void Vector3::show(char coordinate)
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
        else {
            std::printf("Out of vector scope\n");
        }
    }

    void Vector3::negate()
    {
        x = -1 * x;
        y = -1 * y;
        z = -1 * z;
    }

    // rotate Vector
    Vector3 Vector3::rotateVectorAboutAngleAndAxis(float uAngle, Vector3& uAxis)
    {
        Quaternion p(0, (*this));
        uAxis.normalize();
        Quaternion q(uAngle, uAxis);

        q.convertToUnitNormQuaternion();

        Quaternion qInverse = q.inverse();
        Quaternion rotatedVector = q * p * qInverse;

        return rotatedVector.v;
    }

} /* namespace Math */

} /* namespace Engine */
