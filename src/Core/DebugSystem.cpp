#include "DebugSystem.h"
#include "Graphics/Renderer.h"
#include "Window/Window.h"

#include <GL/GL.h>

namespace Apex {

	DebugSystem::DebugSystem()
	{
	}

	DebugSystem::~DebugSystem()
	{
	}

	void DebugSystem::DebugCircle(float scale)
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

		if (Window::GetInstance()->GetKey[F1])
		{
			glScalef(scale, scale, 0.0f);

			Renderer::BeginLine();

			glColor3f(0.0f, 1.0f, 0.0f);

			for (int i = 0; i < 36; i += 3)
			{
				glVertex3fv(&vertices[i]);
			}

			Renderer::End();
		}

	}

	void DebugSystem::DebugLine()
	{
		float vertices[6] = {
			0.0f,  15.0f,  0.0f,
			0.0f, 2000.0f, 0.0f
		};

		if (Window::GetInstance()->GetKey[F2])
		{
			glBegin(GL_LINE_STRIP);

			glColor3f(1.0f, 0.0f, 0.0f);

			for (int i = 0; i < 6; i += 3)
			{
				glVertex3fv(&vertices[i]);
			}

			glEnd();
		}
	}

}