#pragma once

#include "Buffers/VertexBufferLayout.h"
#include "Mesh.h"

#include <vector>

#include <GL/glew.h>

namespace Apex {

	struct VertexPCU
	{
		Vec3 m_Pos;
		Vec4 m_Color;
		Vec2 m_UV;

		VertexPCU(Vec3 position, Vec4 color, Vec2 uv);
	};

	class MeshBuilder
	{
		Mesh* m_Mesh;
		VertexBufferLayout m_Layout;
		std::vector<VertexPCU> m_Vertices;
		unsigned int m_Indices[6] = { 0, 1, 2, 2, 3, 0 };
	public:
		MeshBuilder();
		~MeshBuilder();

		void Push(VertexPCU pcu);
		void CopyToGPU();

		inline Mesh* GetMesh() const { return m_Mesh; }
	};

}