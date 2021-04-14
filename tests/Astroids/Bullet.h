#pragma once

#include "Maths/Vec2.h"

namespace Apex {

	class Bullet
	{
		Vec2 m_Position;
	public:
		explicit Bullet(Vec2 position);
		~Bullet();

		void Render();

		void PivotAxis(float x, float y);

		void Translation(float x, float y);
		void Rotation(float angle);
	};

}