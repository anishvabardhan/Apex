#pragma once

#include "../src/Maths/Vec2.h"

namespace Apex {

	class Bullet
	{
		float m_Velocity, m_Accelaration;
	public:
		Bullet();
		~Bullet();

		static void Render();
	};

}