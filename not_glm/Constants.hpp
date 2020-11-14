#pragma once

#include "math.h"

#ifndef Constants_hpp
#define Constants_hpp

namespace NotGLM {
	#define M_PI (3.14159265358979323846)
	
	
	#define M_PIl (3.14159265358979323846264338327950288)
	
	#define DegreesToRad(angle) angle*M_PI/180
	#define RadToDegrees(angle) angle*180/M_PI
	
	class BasicMath
	{
		public:
			static float radian(float a) { return a * M_PI / 180.f; };
			static float degrees(float radians) { return radians * 180.f / M_PI; }

			static bool approxEqual(float A, float B);

			static float clamp(const float val, const float min, const float max);

			static float randBetween(const float min, const float max);

		private:
			static const int MAX_NUM_DIGITS_DIFFERENCE = 1;
	};
}

#endif /* Constants_hpp */