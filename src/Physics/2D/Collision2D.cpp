#include "Collision2D.h"

namespace Apex {

	bool Collision2D::CollisionObjects(const Renderable2D& GameObj1, const Renderable2D& GameObj2)
	{
		// collision x-axis?
		bool collisionX = GameObj1.GetPosition().m_X + GameObj1.GetSize().m_X >= GameObj2.GetPosition().m_X &&
			GameObj2.GetPosition().m_X + GameObj2.GetSize().m_X >= GameObj1.GetPosition().m_X;
		// collision y-axis?
		bool collisionY = GameObj1.GetPosition().m_Y + GameObj1.GetSize().m_Y >= GameObj2.GetPosition().m_Y &&
			GameObj2.GetPosition().m_Y + GameObj2.GetSize().m_Y >= GameObj1.GetPosition().m_Y;
		// collision only if on both axes
		return collisionX && collisionY;
	}

	bool Collision2D::CollisionWorld(const Renderable2D& GameObj, const Window& window)
	{
		if (GameObj.GetPosition().m_X + GameObj.GetSize().m_X >= window.GetWidth() || GameObj.GetPosition().m_X <= 0)
		{
			increamentX = -increamentX;
			return true;
		}

		if (GameObj.GetPosition().m_Y + GameObj.GetSize().m_Y >= window.GetHeight() || GameObj.GetPosition().m_Y <= 0)
		{
			increamentY = -increamentY;
			return true;
		}

		return false;
	}

}