#pragma once

#include "Maths/Mat4.h"

namespace Apex {

	class OrthoGraphic
	{
		Mat4 m_Proj;
	public:
		OrthoGraphic(float left, float right, float bottom, float top);

		const Mat4& GetProjMatrix() const { return m_Proj; }
	};

}