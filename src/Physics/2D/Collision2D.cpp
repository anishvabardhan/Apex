#include "Collision2D.h"

namespace Apex {

	void Collision2D::CollisionWorld(const Renderable2D& GameObj, const Window& window)
	{
		if (GameObj.GetPosition().x + GameObj.GetSize().x >= 640.0f || GameObj.GetPosition().x <= 0)
			increamentX = -increamentX;

		if (GameObj.GetPosition().y + GameObj.GetSize().y >= 480.0f || GameObj.GetPosition().y <= 0)
			increamentY = -increamentY;
	}

}