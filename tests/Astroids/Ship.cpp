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
		glColor3f(   1.0f,   0.8f, 0.0f);

		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
	}

	void Ship::Translation(float x, float y)
	{
		if (m_Position.m_X + x > 0 && m_Position.m_Y + y > 0)
		{
			glTranslatef((GLfloat)((int)(m_Position.m_X + x) % 1024), (GLfloat)((int)(m_Position.m_Y + y) % 768), 0.0f);
		}

		if(m_Position.m_X + x <= 0)
		{
			glTranslatef((GLfloat)(1024 + ((int)(m_Position.m_X + x) % 1024)), (GLfloat)((int)(m_Position.m_Y + y) % 768), 0.0f);
		}

		if(m_Position.m_Y + y <= 0)
		{
			glTranslatef((GLfloat)((int)(m_Position.m_X + x) % 1024), (GLfloat)(768 + ((int)(m_Position.m_Y + y) % 768)), 0.0f);
		}
	}

	void Ship::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}