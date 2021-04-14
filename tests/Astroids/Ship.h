#pragma once

#include "Maths/Vec2.h";

namespace Apex {

	class Ship
	{
		Vec2 m_Position;
	public:
		explicit Ship(Vec2 position);
		~Ship();

		void Render();

		void Translation(float x = 0, float y = 0);
		void Rotation(float angle);

		inline Vec2 GetPosition() const { return m_Position; }
		static inline Vec2 GetNosePosition() { return Vec2(0.0f, 15.0f); }

		inline void SetPosition(Vec2 position) { m_Position = position; }
	};

}