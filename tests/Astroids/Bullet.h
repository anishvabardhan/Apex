#pragma once

#include "Maths/Vec3.h"

namespace Apex {

	class Bullet
	{
		Vec3 m_Position;
	public:
		explicit Bullet(Vec3 position);
		~Bullet();

		void Render();

		void Translation(float x, float y);
		void Rotation(float angle);
	};

}