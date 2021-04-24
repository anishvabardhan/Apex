#include "Astroid.h"

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Astroid* g_Astroid = nullptr;

	Astroid::Astroid(Vec2 position)
		:m_Position(position)
	{
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::Render()
	{
		glPushMatrix();
		glColor3f(    0.5f,   0.5f, 0.5f);
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

		if ((m_Position.m_X + x > 0.0f && m_Position.m_X + x < 1024.0f) && (m_Position.m_Y + y > 0.0f && m_Position.m_Y + y < 768.0f))
		{
			glTranslatef(m_Position.m_X + x, m_Position.m_Y + y, 0.0f);
		}

		if (m_Position.m_X + x + 55.0f > 1024.0f)
		{
			x = -x;
		}

		if (m_Position.m_Y + y + 55.0f > 768.0f)
		{
			y = -y;
		}
	}

	void Astroid::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

	Astroid* Astroid::GetInstance()
	{
		return g_Astroid;
	}

}