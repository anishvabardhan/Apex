#pragma once

#include "Graphics/Window.h"
#include "Graphics/Renderable2D.h"
#include "Tests/Astroids/Astroid.h"

namespace Apex {

	class Collision2D
	{
		float increamentX = 2.0f, increamentY = 2.0f;
		bool CollisionX, CollisionY;
	public:

		bool CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2);
		bool CollisionWorld(Renderable2D& GameObj, const Window& window);
		bool CollisionWorld(Astroid& GameObj, const Window& window);

		inline float GetX() const { return increamentX; }
		inline float GetY() const { return increamentY; }

		inline void SetX(float x) { increamentX = x; }
		inline void SetY(float y) { increamentY = y; }
	};

}