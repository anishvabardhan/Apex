#pragma once

#include "Vec2.h"

namespace Apex {

	class AABB2
	{
	public:
		static const AABB2 ZERO;
		static const AABB2 ZERO_TO_ONE;

		Vec2 m_Mins;
		Vec2 m_Maxs;
	public:
		AABB2();
		explicit AABB2(float minX, float minY, float maxX, float maxY);
		explicit AABB2(const Vec2& mins, const Vec2& maxs);
		explicit AABB2(const Vec2& center, float radiusX, float radiusY);
		AABB2(const AABB2& copy);
		~AABB2();

		void StretchToIncludePoint(float x, float y);
		void StretchToIncludePoint(const Vec2& point);
		void AddPaddingToSides(float xPaddingRadius, float yPaddingRadius);
		void Translate(const Vec2& translation);
		void Translate(float translationX, float translationY);

		bool IsPointInside(float x, float y) const;
		bool IsPointInside(const Vec2& point) const;
		
		Vec2 GetDimensions() const;
		Vec2 GetCenter() const;

		void operator +=(const Vec2& translation);
		void operator -=(const Vec2& antiTranslation);
		AABB2 operator +(const Vec2& translation);
		AABB2 operator -(const Vec2& antiTranslation);
	};

}