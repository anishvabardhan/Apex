#include "Vec2.h"

namespace Apex {

	Vec2::Vec2()
		: m_X(0), m_Y(0)
	{
	}

	Vec2::Vec2(float x, float y)
		: m_X(x), m_Y(y)
	{
	}

	Vec2& Vec2::Add(const Vec2& other)
	{
		m_X += other.m_X;
		m_Y += other.m_Y;

		return *this;
	}

	Vec2& Vec2::Subtract(const Vec2& other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;

		return *this;
	}

	Vec2& Vec2::Multiply(const Vec2& other)
	{
		m_X *= other.m_X;
		m_Y *= other.m_Y;

		return *this;
	}

	Vec2& Vec2::Divide(const Vec2& other)
	{
		m_X /= other.m_X;
		m_Y /= other.m_Y;

		return *this;
	}

	Vec2 Vec2::operator+=(const Vec2& other)
	{
		return Add(other);
	}

	Vec2 Vec2::operator-=(const Vec2& other)
	{
		return Subtract(other);
	}

	Vec2 Vec2::operator*=(const Vec2& other)
	{
		return Multiply(other);
	}

	Vec2 Vec2::operator/=(const Vec2& other)
	{
		return Divide(other);
	}

	bool Vec2::operator==(const Vec2& other)
	{
		return this->GetX() == other.GetX() && this->GetY() == other.GetY();
	}

	bool Vec2::operator!=(const Vec2& other)
	{
		return !(*this == other);
	}

	Vec2& operator+(Vec2 one, const Vec2& other)
	{
		return one.Add(other);
	}

	Vec2& operator-(Vec2 one, const Vec2& other)
	{
		return one.Subtract(other);
	}

	Vec2& operator*(Vec2 one, const Vec2& other)
	{
		return one.Multiply(other);
	}

	Vec2& operator/(Vec2 one, const Vec2& other)
	{
		return one.Divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
	{
		stream << "(" << vector.GetX() << ", " << vector.GetY() << ")";

		return stream;
	}

}