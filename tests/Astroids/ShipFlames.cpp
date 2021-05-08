#include "ShipFlames.h"

#include "../src/Graphics/Renderer.h"
#include "../src/Window/Window.h"

#include <GL/GL.h>

namespace Apex {

	void ShipFlames::RenderRight()
	{
		GLfloat vertices1[12] = {
			10.0f, -10.0f, 0.0f,
			15.0f, -15.0f, 0.0f,
			10.0f, -35.0f, 0.0f,
			 5.0f, -15.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[LEFT_ARROW])
		{
			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices1[i]);
			}

			Renderer::End();
		}

		GLfloat vertices2[12] = {
			-10.0f, -10.0f, 0.0f,
			-15.0f, -15.0f, 0.0f,
			-10.0f, -35.0f, 0.0f,
			 -5.0f, -15.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[A])
		{
			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices1[i]);
			}

			Renderer::End();

			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices2[i]);
			}

			Renderer::End();
		}
	}

	void ShipFlames::RenderLeft()
	{
		GLfloat vertices2[12] = {
			-10.0f, -10.0f, 0.0f,
			-15.0f, -15.0f, 0.0f,
			-10.0f, -35.0f, 0.0f,
			 -5.0f, -15.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[RIGHT_ARROW])
		{
			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices2[i]);
			}

			Renderer::End();
		}

		GLfloat vertices1[12] = {
			10.0f, -10.0f, 0.0f,
			15.0f, -15.0f, 0.0f,
			10.0f, -35.0f, 0.0f,
			 5.0f, -15.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[D])
		{
			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices1[i]);
			}

			Renderer::End();

			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices2[i]);
			}

			Renderer::End();
		}
	}

	void ShipFlames::Render()
	{
		GLfloat vertices1[12] = {
			10.0f, -10.0f, 0.0f,
			15.0f, -15.0f, 0.0f,
			10.0f, -35.0f, 0.0f,
			 5.0f, -15.0f, 0.0f
		};

		GLfloat vertices2[12] = {
			-10.0f, -10.0f, 0.0f,
			-15.0f, -15.0f, 0.0f,
			-10.0f, -35.0f, 0.0f,
			 -5.0f, -15.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[W] || Window::GetInstance()->GetKey[S])
		{
			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices1[i]);
			}

			Renderer::End();

			Renderer::BeginQuads();

			glColor3f(1.0f, 0.27f, 0.0f);

			for (int i = 0; i < 12; i += 3)
			{
				glVertex3fv(&vertices2[i]);
			}

			Renderer::End();
		}
	}
}