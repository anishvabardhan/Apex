#pragma once

#include "../src/Maths/Vec2.h"

namespace Apex {

	class Bullet
	{
		Vec2 m_Position, m_Translate;

		float m_Velocity, m_Accelaration, m_Angle;
	public:
		explicit Bullet(Vec2 position);
		~Bullet();

		void OnUpdate(float dt);
		void Render();
	};

}