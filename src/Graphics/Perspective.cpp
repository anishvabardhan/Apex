#include "Perspective.h"

namespace Apex {

	Perspective::Perspective(float fov, float aspectRatio, float near, float far)
		: m_Fov(fov), m_AspectRatio(aspectRatio), m_Near(near), m_Far(far)
	{
	}

	Perspective::~Perspective()
	{
	}

	Mat4 Perspective::CreateCamera()
	{
		return Mat4::perspective(m_Fov, m_AspectRatio, m_Near, m_Far);
	}

}