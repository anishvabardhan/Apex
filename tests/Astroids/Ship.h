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

		void Translation();

		inline Vec2 GetPosition() const { return m_Position; }
	};

}