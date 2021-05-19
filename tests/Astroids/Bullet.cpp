#include "Bullet.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Window/Window.h"

#include "Ship.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/GL.h>

namespace Apex {

	Bullet::Bullet(Vec2 position)
		:m_Position(position), m_Translate(Vec2(0, 0)), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ 0.0f, 0.0f }, m_Angle(0.0f), m_Radius(1.0f), m_NumOfVertices(10), g_BulletVelocity{ 0.0f, 0.0f }, 
		g_BulletAccelaration{ 0.0f, 0.0f }
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		for (int i = 0; i < m_NumOfVertices; i++)
		{
			m_BodyVertices[i] = Vec3((m_Radius * cos(i * twicePi / m_NumOfVertices)), (m_Radius * sin(i * twicePi / m_NumOfVertices)), 0.0f);
		}
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::OnUpdate(Vec2 position, Vec2 spawnPosition, float dt)
	{
		position += m_Position;

		if ((position.m_X > 0.0f && position.m_X < 1024.0f)
			&& (position.m_Y > 0.0f && position.m_Y < 768.0f))
		{
			glTranslatef(position.m_X, position.m_Y, 0.0f);
		}

		if (position.m_X < 0.0f)
		{
			position.m_X = 1024.0f + (float)((int)(position.m_X) % 1024);
		}

		if (position.m_Y < 0.0f)
		{
			position.m_Y = 768.0f + (float)((int)(position.m_Y) % 768);
		}

		if (position.m_X > 1024.0f)
		{
			position.m_X = (float)((int)(position.m_X) % 1024) - position.m_X;
		}

		if (position.m_Y > 768.0f)
		{
			position.m_Y = (float)((int)(position.m_Y) % 768) - position.m_Y;
		}

		Rotation();
	}

	void Bullet::Render()
	{
		GLfloat vertices[30] = {
			m_BodyVertices[0].m_X, m_BodyVertices[0].m_Y, m_BodyVertices[0].m_Z,
			m_BodyVertices[1].m_X, m_BodyVertices[1].m_Y, m_BodyVertices[1].m_Z,
			m_BodyVertices[2].m_X, m_BodyVertices[2].m_Y, m_BodyVertices[2].m_Z,
			m_BodyVertices[3].m_X, m_BodyVertices[3].m_Y, m_BodyVertices[3].m_Z,
			m_BodyVertices[4].m_X, m_BodyVertices[4].m_Y, m_BodyVertices[4].m_Z,
			m_BodyVertices[5].m_X, m_BodyVertices[5].m_Y, m_BodyVertices[5].m_Z,
			m_BodyVertices[6].m_X, m_BodyVertices[6].m_Y, m_BodyVertices[6].m_Z,
			m_BodyVertices[7].m_X, m_BodyVertices[7].m_Y, m_BodyVertices[7].m_Z,
			m_BodyVertices[8].m_X, m_BodyVertices[8].m_Y, m_BodyVertices[8].m_Z,
			m_BodyVertices[9].m_X, m_BodyVertices[9].m_Y, m_BodyVertices[9].m_Z
		};

		Renderer::BeginPolygon();

		glColor3f(0.0f, 1.0f, 0.0f);

		for (int i = 0; i < m_NumOfVertices * 3; i += 3)
		{
			glVertex3fv(&vertices[i]);
		}

		Renderer::End();
	}

	void Bullet::Rotation()
	{
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	}

}