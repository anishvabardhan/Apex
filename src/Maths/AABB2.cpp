#include "AABB2.h"

#include "Maths_Func.h"

namespace Apex {

	AABB2::AABB2()
	{
	}

	AABB2::AABB2(float minX, float minY, float maxX, float maxY)
	{
		m_Mins = Vec2(minX, minY);
		m_Maxs = Vec2(maxX, maxY);
	}
	
	AABB2::AABB2(const Vec2& mins, const Vec2& maxs)
	{
		this->m_Mins = mins;
		this->m_Maxs = maxs;
	}
	
	AABB2::AABB2(const Vec2& center, float radiusX, float radiusY)
	{
		m_Maxs.m_X = center.m_X + radiusX;
		m_Maxs.m_Y = center.m_Y + radiusY;

		m_Mins.m_X = center.m_X - radiusX;
		m_Mins.m_Y = center.m_Y - radiusY;
	}
	
	AABB2::AABB2(const AABB2& copy)
	{
		m_Mins = copy.m_Mins;
		m_Maxs = copy.m_Maxs;
	}
	
	AABB2::~AABB2()
	{
	}
	
	void AABB2::StretchToIncludePoint(float x, float y)
	{
		if (IsPointInside(Vec2(x, y)))
			return;

		StretchToIncludePoint(Vec2(x, y));
	}
	
	void AABB2::StretchToIncludePoint(const Vec2& point)
	{
		if (IsPointInside(Vec2(point.m_X, point.m_Y)))
			return;

		if (point.m_X < m_Mins.m_X)
		{
			m_Mins.m_X = point.m_X;

			if (point.m_Y < m_Mins.m_Y)
				m_Mins.m_Y = point.m_Y;
			if (point.m_Y > m_Maxs.m_Y)
				m_Maxs.m_Y = point.m_Y;
		}
		if (point.m_X > m_Mins.m_X && point.m_X < m_Maxs.m_X)
		{
			if (point.m_Y < m_Mins.m_Y)
				m_Mins.m_Y = point.m_Y;
			if (point.m_Y > m_Maxs.m_Y)
				m_Maxs.m_Y = point.m_Y;
		}

		if (point.m_X > m_Maxs.m_X)
		{
			m_Maxs.m_X = point.m_X;
			if (point.m_Y < m_Mins.m_Y)
				m_Mins.m_Y = point.m_Y;
			if (point.m_Y > m_Maxs.m_Y)
				m_Maxs.m_Y = point.m_Y;
		}
	}
	
	void AABB2::AddPaddingToSides(float xPaddingRadius, float yPaddingRadius)
	{
		m_Mins -= Vec2(xPaddingRadius, yPaddingRadius);
		m_Maxs += Vec2(xPaddingRadius, yPaddingRadius);
	}
	
	void AABB2::Translate(const Vec2& translation)
	{
		m_Mins += translation;
		m_Maxs += translation;
	}
	
	void AABB2::Translate(float translationX, float translationY)
	{
		m_Mins += Vec2(translationX, translationY);
		m_Maxs += Vec2(translationX, translationY);
	}
	
	bool AABB2::IsPointInside(float x, float y) const
	{
		if ((x >= m_Mins.m_X && x <= m_Maxs.m_X) && (y >= m_Mins.m_Y && y <= m_Maxs.m_Y))
		{
			return true;
		}
		else
			return false;
	}
	
	bool AABB2::IsPointInside(const Vec2& point) const
	{
		return IsPointInside(point.m_X, point.m_Y);
	}
	
	Vec2 AABB2::GetDimensions() const
	{
		float width = m_Maxs.m_X - m_Mins.m_X;
		float height = m_Maxs.m_Y - m_Mins.m_Y;

		return Vec2(width, height);
	}
	
	Vec2 AABB2::GetCenter() const
	{
		float x = (m_Mins.m_X + m_Maxs.m_X) * 0.5f;
		float y = (m_Mins.m_Y + m_Maxs.m_Y) * 0.5f;

		return Vec2(x, y);
	}
	
	void AABB2::operator+=(const Vec2& translation)
	{
		Translate(translation);
	}
	
	void AABB2::operator-=(const Vec2& antiTranslation)
	{
		Translate(antiTranslation * -1.f);
	}
	
	AABB2 AABB2::operator+(const Vec2& translation)
	{
		AABB2 temp;

		temp.m_Mins = m_Mins + translation;
		temp.m_Maxs = m_Maxs + translation;

		return temp;
	}
	
	AABB2 AABB2::operator-(const Vec2& antiTranslation)
	{
		AABB2 temp;

		temp.m_Mins = m_Mins - antiTranslation;
		temp.m_Maxs = m_Maxs - antiTranslation;
		
		return temp;
	}

}