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

	void Astroid::Translation()
	{
		glLoadIdentity();

		glTranslatef(m_Position.m_X, m_Position.m_Y, 0.0f);
	}

	void Astroid::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}