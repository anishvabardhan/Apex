#pragma once

//#include "Renderable2D.h"

namespace Apex {

	class Renderer
	{
	public:
		Renderer();
	    ~Renderer();

		/*void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Draw(const Renderable2D& renderable) const;
		*/
		void InitRender();

		void Push();
		void Pop();

		static void BeginLineLoop();
		static void BeginLineStrip();
		static void BeginPolygon();
		static void BeginQuads();

		static void End();
		static void Flush();
	};

}