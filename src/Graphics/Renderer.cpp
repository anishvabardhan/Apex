#include "Renderer.h"

#include "Window/Window.h"
#include "Input/Input.h"

#include <gl/GL.h>

namespace Apex {

	/*void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Draw(const Renderable2D& renderable) const
	{
		renderable.GetVAO()->Bind();
		renderable.GetIBO()->Bind();
		renderable.GetShader().Bind();

		glDrawElements(GL_LINE_STRIP, renderable.GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}*/

	void Renderer::InitRender()
	{
		//--------------------------------------------------------------------------------------------------
		//Setup OpenGL3 Viewport----------------------------------------------------------------------------
		
		glViewport(0, 0, 1024, 768);

		//--------------------------------------------------------------------------------------------------
		//Setup an Identity Matrix--------------------------------------------------------------------------

		glLoadIdentity();

		//--------------------------------------------------------------------------------------------------
        //Set Current Matrix to Projection Matrix-----------------------------------------------------------
		
		glMatrixMode(GL_PROJECTION);
		
		//--------------------------------------------------------------------------------------------------
		//Multiply Orthographic Matrix to Current Matrix----------------------------------------------------

		glOrtho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);

		//--------------------------------------------------------------------------------------------------
		//Clear Buffers to Preset Values--------------------------------------------------------------------

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		//--------------------------------------------------------------------------------------------------
		//Specify Clear Values for the Color Buffers--------------------------------------------------------

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Renderer::MainRender()
	{
		//----------------------------------------------------------------------------------------------
		//Multiply Translation Matrix to Current Matrix-------------------------------------------------

		glTranslatef(512.0f, 384.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(   0.0f,  100.0f, 0.0f);
		glVertex3f( 100.0f, -100.0f, 0.0f);
		glVertex3f(-100.0f, -100.0f, 0.0f);
		glVertex3f(   0.0f,  100.0f, 0.0f);
		glEnd();
	}

}