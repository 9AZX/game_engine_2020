#include "Engine/Maths/Constants.hpp"

#include <cassert>
#include <cstdlib>

namespace Engine {

namespace Math {

	bool BasicMath::approxEqual(float A, float B) {
		return fabs(A - B) < .001;
	}

	float BasicMath::clamp(const float val, const float min, const float max) {
		if (val < min) {
			return min;
		}
		else if (val > max) {
			return max;
		}
		else {
			return val;
		}
	}

	float BasicMath::randBetween(const float min, const float max) {
		return ((max - min) * ((float)rand() / RAND_MAX)) + min;
	}

} /* namespace Math */

} /* namespace Engine */