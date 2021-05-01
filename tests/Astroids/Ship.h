#pragma once

#include "../src/Maths/Vec2.h"

namespace Apex {

	class Ship
	{
		Vec2 m_Position;
		Vec2 m_Translate;

		float m_Velocity, m_Accelaration;

		float m_Angle;
	public:
		explicit Ship(Vec2 position);
		~Ship();

		void OnUpdate(float dt);
		void Render();

		void Translation();
		void Rotation();

		inline Vec2 GetPosition() const { return m_Position; }
		static inline Vec2 GetNosePosition() { return Vec2(0.0f, 15.0f); }

		inline Vec2 GetTranslate() const { return m_Translate; }
		inline void SetTranslate(Vec2 vector) { m_Translate = vector; }

		inline void SetPosition(Vec2 position) { m_Position = position; }
	};

}