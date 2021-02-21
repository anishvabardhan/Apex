#include "OrthoGraphic.h"

namespace Apex {

	OrthoGraphic::OrthoGraphic(float left, float right, float bottom, float top, float near, float far)
		: m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top), m_Near(near), m_Far(far)
	{
	}

	OrthoGraphic::~OrthoGraphic()
	{
	}

	Mat4 OrthoGraphic::CreateCamera()
	{
		return Mat4::orthographic(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far);
	}

}