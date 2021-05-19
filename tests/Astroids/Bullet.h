#pragma once

#include "../src/Maths/Vec2.h"
#include "../src/Maths/Vec3.h"

namespace Apex {

	class Bullet
	{
		Vec2 m_Position;
		Vec2 m_Translate;
		Vec2 m_Velocity;
		Vec2 m_Accelaration;

		Vec2 g_BulletVelocity, g_BulletAccelaration;

		Vec3 m_BodyVertices[10];

		int m_NumOfVertices;
		float m_Angle, m_Radius;
	public:
		explicit Bullet(Vec2 position);
		~Bullet();

		void OnUpdate(Vec2 position, Vec2 spawnPosition, float dt);
		void Render();

		void Rotation();
	};

}