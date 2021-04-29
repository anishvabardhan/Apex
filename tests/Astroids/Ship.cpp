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
		glColor3f(1.0f, 0.8f, 0.0f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
	}

	void Ship::Translation(float x, float y)
	{
		glLoadIdentity();

		if ((m_Position.m_X + x > 20.0f && m_Position.m_X + x < 984.0f) && (m_Position.m_Y + y > 20.0f && m_Position.m_Y + y < 698.0f))
		{
			glTranslatef(m_Position.m_X + x, m_Position.m_Y + y, 0.0f);
		}

		if(m_Position.m_X + x < 20.0f)
		{
			glTranslatef(20.0f, m_Position.m_Y + y, 0.0f);
		}
		
		if (m_Position.m_Y + y < 20.0f)
		{
			glTranslatef(m_Position.m_X + x, 20.0f, 0.0f);
		}
		
		if (m_Position.m_X + x > 984.0f)
		{
			glTranslatef(984.0f, m_Position.m_Y + y, 0.0f);
		}
		
		if (m_Position.m_Y + y > 698.0f)
		{
			glTranslatef(m_Position.m_X + x, 698.0f, 0.0f);
		}
	}

	void Ship::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}