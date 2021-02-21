#pragma once

#include "Camera.h"

namespace Apex {

	class Perspective : public Camera
	{
		float m_Fov, m_AspectRatio, m_Near, m_Far;
	public:
		explicit Perspective(float fov, float aspectRatio, float near, float far);
		~Perspective();

		virtual Mat4 CreateCamera() override;
	};

}