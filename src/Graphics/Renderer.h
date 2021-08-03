#pragma once

#include <string>

#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"
#include "Buffers/FrameBuffer.h"
#include "Mesh.h"
#include "Font.h"
#include "Texture.h"
#include "Shader.h"
#include "../Maths/Maths.h"

namespace Apex {

	class Renderer
	{
	public:
		Renderer();
	    ~Renderer();

		void InitRender();

		void Push();
		void Pop();

		void Drawtext(const Vec2& position, const std::string& asciiText, float quadHeight, Font* font, Shader shader);
		void DrawQuad(Mesh* mesh, Shader shader);
		void DrawFrameBuffer(Mesh* mesh);
		void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);
		void Clear() const;
		void ClearColor() const;

		Font* CreateBitmapFont(const std::string& path);

		static void BeginLineLoop();
		static void BeginLineStrip();
		static void BeginPolygon();
		static void BeginQuads();

		static void End();
		static void Flush();
	};

}