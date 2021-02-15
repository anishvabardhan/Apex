#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"

namespace Apex {

	class Collision2D
	{
		float increamentX = 0.5f, increamentY = 0.5f;
	public:
		void CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2);
		void CollisionWorld(const Renderable2D& GameObj, const Window& window);

		inline float GetX() const { return increamentX; }
		inline float GetY() const { return increamentY; }
	};

}