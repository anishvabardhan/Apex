#include "Bullet.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Window/Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/GL.h>

namespace Apex {

	Bullet::Bullet(Vec2 position)
		:m_Position(position), m_Translate(Vec2((cos(m_Angle)), (sin(m_Angle)))), m_Velocity(0.0f), m_Accelaration(0.0f), m_Angle(0.0f)
	{
	}

	Bullet::~Bullet()
	{
	}


	void Bullet::OnUpdate(float dt)
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;
		
		if (Window::GetInstance()->GetKey[RIGHT_ARROW])
		{
			m_Angle -= 5 * dt;
		}
		
		if (Window::GetInstance()->GetKey[LEFT_ARROW])
		{
			m_Angle += 5 * dt;
		}
		
		if (Window::GetInstance()->GetKey[SPACEBAR])
		{
			m_Accelaration = 5.0f;
		}
		
		m_Velocity = m_Accelaration * dt;
		
		m_Translate += Vec2(m_Velocity, m_Velocity);
		
		glTranslatef(m_Position.m_X + (m_Translate.m_X * -cos(-m_Angle)), m_Position.m_Y + (m_Translate.m_Y * -sin(-m_Angle)), 0.0f);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 15.0f, 0.0f);
	}

	void Bullet::Render()
	{
		GLfloat twicePi = 2.0f * (GLfloat)M_PI;

		Renderer::BeginPolygon();

		glColor3f(1.0f, 0.5f, 1.5f);

		for (int i = 0; i < 100; i++)
		{
			glVertex3f((2.0f * cos(i * twicePi / 100)), (2.0f * sin(i * twicePi / 100)), 0.0f);
		}

		Renderer::End();
	}

}