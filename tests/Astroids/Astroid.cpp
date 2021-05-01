#include "Astroid.h"

#include "../src/Maths/Random.h"

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Random random(100, 500);

	Astroid::Astroid(Vec2 position, int i)
		:m_Position(position), m_Translate(Vec2(random.GetRandomInRange(), random.GetRandomInRange())), m_Angle(0.0f), m_Velocity(0.0f), m_Accelaration(random.GetRandomInRange())
	{
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::OnUpdate(float dt)
	{
		m_Velocity = m_Accelaration * dt;

		m_Translate.m_X += m_Velocity * dt;
		m_Translate.m_Y += m_Velocity * dt;

		m_Angle += m_Velocity * dt;

		Translation();
		Rotation();
	}

	void Astroid::Render()
	{
		glColor3f(    0.5f,   0.5f, 0.5f);
		glVertex3f(   0.0f,  55.0f, 0.0f);
		glVertex3f(  47.5f,  27.5f, 0.0f);
		glVertex3f(  47.5f, -27.5f, 0.0f);
		glVertex3f(   0.0f, -55.0f, 0.0f);
		glVertex3f( -47.5f, -27.5f, 0.0f);
		glVertex3f( -47.5f,  27.5f, 0.0f);
	}

	void Astroid::Translation()
	{
		glLoadIdentity();

		if ((m_Position.m_X + m_Translate.m_X > 0.0f && m_Position.m_X + m_Translate.m_X < 1024.0f) && (m_Position.m_Y + m_Translate.m_Y > 0.0f && m_Position.m_Y + m_Translate.m_Y < 768.0f))
		{
			glTranslatef(m_Position.m_X + m_Translate.m_X, m_Position.m_Y + m_Translate.m_Y, 0.0f);
		}
	}

	void Astroid::Rotation()
	{
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	}

}