#pragma once

#include "Camera.h"

namespace Apex {

	class OrthoGraphic : public Camera
	{
		float m_Left ,m_Right, m_Bottom, m_Top, m_Near, m_Far;
	public:
		explicit OrthoGraphic(float left, float right, float bottom, float top, float near, float far);
		~OrthoGraphic();

		virtual Mat4 CreateCamera() override;
	};

}