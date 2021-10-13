#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Maths/Vec4.h"
#include <vector>
#include <GL/glew.h>

namespace Apex {

	struct Mesh;

	struct VertexBufferElement
	{
		unsigned int m_Type;
		unsigned int m_ElementCount;
		unsigned char m_Normalized;

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

		VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized);
	};

	struct VertexBufferLayout
	{
		std::vector<VertexBufferElement> m_Element;
		unsigned int m_Stride;

		VertexBufferLayout(const std::vector<VertexBufferElement> element, unsigned int stride);
	};

	struct VertexPCU
	{
		Vec3 m_Pos;
		Vec4 m_Color;
		Vec2 m_UV;

		static std::vector<VertexBufferElement> m_Attributes;
		static VertexBufferLayout m_Layout;

		VertexPCU();
		VertexPCU(Vec3 position, Vec4 color, Vec2 uv);
	};

	struct MeshBuilder
	{
		std::vector<VertexPCU> m_Vertices;

		MeshBuilder();
		~MeshBuilder();

		void Push(VertexPCU vertex);

		template<typename FORMAT>
		Mesh* CreateMesh();
	};

	template Mesh* MeshBuilder::CreateMesh<VertexPCU>();

}