#include "MeshBuilder.h"

#include "Mesh.h"

namespace Apex {

	std::vector<VertexBufferElement> VertexPCU::m_Attributes = {
		VertexBufferElement(GL_FLOAT, 3, GL_FALSE),
		VertexBufferElement(GL_FLOAT, 4, GL_FALSE),
		VertexBufferElement(GL_FLOAT, 2, GL_FALSE)
	};

	VertexBufferLayout VertexPCU::m_Layout(VertexPCU::m_Attributes, sizeof(VertexPCU));

	VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement> element, unsigned int stride)
		: m_Element(element), m_Stride(stride)
	{
	}

	VertexBufferElement::VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
		: m_Type(type), m_ElementCount(count), m_Normalized(normalized)
	{
	}

	VertexPCU::VertexPCU()
		: m_Pos(Vec3(0, 0, 0)), m_Color(Vec4(0, 0, 0, 0)), m_UV(Vec2(0, 0))
	{
	}

	VertexPCU::VertexPCU(Vec3 position, Vec4 color, Vec2 uv)
		: m_Pos(position), m_Color(color), m_UV(uv)
	{
	}

	MeshBuilder::MeshBuilder()
	{
	}
	
	MeshBuilder::~MeshBuilder()
	{
	}

	void MeshBuilder::Push(VertexPCU vertex)
	{
		m_Vertices.push_back(vertex);
	}

	template <typename FORMAT>
	Mesh* MeshBuilder::CreateMesh()
	{
		int size = m_Vertices.size();

		FORMAT* temp = new FORMAT[sizeof(FORMAT) * size];

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		for (int i = 0; i < size; i++)
		{
			temp[i] = (FORMAT)m_Vertices[i];
		}

		Mesh* mesh = new Mesh(temp, &FORMAT::m_Layout);

		delete[] temp;

		return mesh;
	}

}