#include "Ship.h"

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Ship::Ship(Vec2 position)
		:m_Position(position)
	{
	}

	Ship::~Ship()
	{
	}

	void Ship::Render()
	{
		glColor3f(   0.2f,   0.3f, 0.8f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
	}

	void Ship::Translation(float x, float y)
	{
		glTranslatef(m_Position.m_X + x, m_Position.m_Y + y, 0.0f);
	}

	void Ship::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}