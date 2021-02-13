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

		glDrawElements(GL_TRIANGLES, renderable.GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}