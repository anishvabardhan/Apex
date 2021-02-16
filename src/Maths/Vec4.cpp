#include "Vec4.h"

namespace Apex {

	Vec4::Vec4(float x, float y, float z, float w)
		: m_X(x), m_Y(y), m_Z(z), m_W(w)
	{
	}

	Vec4& Vec4::Add(const Vec4& other)
	{
		m_X += other.m_X;
		m_Y += other.m_Y;
		m_Z += other.m_Z;
		m_W += other.m_W;
		return *this;
	}

	Vec4& Vec4::Subtract(const Vec4& other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
		m_W -= other.m_W;
		return *this;
	}

	Vec4& Vec4::Multiply(const Vec4& other)
	{
		m_X *= other.m_X;
		m_Y *= other.m_Y;
		m_Z *= other.m_Z;
		m_W *= other.m_W;
		return *this;
	}

	Vec4& Vec4::Divide(const Vec4& other)
	{
		m_X /= other.m_X;
		m_Y /= other.m_Y;
		m_Z /= other.m_Z;
		m_W /= other.m_W;
		return *this;
	}

	Vec4 Vec4::operator+=(const Vec4& other)
	{
		return Add(other);
	}

	Vec4 Vec4::operator-=(const Vec4& other)
	{
		return Subtract(other);
	}

	Vec4 Vec4::operator*=(const Vec4& other)
	{
		return Multiply(other);
	}

	Vec4 Vec4::operator/=(const Vec4& other)
	{
		return Divide(other);
	}

	bool Vec4::operator==(const Vec4& other)
	{
		return this->GetX() == other.GetX() && this->GetY() == other.GetY() && this->GetZ() == other.GetZ() && this->GetW() == other.GetW();
	}

	bool Vec4::operator!=(const Vec4& other)
	{
		return !(*this == other);
	}

	Vec4& operator+(Vec4 one, const Vec4& other)
	{
		return one.Add(other);
	}

	Vec4& operator-(Vec4 one, const Vec4& other)
	{
		return one.Subtract(other);
	}

	Vec4& operator*(Vec4 one, const Vec4& other)
	{
		return one.Multiply(other);
	}

	Vec4& operator/(Vec4 one, const Vec4& other)
	{
		return one.Divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec4& vector)
	{
		stream << "(" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ", " << vector.GetW() << ")";
		return stream;
	}

}