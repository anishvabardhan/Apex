#pragma once

#include "../src/Maths/Vec2.h"

namespace Apex {

	class Bullet
	{
		Vec2 m_Position;
		Vec2 m_Translate;
		Vec2 m_Velocity;
		Vec2 m_Accelaration;

		float m_Angle;
	public:
		explicit Bullet(Vec2 position);
		~Bullet();

		void Render(float dt);
	};

}