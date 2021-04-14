#pragma once

//#include "Renderable2D.h"

namespace Apex {

	class Renderer
	{
	public:
		/*void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Draw(const Renderable2D& renderable) const;
		*/
		void InitRender();

		void BeginLine();
		void BeginQuads();
		void End();
	};

}