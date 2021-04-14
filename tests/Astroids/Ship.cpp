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
		glPushMatrix();
		glColor3f(1.0f, 0.8f, 0.0f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
		glPopMatrix();
	}

	void Ship::Translation(float x, float y)
	{
		glLoadIdentity();

		if ((m_Position.m_X + x > 0.0f && m_Position.m_X + x < 1024.0f) && (m_Position.m_Y + y > 0.0f && m_Position.m_Y + y < 768.0f))
		{
			glTranslatef(m_Position.m_X + x, m_Position.m_Y + y, 0.0f);
		}

		if(m_Position.m_X + x < 0.0f)
		{
			glTranslatef(0.0f, m_Position.m_Y, 0.0f);
		}
		
		if (m_Position.m_Y + y < 0.0f)
		{
			glTranslatef(m_Position.m_X, 0.0f, 0.0f);
		}
		
		//if (m_Position.m_X + x > 1024.0f)
		//{
		//	SetPosition(Vec2(1024.0f, 0.0f));
		//	glTranslatef(1024.0f, m_Position.m_Y, 0.0f);
		//}
		//
		//if (m_Position.m_Y + y >768.0f)
		//{
		//	SetPosition(Vec2(0.0f, 768.0f));
		//	glTranslatef(m_Position.m_Y, 768.0f, 0.0f);
		//}
	}

	void Ship::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}