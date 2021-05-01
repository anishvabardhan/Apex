#pragma once

#include "Maths/Vec2.h"

namespace Apex {

	class Astroid
	{
		Vec2 m_Position;
		Vec2 m_Translate;

		float m_Velocity, m_Accelaration;
		float m_Angle;
	public:
		explicit Astroid(Vec2 position, int i);
		~Astroid();

		void OnUpdate(float dt);
		void Render();

		void Translation();
		void Rotation();

		inline Vec2 GetPostion() const { return m_Position; }
		inline Vec2 GetTranslate() const { return m_Translate; }
	};

}