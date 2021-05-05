#include "Ship.h"
#include "../src/Window/Window.h"

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
			m_Angle -= 10 * dt;
		}
		
		if (Window::GetInstance()->GetKey[LEFT_ARROW])
		{
			m_Angle += 10 * dt;
		}

		if (Window::GetInstance()->GetKey[D] && m_Position.m_X + m_Translate.m_X < 984.0f)
		{
			m_Accelaration[0] = 500.0f;
		}
		else if (Window::GetInstance()->GetKey[A] && m_Position.m_X + m_Translate.m_X > 20.0f)
		{
			m_Accelaration[0] = -500.0f;
		}
		else
		{
			m_Accelaration[0] = 0.0f;
		}

		if (Window::GetInstance()->GetKey[W] && m_Position.m_Y + m_Translate.m_Y < 698.0f)
		{
			m_Accelaration[1] = 500.0f;
		}
		else if (Window::GetInstance()->GetKey[S] && m_Position.m_Y + m_Translate.m_Y > 20.0f)
		{
			m_Accelaration[1] = -500.0f;
		}
		else
		{
			m_Accelaration[1] = 0.0f;
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
		glColor3f(1.0f, 0.8f, 0.0f);
		glVertex3f(  0.0f,  15.0f, 0.0f);
		glVertex3f( 10.0f, -10.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 0.0f);
	}

	void Ship::Translation()
	{
		glLoadIdentity();

		if ((m_Position.m_X + m_Translate.m_X > 20.0f && m_Position.m_X + m_Translate.m_X < 984.0f) && (m_Position.m_Y + m_Translate.m_Y > 20.0f && m_Position.m_Y + m_Translate.m_Y < 698.0f))
		{
			glTranslatef(m_Position.m_X + m_Translate.m_X, m_Position.m_Y + m_Translate.m_Y, 0.0f);
		}

		if(m_Position.m_X + m_Translate.m_X < 20.0f)
		{
			glTranslatef(20.0f, m_Position.m_Y + m_Translate.m_Y, 0.0f);
		}
		
		if (m_Position.m_Y + m_Translate.m_Y < 20.0f)
		{
			glTranslatef(m_Position.m_X + m_Translate.m_X, 20.0f, 0.0f);
		}
		
		if (m_Position.m_X + m_Translate.m_X > 984.0f)
		{
			glTranslatef(984.0f, m_Position.m_Y + m_Translate.m_Y, 0.0f);
		}
		
		if (m_Position.m_Y + m_Translate.m_Y > 698.0f)
		{
			glTranslatef(m_Position.m_X + m_Translate.m_X, 698.0f, 0.0f);
		}
	}

	void Ship::Rotation()
	{
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	}

}