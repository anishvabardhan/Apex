#pragma once

#include "../src/Maths/Vec2.h"
#include "../src/Physics/2D/Disc2D.h"
#include "Entity.h"

namespace Apex {

	class Astroid : public Entity
	{
		Vec2 m_Position;
		Vec2 m_Translate;

		float m_Velocity[2], m_Accelaration[2];
		float m_Angle;
	public:
		explicit Astroid(Vec2 position, int i);
		~Astroid();

		void OnUpdate(float dt) override;
		void Render() override;

		void Translation();
		void Rotation();

		inline Vec2 GetPostion() const { return m_Position; }
		inline Vec2 GetTranslate() const { return m_Translate; }
	};

}