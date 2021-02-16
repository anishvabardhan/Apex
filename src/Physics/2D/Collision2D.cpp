#include "Collision2D.h"

namespace Apex {

	bool Collision2D::CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2)
	{
		if ((GameObj1.GetPosition().x + GameObj1.GetSize().x) == (GameObj2.GetPosition().x - GameObj2.GetSize().x) || (GameObj1.GetPosition().x) == (GameObj2.GetPosition().x + GameObj2.GetSize().x))
		{
			increamentX = -increamentX;
			return true;
		}

		if ((GameObj1.GetPosition().y + GameObj1.GetSize().y) == (GameObj2.GetPosition().y - GameObj2.GetSize().y) || (GameObj1.GetPosition().y) == (GameObj2.GetPosition().y + GameObj2.GetSize().y))
		{
			increamentY = -increamentY;
			return true;
		}

		return false;
	}

	bool Collision2D::CollisionWorld(const Renderable2D& GameObj, const Window& window)
	{
		if (GameObj.GetPosition().x + GameObj.GetSize().x >= window.GetWidth() || GameObj.GetPosition().x <= 0)
		{
			increamentX = -increamentX;
			return true;
		}
		if (GameObj.GetPosition().y + GameObj.GetSize().y >= window.GetHeight() || GameObj.GetPosition().y <= 0)
		{
			increamentY = -increamentY;
			return true;
		}

		return false;
	}

}