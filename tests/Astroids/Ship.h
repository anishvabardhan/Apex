#pragma once

#include "../src/Maths/Vec2.h"
#include "../src/Maths/Vec3.h"
#include "../src/Physics/2D/Disc2D.h"
#include "Entity.h"

namespace Apex {

	class Ship : public Entity
	{
		Vec2 m_Position;
		Vec2 m_Translate;
		Vec2 m_Velocity;
		Vec2 m_Accelaration;

		Vec3 m_BodyVertices[4];
		Vec3 m_ThrusterVertices[6];

		bool m_IsAccelarating;

		float m_Angle;
	public:
		explicit Ship(Vec2 position);
		~Ship();

		void OnUpdate(float dt) override;
		void Render() override;

		void Translation();
		void Rotation();

		inline Vec2 GetPosition() const { return m_Position; }
		inline Vec2 GetTranslate() const { return m_Translate; }

		Vec2 GetNosePosition();
	};

}