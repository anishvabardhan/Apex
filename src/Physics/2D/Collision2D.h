#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"

namespace Apex {

	class Collision2D
	{
		float increamentX = 2.0f, increamentY = 2.0f;
	public:
		void CollisionWorld(const Renderable2D& GameObj, const Window& window);

		inline float GetX() const { return increamentX; }
		inline float GetY() const { return increamentY; }
	};

}