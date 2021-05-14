#include "Bullet.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Window/Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/GL.h>

namespace Apex {

	Bullet::Bullet(Vec2 position)
		:m_Position(position), m_Translate{ 0.0f, 0.0f }, m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ 0.0f, 0.0f }, m_Angle(0.0f)
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Render(float dt)
	{
		if (Window::GetInstance()->GetKey[A])
		{
			m_Angle += 5 * dt;
		}
		else if (Window::GetInstance()->GetKey[D])
		{
			m_Angle -= 5 * dt;
		}

		if (Window::GetInstance()->GetKey[SPACEBAR])
		{
			m_Accelaration = Vec2(50.0f, 50.0f);
		}
		else
		{
			m_Accelaration = Vec2(0.0f, 0.0f);
		}

		Vec2 forwardDir = m_Position.GetNormalised();

		m_Velocity = m_Accelaration * forwardDir;

		m_Translate.m_X += m_Velocity.m_X * dt * dt;
		m_Translate.m_Y += m_Velocity.m_Y * dt * dt;

		glTranslatef(m_Position.m_X + m_Translate.m_X, m_Position.m_Y + m_Translate.m_Y, 0.0f);

		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);

		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		Renderer::BeginPolygon();

		glColor3f(0.0f, 1.0f, 0.0f);

		for (int i = 0; i < 100; i++)
		{
			glVertex3f((200.0f * cos(i * twicePi / 100)), (200.0f * sin(i * twicePi / 100)), 0.0f);
		}

		Renderer::End();
	}

}