#pragma once

//#include "Graphics/Windows.h"
//#include "../Graphics/Renderable2D.h"
#include "../../tests/Astroids/Code/Ship.h"
#include "../../tests/Astroids/Code/Astroid.h"

namespace Apex {

	class Collision2D
	{
		float increamentX = 0.035f, increamentY = 0.035f;
		bool CollisionX, CollisionY;
	public:

		//bool CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2);
		bool CollisionObjects(const Ship& GameObj1, const Astroid& GameObj2);
	    void CollisionWorld(const Astroid& GameObj);

		inline float GetX() const { return increamentX; }
		inline float GetY() const { return increamentY; }

		inline void SetX(float x) { increamentX = x; }
		inline void SetY(float y) { increamentY = y; }
	};

}