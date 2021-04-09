#include "Ship.h"

#include <GL/glew.h>

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
		glTranslatef(m_Position.m_X, m_Position.m_Y, 0.0f);

		glBegin(GL_LINE_STRIP);
		glColor3f(   0.5f,   0.5f, 0.5f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glEnd();
	}

}