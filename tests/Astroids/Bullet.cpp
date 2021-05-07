#include "Bullet.h"
#include "../src/Graphics/Renderer.h"
#include "../src/Window/Window.h"

#include <GL/GL.h>

namespace Apex {

	Bullet::Bullet()
		:m_Velocity(0.0f), m_Accelaration(0.0f)
	{
	}

	Bullet::~Bullet()
	{
	}


	void Bullet::Render()
	{
		float vertices[36] = {
			  0.0f, 1.0f, 0.0f,
			 0.5f, 0.86f, 0.0f,
			 0.86f, 0.5f, 0.0f,
			  1.0f, 0.0f, 0.0f,
			0.86f, -0.5f, 0.0f,
			0.5f, -0.86f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			-0.5f,-0.86f, 0.0f,
			-0.86f,-0.5f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			-0.86f, 0.5f, 0.0f,
			-0.5f, 0.86f, 0.0f
		};

		glScalef(3.0f, 3.0f, 0.0f);

		Renderer::BeginPolygon();

		glColor3f(1.0f, 0.0f, 1.0f);

		for (int i = 0; i < 36; i += 3)
		{
			glVertex3fv(&vertices[i]);
		}

		Renderer::End();
	}

}