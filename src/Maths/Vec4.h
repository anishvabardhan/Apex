#pragma once
#include <iostream>

namespace Apex {

	class Vec4
	{
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;
	public:
		Vec4();
		Vec4(float x, float y, float z, float w);
		~Vec4();

		Vec4& Add(const Vec4& other);
		Vec4& Subtract( const Vec4& other);
		Vec4& Multiply(const Vec4& other);
		Vec4& Divide(const Vec4& other);

		friend Vec4& operator+(Vec4 one, const Vec4& other);
		friend Vec4& operator-(Vec4 one, const Vec4& other);
		friend Vec4& operator*(Vec4 one, const Vec4& other);
		friend Vec4& operator/(Vec4 one, const Vec4& other);

		Vec4 operator+=(const Vec4& other);
		Vec4 operator-=(const Vec4& other);
		Vec4 operator*=(const Vec4& other);
		Vec4 operator/=(const Vec4& other);

		bool operator==(const Vec4& other);
		bool operator!=(const Vec4& other);

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
		inline float GetZ() const { return m_Z; }
		inline float GetW() const { return m_W; }

		friend std::ostream& operator<<(std::ostream& stream, const Vec4& vector);
	};

}