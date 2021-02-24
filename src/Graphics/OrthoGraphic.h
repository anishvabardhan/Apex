#pragma once

#include "Maths/Maths.h"

namespace Apex {

	class OrthoGraphic
	{

	// Member Variables-------------------------------------------------------------------------------------

		Mat4 m_Proj;
		Mat4 m_View;
		Mat4 m_ViewProj;
	public:

// Constructors---------------------------------------------------------------------------------------------

		explicit OrthoGraphic(float left, float right, float bottom, float top);

// Methods--------------------------------------------------------------------------------------------------

		const Mat4& GetProjMatrix() const { return m_Proj; }
		const Mat4& GetViewMatrix() const { return m_View; }
		const Mat4& GetViewProjMatrix() const { return m_ViewProj; }
	};

}