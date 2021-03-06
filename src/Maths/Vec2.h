#pragma once
#include <iostream>

namespace Apex {

	class Vec2
	{
	public:
		float m_X;
		float m_Y;
	public:
		Vec2();
		explicit Vec2(float x, float y);

		Vec2& Add(const Vec2& other);
		Vec2& Subtract( const Vec2& other);
		Vec2& Multiply(const Vec2& other);
		Vec2& Divide(const Vec2& other);

		Vec2& operator+(const Vec2& other);
		Vec2& operator-(const Vec2& other);
		Vec2& operator*(const Vec2& other);
		Vec2& operator/(const Vec2& other);

		Vec2 operator+=(const Vec2& other);
		Vec2 operator-=(const Vec2& other);
		Vec2 operator*=(const Vec2& other);
		Vec2 operator/=(const Vec2& other);

		bool operator==(const Vec2& other);
		bool operator!=(const Vec2& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
	};

}