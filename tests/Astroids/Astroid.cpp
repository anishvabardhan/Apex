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
		glColor3f(   1.0f,   0.0f, 0.0f);
		glVertex3f(  0.0f,  25.0f, 0.0f);
		glVertex3f( 16.5f,  16.5f, 0.0f);
		glVertex3f( 16.5f, -16.5f, 0.0f);
		glVertex3f(  0.0f, -25.0f, 0.0f);
		glVertex3f(-16.5f, -16.5f, 0.0f);
		glVertex3f(-16.5f,  16.5f, 0.0f);
	}

	void Astroid::Translation()
	{
		glTranslatef(m_Position.m_X, m_Position.m_Y, 0.0f);
	}

}