#pragma once

#include "Buffers/VertexBufferLayout.h"
#include "../Maths/Maths.h"
#include <vector>
#include <GL/glew.h>

namespace Apex {

	class VertexArrayObject;
	class IndexBuffer;
	class VertexBuffer;

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
		VertexBufferLayout m_Layout;
		std::vector<VertexPCU> m_Vertices;
		unsigned int m_Indices[6];

		MeshBuilder();
		~MeshBuilder();

		void Begin(GLenum drawType);
		void Push(VertexPCU pcu);
		void End();

		void CreateMesh();
	};

}