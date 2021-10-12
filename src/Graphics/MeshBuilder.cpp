#include "MeshBuilder.h"

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"

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
		: m_VAO(nullptr), m_VBO(nullptr), m_IBO(nullptr)
	{
	}
	
	MeshBuilder::~MeshBuilder()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_VBO;
	}
	
	void MeshBuilder::Begin(GLenum drawType)
	{
		m_DrawType = drawType;

		m_VAO->Bind();
		m_IBO->Bind();
	}

	void MeshBuilder::End()
	{
		m_VAO->UnBind();
		m_IBO->UnBind();
	}

	template <typename FORMAT>
	void MeshBuilder::CreateMesh(const FORMAT vertices[])
	{
		int size = sizeof(vertices);

		FORMAT* temp = new FORMAT[sizeof(FORMAT) * size];

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		for (int i = 0; i < size; i++)
		{
			temp[i] = FORMAT(vertices[i]);
		}
	
		m_VAO = new VertexArrayObject();
	
		m_VBO = new VertexBuffer(temp, size * FORMAT::m_Layout.m_Stride);
	
		m_VAO->AddBuffer(*m_VBO, FORMAT::m_Layout);
	
		m_IBO = new IndexBuffer(indices, 6);

		delete[] temp;
	}

}