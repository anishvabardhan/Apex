#include "Vec3.h"

namespace Apex {

	Vec3::Vec3()
		: m_X(0), m_Y(0)
	{
	}

	Vec3::Vec3(float x, float y, float z)
		: m_X(x), m_Y(y), m_Z(z)
	{
	}

	Vec3& Vec3::Add(const Vec3& other)
	{
		m_X += other.m_X;
		m_Y += other.m_Y;
		m_Z += other.m_Z;
		return *this;
	}

	Vec3& Vec3::Subtract(const Vec3& other)
	{
		m_X -= other.m_X;
		m_Y -= other.m_Y;
		m_Z -= other.m_Z;
		return *this;
	}

	Vec3& Vec3::Multiply(const Vec3& other)
	{
		m_X *= other.m_X;
		m_Y *= other.m_Y;
		m_Z *= other.m_Z;
		return *this;
	}

	Vec3& Vec3::Divide(const Vec3& other)
	{
		m_X /= other.m_X;
		m_Y /= other.m_Y;
		m_Z /= other.m_Z;
		return *this;
	}

	Vec3 Vec3::operator+=(const Vec3& other)
	{
		return Add(other);
	}

	Vec3 Vec3::operator-=(const Vec3& other)
	{
		return Subtract(other);
	}

	Vec3 Vec3::operator*=(const Vec3& other)
	{
		return Multiply(other);
	}

	Vec3 Vec3::operator/=(const Vec3& other)
	{
		return Divide(other);
	}

	bool Vec3::operator==(const Vec3& other)
	{
		return this->GetX() == other.GetX() && this->GetY() == other.GetY() && this->GetZ() == other.GetZ();
	}

	bool Vec3::operator!=(const Vec3& other)
	{
		return !(*this == other);
	}

	Vec3& operator+(Vec3 one, const Vec3& other)
	{
		return one.Add(other);
	}

	Vec3& operator-(Vec3 one, const Vec3& other)
	{
		return one.Subtract(other);
	}

	Vec3& operator*(Vec3 one, const Vec3& other)
	{
		return one.Multiply(other);
	}

	Vec3& operator/(Vec3 one, const Vec3& other)
	{
		return one.Divide(other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
	{
		// TODO: insert return statement here
		stream << "(" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ")";
		return stream;
	}

}