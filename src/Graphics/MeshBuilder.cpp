#include "MeshBuilder.h"

namespace Apex {

	VertexPCU::VertexPCU(Vec3 position, Vec4 color, Vec2 uv)
		: m_Pos(position), m_Color(color), m_UV(uv)
	{
	}

	MeshBuilder::MeshBuilder()
		: m_Mesh(nullptr)
	{
	}
	
	MeshBuilder::~MeshBuilder()
	{
		delete m_Mesh;
	}
	
	void MeshBuilder::Push(VertexPCU pcu)
	{
		m_Vertices.push_back(pcu);
	}

	void MeshBuilder::CopyToGPU()
	{
		m_Layout.Push(3);
		m_Layout.Push(4);
		m_Layout.Push(2);

		m_Mesh = new Mesh(m_Vertices, m_Layout);
	}

}