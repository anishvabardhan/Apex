#pragma once

namespace Apex {

	class Random
	{
	public:
		float min, max;

		Random() { min = max = 0.0f; }
		explicit Random(float minInclusive, float maxInclusive);
		explicit Random(float rangeMinMax);

		float GetRandomInRange();
		
		static int GetRandomIntLessThan(int maxNotInclusive);
		static float GetRandomFloatInRange(float minInclusive, float maxInclusive);

		float Interpolate(float start, float end, float fractionTowardEnd);
	public:
		const Random Interpolate(const Random& start, const Random& end, float fractionTowardEnd);
	};

}