#include "Collision2D.h"

namespace Apex {

	void Collision2D::CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2)
	{
		if (GameObj1.GetPosition().x + GameObj1.GetSize().x >= GameObj2.GetPosition().x - GameObj2.GetSize().x || GameObj1.GetPosition().x - GameObj1.GetSize().x <= GameObj2.GetPosition().x + GameObj2.GetSize().x)
			increamentX = -increamentX;
	}

	void Collision2D::CollisionWorld(const Renderable2D& GameObj, const Window& window)
	{
		if (GameObj.GetPosition().x + GameObj.GetSize().x >= window.GetWidth() || GameObj.GetPosition().x <= 0)
			increamentX = -increamentX;

		if (GameObj.GetPosition().y + GameObj.GetSize().y >= window.GetHeight() || GameObj.GetPosition().y <= 0)
			increamentY = -increamentY;
	}

}