#include "Astroid.h"

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Astroid::Astroid(Vec2 position)
		:m_Position(position)
	{
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::Render()
	{
		glColor3f(   0.5f,   0.5f, 0.5f);

		glPushMatrix();
		glVertex3f(   0.0f,  55.0f, 0.0f);
		glVertex3f(  47.5f,  27.5f, 0.0f);
		glVertex3f(  47.5f, -27.5f, 0.0f);
		glVertex3f(   0.0f, -55.0f, 0.0f);
		glVertex3f( -47.5f, -27.5f, 0.0f);
		glVertex3f( -47.5f,  27.5f, 0.0f);
		glPopMatrix();
	}

	void Astroid::Translation(float x, float y)
	{
		glLoadIdentity();

		if (m_Position.m_X + x > 0 && m_Position.m_Y + y > 0)
		{
			glTranslatef((GLfloat)((int)(m_Position.m_X + x) % 1024), (GLfloat)((int)(m_Position.m_Y + y) % 768), 0.0f);
		}

		if (m_Position.m_X + x < 0)
		{
			glTranslatef((GLfloat)(1024 + (int)(m_Position.m_X + x) % 1024), (GLfloat)((int)(m_Position.m_Y + y) % 768), 0.0f);
		}

		if (m_Position.m_Y + y < 0)
		{
			glTranslatef((GLfloat)((int)(m_Position.m_X + x) % 1024), (GLfloat)(768 + (int)(m_Position.m_Y + y) % 768), 0.0f);
		}
	}

	void Astroid::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}