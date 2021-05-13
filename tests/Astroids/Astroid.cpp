#include "Astroid.h"

#include "../src/Maths/Random.h"
#include "../src/Graphics/Renderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Random random1(100, 500), random2(-100, 100);

	Astroid::Astroid(Vec2 position, int i)
		:m_Position(position), m_Translate(Vec2(random1.GetRandomInRange(), random1.GetRandomInRange())), m_Angle(0.0f), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ random2.GetRandomInRange(), random2.GetRandomInRange() }, m_NumOfVertices(10)
	{
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::OnUpdate(float dt)
	{
		m_Velocity.m_X = m_Accelaration.m_X * dt;
		m_Velocity.m_Y = m_Accelaration.m_Y * dt;

		m_Translate.m_X += m_Velocity.m_X * dt;
		m_Translate.m_Y += m_Velocity.m_Y * dt;

		Translation();
	} 

	void Astroid::Render()
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		Renderer::BeginLineLoop();

		glColor3f(0.5f, 0.5f, 0.5f);

		for (int i = 0; i < m_NumOfVertices; i++)
		{
			glVertex3f((55.0f * cos(i * twicePi / m_NumOfVertices)), (55.0f * sin(i * twicePi / m_NumOfVertices)), 0.0f);
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