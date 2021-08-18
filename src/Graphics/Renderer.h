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

	enum APEX_BLEND_FACTOR {
		APEX_ZERO                      =      GL_ZERO,
		APEX_ONE                       =      GL_ONE,
		APEX_SRC_COLOR                 =      GL_SRC_COLOR,
		APEX_ONE_MINUS_SRC_COLOR       =      GL_ONE_MINUS_SRC_COLOR,
		APEX_DST_COLOR                 =      GL_DST_COLOR,
		APEX_ONE_MINUS_DST_COLOR       =      GL_ONE_MINUS_DST_COLOR,
		APEX_SRC_ALPHA                 =      GL_SRC_ALPHA,
		APEX_ONE_MINUS_SRC_ALPHA       =      GL_ONE_MINUS_SRC_ALPHA,
		APEX_DST_ALPHA                 =      GL_DST_ALPHA,
		APEX_ONE_MINUS_DST_ALPHA       =      GL_ONE_MINUS_DST_ALPHA,
		APEX_CONSTANT_COLOR            =      GL_CONSTANT_COLOR,
		APEX_ONE_MINUS_CONSTANT_COLOR  =      GL_ONE_MINUS_CONSTANT_COLOR,
		APEX_CONSTANT_ALPHA            =      GL_CONSTANT_ALPHA,
		APEX_ONE_MINUS_CONSTANT_ALPHA  =      GL_ONE_MINUS_CONSTANT_ALPHA,
	};

	enum APEX_BLEND_OP {
		APEX_FUNC_ADD                  =      GL_FUNC_ADD,
		APEX_FUNC_SUBTRACT             =      GL_FUNC_SUBTRACT,
		APEX_FUNC_REVERSE_SUBTRACT     =      GL_FUNC_REVERSE_SUBTRACT,
		APEX_MIN                       =      GL_MIN,
		APEX_MAX                       =      GL_MAX
	};

	class Renderer
	{
	public:
		Renderer();
	    ~Renderer();

		void InitRender();

		void Push();
		void Pop();

		void Drawtext(const Vec2& position, const std::string& asciiText, float quadHeight, Font* font, Shader shader);
		void DrawQuad(const Vec2& position, const Vec2& dimensions, const Texture& texture, const AABB2& texCoords, const Vec4& color, Shader shader);
		void DrawQuad(Mesh* mesh, Shader shader);
		void DrawFrameBuffer(Mesh* mesh);
		void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);
		void Clear() const;
		void ClearColor() const;

		Font* CreateBitmapFont(const std::string& path);
		Texture* CreateTexture(const std::string& path);

		static void BeginLineLoop();
		static void BeginLineStrip();
		static void BeginPolygon();
		static void BeginQuads();

		static void EnableBlend(enum APEX_BLEND_FACTOR src, enum APEX_BLEND_FACTOR dest, enum APEX_BLEND_OP mode = APEX_BLEND_OP::APEX_FUNC_ADD);
		static void DisableBlend();

		static void End();
		static void Flush();
	};

}