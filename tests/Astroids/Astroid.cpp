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
		:m_Position(position), m_Translate(Vec2(random1.GetRandomInRange(), random1.GetRandomInRange())), m_Angle(0.0f), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ random2.GetRandomInRange(), random2.GetRandomInRange() }, m_NumOfVertices(6), m_Radius(55.0f)
	{
		float twicePi = 2 * (float)M_PI;

		for (int i = 0; i < m_NumOfVertices; i++)
		{
			m_Radius = Random::GetRandomFloatInRange(30.0f, 55.0f);

			m_BodyVertices[i] = Vec3(m_Radius * cos(i * (twicePi / m_NumOfVertices)), m_Radius * sin(i * (twicePi / m_NumOfVertices)), 0.0f);
		}
	}

	Astroid::~Astroid()
	{
	}

	void Astroid::OnUpdate(float dt)
	{
		m_Velocity = m_Accelaration * dt;

		m_Translate += m_Velocity * dt;

		Translation();
	} 

	void Astroid::Render()
	{
		float vertices[18] = {
			m_BodyVertices[0].m_X, m_BodyVertices[0].m_Y, m_BodyVertices[0].m_Z,
			m_BodyVertices[1].m_X, m_BodyVertices[1].m_Y, m_BodyVertices[1].m_Z,
			m_BodyVertices[2].m_X, m_BodyVertices[2].m_Y, m_BodyVertices[2].m_Z,
			m_BodyVertices[3].m_X, m_BodyVertices[3].m_Y, m_BodyVertices[3].m_Z,
			m_BodyVertices[4].m_X, m_BodyVertices[4].m_Y, m_BodyVertices[4].m_Z,
			m_BodyVertices[5].m_X, m_BodyVertices[5].m_Y, m_BodyVertices[5].m_Z
		};

		Renderer::BeginLineLoop();

		glColor3f(0.5f, 0.5f, 0.5f);

		for (int i = 0; i < 18; i += 3)
		{
			glVertex3fv(&vertices[i]);
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