#include "Ship.h"

#include "../src/Window/Window.h"
#include "../src/Graphics/Renderer.h"

#include <gl/GL.h>

namespace Apex {

	Ship::Ship(Vec2 position)
		:m_Position(position), m_Translate(Vec2(0.0f, 0.0f)), m_Angle(0), m_Velocity{ 0.0f, 0.0f }, m_Accelaration{ 0.0f, 0.0f }
	{
	}

	Ship::~Ship()
	{
	}

	void Ship::OnUpdate(float dt)
	{
		if (Window::GetInstance()->GetKey[RIGHT_ARROW])
		{
			m_Angle -= 5 * dt;
		}
		
		if (Window::GetInstance()->GetKey[LEFT_ARROW])
		{
			m_Angle += 5 * dt;
		}

		if (Window::GetInstance()->GetKey[D] && m_Accelaration[0] <= 350.0f)
		{
			m_Accelaration[0] +=  2 * dt;
		}
		else if (Window::GetInstance()->GetKey[A] && m_Accelaration[0] >= -350.0f)
		{
			m_Accelaration[0] -= 2 * dt;
		}
		else if(m_Accelaration[0] > 0.0f)
		{
			m_Accelaration[0] -= dt;
		}
		else if (m_Accelaration[0] < 0.0f)
		{
			m_Accelaration[0] += dt;
		}

		if (Window::GetInstance()->GetKey[W] && m_Accelaration[1] <= 350.0f)
		{
			m_Accelaration[1] += 2 * dt;
		}
		else if (Window::GetInstance()->GetKey[S] && m_Accelaration[1] >= -350.0f)
		{
			m_Accelaration[1] -= 2 * dt;
		}
		else if (m_Accelaration[1] > 0.0f)
		{
			m_Accelaration[1] -= dt;
		}
		else if (m_Accelaration[1] < 0.0f)
		{
			m_Accelaration[1] += dt;
		}

		m_Velocity[0] = m_Accelaration[0] * dt;
		m_Velocity[1] = m_Accelaration[1] * dt;

		m_Translate.m_X += m_Velocity[0] * dt;
		m_Translate.m_Y += m_Velocity[1] * dt;

		Translation();

		Rotation();
	}

	void Ship::Render()
	{

		float vertices[12] = {
			  0.0f,  15.0f, 0.0f,
			 10.0f, -10.0f, 0.0f,
			  0.0f,   0.0f, 0.0f,
			-10.0f, -10.0f, 0.0f
		};

		Renderer::BeginLineLoop();

		glColor3f(1.0f, 0.8f, 0.0f);
		
		for (int i = 0; i < 12; i += 3)
		{
			glVertex3fv(&vertices[i]);
		}

		Renderer::End();
	}

	void Ship::Translation()
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

	void Ship::Rotation()
	{
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	}

}