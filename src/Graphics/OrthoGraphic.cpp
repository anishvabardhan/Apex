#include "OrthoGraphic.h"

namespace Apex {

	OrthoGraphic::OrthoGraphic(float left, float right, float bottom, float top)
		: m_Proj(Mat4::orthographic(left, right, bottom, top, -1.0f, 1.0f))
	{
	}

}