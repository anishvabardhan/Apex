#include "OrthoGraphic.h"

namespace Apex {

	OrthoGraphic::OrthoGraphic(float left, float right, float bottom, float top)
		: m_Proj(Mat4::orthographic(left, right, bottom, top, -100.0f, 100.0f)), m_View(Mat4::identity())
	{
		m_ViewProj = m_Proj * m_View;
	}

}