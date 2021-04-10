#include "Astroid.h"

#include <gl/glew.h>

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
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(  0.0f,  50.0f, 0.0f);
		glVertex3f( 25.0f,  25.0f, 0.0f);
		glVertex3f( 25.0f, -25.0f, 0.0f);
		glVertex3f(  0.0f, -50.0f, 0.0f);
		glVertex3f(-25.0f, -25.0f, 0.0f);
		glVertex3f(-25.0f,  25.0f, 0.0f);
		glPopMatrix();
	}

	void Astroid::Translation()
	{
		glTranslatef(m_Position.m_X, m_Position.m_Y, 0.0f);
	}

}