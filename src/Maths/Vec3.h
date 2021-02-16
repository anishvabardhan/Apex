#pragma once
#include <iostream>

namespace Apex {

	class Vec3
	{
	public:
		float m_X;
		float m_Y;
		float m_Z;
	public:
		Vec3();
		Vec3(float x, float y, float z);

		Vec3& Add(const Vec3& other);
		Vec3& Subtract( const Vec3& other);
		Vec3& Multiply(const Vec3& other);
		Vec3& Divide(const Vec3& other);

		friend Vec3& operator+(Vec3 one, const Vec3& other);
		friend Vec3& operator-(Vec3 one, const Vec3& other);
		friend Vec3& operator*(Vec3 one, const Vec3& other);
		friend Vec3& operator/(Vec3 one, const Vec3& other);

		Vec3 operator+=(const Vec3& other);
		Vec3 operator-=(const Vec3& other);
		Vec3 operator*=(const Vec3& other);
		Vec3 operator/=(const Vec3& other);

		bool operator==(const Vec3& other);
		bool operator!=(const Vec3& other);

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
		inline float GetZ() const { return m_Z; }

		friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	};

}