#pragma once

#include "Maths/Vec2.h"

namespace Apex {

	class Astroid
	{
		Vec2 m_Position;
	public:
		explicit Astroid(Vec2 position);
		~Astroid();

		void Render();

		void Translation(float x, float y);
		void Rotation(float angle);

		inline Vec2 GetPostion() const { return m_Position; }
	};

}