#pragma once

#ifndef ENGINE_MATHS_CONSTANTS_HPP_
#define ENGINE_MATHS_CONSTANTS_HPP_

#include <cmath>

namespace Engine {

namespace Math {

#define M_PI (3.14159265358979323846)


#define M_PIl (3.14159265358979323846264338327950288)

#define DegreesToRad(angle) angle*M_PI/180
#define RadToDegrees(angle) angle*180/M_PI

class BasicMath
{
	public:
		static float radian(float a) { return a * static_cast<float>(M_PI) / 180.f; };
		static float degrees(float radians) { return radians * 180.f / static_cast<float>(M_PI); }

		static bool approxEqual(float A, float B);

		static float clamp(const float val, const float min, const float max);

		static float randBetween(const float min, const float max);

	private:
		static const int MAX_NUM_DIGITS_DIFFERENCE = 1;
}; /* class BasicMath */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_CONSTANTS_HPP_ */
