#include "Bullet.h"

#include "Ship.h"

#include <Windows.h>
#include <gl/GL.h>

namespace Apex {

	Bullet::Bullet(Vec2 position)
		:m_Position(position)
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Render()
	{
		glPushMatrix();
		glColor3f(  1.0f,  0.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
		glPopMatrix();
	}

	void Bullet::PivotAxis(float x, float y)
	{
		glTranslatef(x, y, 0.0f);
	}

	void Bullet::Translation(float x, float y)
	{
		glLoadIdentity();
		glTranslatef(m_Position.m_X + x, m_Position.m_Y + y, 0.0f);
	}

	void Bullet::Rotation(float angle)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
	}

}