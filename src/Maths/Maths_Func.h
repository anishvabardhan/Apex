#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace Apex {

	inline float toRadians(float degrees)
	{
		float temp = M_PI / 180.0f;
		return degrees * temp;
	}

}