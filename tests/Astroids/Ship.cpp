#include "Ship.h"

#include <gl/glew.h>

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
		glPushMatrix();
		glColor3f(   0.2f,   0.3f, 0.8f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
		glPopMatrix();
	}

	void Ship::Translation()
	{
		glTranslatef(m_Position.m_X, m_Position.m_Y, 0.0f);
	}

}