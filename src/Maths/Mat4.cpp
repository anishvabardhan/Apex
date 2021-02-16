#include "Mat4.h"

namespace Apex {

	Mat4::Mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
		{
			elements[i] = 0.0f;
		}
	}

	Mat4::Mat4(float d)
	{
		for (int i = 0; i < 4 * 4; i++)
		{
			elements[i] = 0.0f;
		}

		elements[0 + 0 * 4] = d;
		elements[1 + 1 * 4] = d;
		elements[2 + 2 * 4] = d;
		elements[3 + 3 * 4] = d;
	}

	Mat4 Mat4::identity()
	{
		return Mat4(1.0f);
	}

	Mat4& Mat4::Multiply(const Mat4& other)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				elements[x + y * 4] = sum;
			}
		}

		return *this;
	}

	Mat4& Mat4::operator*(const Mat4& other)
	{
		return Multiply(other);
	}

	Mat4& Mat4::operator*=(const Mat4& other)
	{
		return Multiply(other);
	}

	bool Mat4::operator==(const Mat4& other)
	{
		int c = 0;
		for (int i = 0; i < 4 * 4; i++)
		{
			if (elements[i] == other.elements[i])
				c = 0;
			else
				c++;
		}

		if (!c)
			return true;
		return false;
	}

	bool Mat4::operator!=(const Mat4& other)
	{
		int c = 0;
		for (int i = 0; i < 4 * 4; i++)
		{
			if (elements[i] != other.elements[i])
				c = 0;
			else
				c++;
		}

		if (!c)
			return true;
		return false;
	}

	Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 result(1.0f);

		result.elements[0] = 2 / (right - left);
		result.elements[5] = 2 / (top - bottom);
		result.elements[10] = 2 / (near - far);
		result.elements[12] = (right + left) / (left - right);
		result.elements[13] = (top + bottom) / (bottom - top);
		result.elements[14] = (far + near) / (far - near);

		return result;
	}

	Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far)
	{
		Mat4 result(1.0f);

		result.elements[0] = 1 / (aspectRatio * tan(fov / 2));
		result.elements[5] = 1 / tan(toRadians(fov / 2));
		result.elements[10] = (near + far) / (near - far);
		result.elements[11] = -1;
		result.elements[14] = (2.0f * near * far) / (near - far);
		return result;
	}

	Mat4 Mat4::translation(const Vec3& translation)
	{
		Mat4 result(1.0f);

		result.elements[12] = translation.GetX();
		result.elements[13] = translation.GetY();
		result.elements[14] = translation.GetZ();

		return result;
	}

	Mat4 Mat4::rotation(float angle, const Vec3& axis)
	{
		Mat4 result(1.0f);

		result.elements[0] = axis.GetX() * (1.0f - cos(toRadians(angle))) + cos(toRadians(angle));
		result.elements[1] = axis.GetY() * axis.GetX() * (1.0f - cos(toRadians(angle))) + axis.GetZ() * sin(toRadians(angle));
		result.elements[2] = axis.GetX() * axis.GetZ() * (1.0f - cos(toRadians(angle))) - axis.GetY() * sin(toRadians(angle));

		result.elements[4] = axis.GetX() * axis.GetY() * (1.0f - cos(toRadians(angle))) - axis.GetZ() * sin(toRadians(angle));
		result.elements[5] = axis.GetY() * (1.0f - cos(toRadians(angle))) + cos(toRadians(angle));
		result.elements[6] = axis.GetY() * axis.GetZ() * (1.0f - cos(toRadians(angle))) + axis.GetX() * sin(toRadians(angle));

		result.elements[8] = axis.GetX() * axis.GetZ() * (1.0f - cos(toRadians(angle))) + axis.GetY() * sin(toRadians(angle));
		result.elements[9] = axis.GetY() * axis.GetZ() * (1.0f - cos(toRadians(angle))) - axis.GetX() * sin(toRadians(angle));
		result.elements[10] = axis.GetZ() * (1.0f - cos(toRadians(angle))) + cos(toRadians(angle));

		return result;
	}

	Mat4 Mat4::scale(const Vec3& scale)
	{
		Mat4 result(1.0f);

		result.elements[0] = scale.GetX();
		result.elements[5] = scale.GetY();
		result.elements[10] = scale.GetZ();

		return result;
	}

}