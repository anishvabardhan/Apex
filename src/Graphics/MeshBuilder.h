#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Maths/Vec4.h"
#include <vector>
#include <GL/glew.h>

namespace Apex {

	class VertexArrayObject;
	class VertexBuffer;
	class IndexBuffer;

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:           return 4;
			case GL_UNSIGNED_INT:    return 4;
			case GL_UNSIGNED_BYTE:   return 1;
			}

			return 0;
		}
	};

	struct VertexBufferLayout
	{

		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;

		VertexBufferLayout(): m_Stride(0) {}
	};

	struct VertexPCU
	{
		Vec3 m_Pos;
		Vec4 m_Color;
		Vec2 m_UV;

		VertexPCU(Vec3 position, Vec4 color, Vec2 uv);
	};

	struct MeshBuilder
	{
		GLenum m_DrawType;
		VertexArrayObject* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;
		std::vector<VertexPCU> m_Vertices;
		unsigned int m_Indices[6];
		VertexBufferLayout* m_Layout;

		MeshBuilder();
		~MeshBuilder();

		void Begin(GLenum drawType);
		void Push(VertexPCU pcu);
		void End();
		void CreateMesh();
	};

}