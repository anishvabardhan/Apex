#pragma once

#include "Maths/Vec2.h";

namespace Apex {

	class Ship
	{
		Vec2 m_Position;
	public:
		Ship(Vec2 position);
		~Ship();

		void Render();

		inline Vec2 GetPosition() const { return m_Position; }
	};

}