#include "Astroid.h"

#include "../src/Maths/Random.h"
#include "../src/Graphics/Renderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Random random1(100, 500), random2(-400, 400);

	Astroid::Astroid(Vec2 position, int i)
		:m_Position(position), m_Translate(Vec2(random1.GetRandomInRange(), random1.GetRandomInRange())), m_Angle(0.0f), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ random2.GetRandomInRange(), random2.GetRandomInRange() }
	{
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::OnUpdate(float dt)
	{
		m_Velocity[0] = m_Accelaration[0] * dt;
		m_Velocity[1] = m_Accelaration[1] * dt;

		m_Translate.m_X += m_Velocity[0] * dt;
		m_Translate.m_Y += m_Velocity[1] * dt;

		Translation();
	} 

	void Astroid::Render()
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		Renderer::BeginLineLoop();

		glColor3f(0.5f, 0.5f, 0.5f);

		for (int i = 0; i < 6; i++)
		{
			glVertex3f((55.0f * cos(i * twicePi / 6)), (55.0f * sin(i * twicePi / 6)), 0.0f);
		}

		Renderer::End();
	}

	void Astroid::Translation()
	{
		glLoadIdentity();

		if ((m_Position.m_X + m_Translate.m_X > 0.0f && m_Position.m_X + m_Translate.m_X < 1024.0f) 
			&& (m_Position.m_Y + m_Translate.m_Y > 0.0f && m_Position.m_Y + m_Translate.m_Y < 768.0f))
		{
			glTranslatef(m_Position.m_X + m_Translate.m_X, m_Position.m_Y + m_Translate.m_Y, 0.0f);
		}

		if (m_Position.m_X + m_Translate.m_X < 0.0f)
		{
			m_Translate.m_X = 1024.0f + (float)((int)(m_Translate.m_X) % 1024);
		}

		if (m_Position.m_Y + m_Translate.m_Y < 0.0f)
		{
			m_Translate.m_Y = 768.0f + (float)((int)(m_Translate.m_Y) % 768);
		}

		if (m_Position.m_X + m_Translate.m_X > 1024.0f)
		{
			m_Translate.m_X = (float)((int)(m_Position.m_X + m_Translate.m_X) % 1024) - m_Position.m_X;
		}

		if (m_Position.m_Y + m_Translate.m_Y > 768.0f)
		{
			m_Translate.m_Y = (float)((int)(m_Position.m_Y + m_Translate.m_Y) % 768) - m_Position.m_Y;
		}
	}

	void Astroid::Rotation()
	{
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	}

}