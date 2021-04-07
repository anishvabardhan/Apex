#include "Renderer.h"

namespace Apex {

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
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
	}

	void Renderer::MainRender()
	{
		glViewport(0, 0, 1024, 768);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		gluPerspective(45.0f, (GLfloat)1024.0f / (GLfloat)768.0f, 1.0f, 1000.0f);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glTranslatef(-1.0f, 0.0f, -5.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f( 0.0f,  1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f( 0.0f,  1.0f, 0.0f);
		glEnd();

		glTranslatef(3.0f, 0.0f, -5.0f);
		glBegin(GL_QUADS);
		glVertex3f( 2.0f,  2.0f, 0.0f);
		glVertex3f( 2.0f, -2.0f, 0.0f);
		glVertex3f(-2.0f, -2.0f, 0.0f);
		glVertex3f(-2.0f,  2.0f, 0.0f);
		glEnd();
	}

}