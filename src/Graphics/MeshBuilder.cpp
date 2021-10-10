#include "MeshBuilder.h"

#include "Buffers/VertexArrayObject.h"
#include "Buffers/IndexBuffer.h"

namespace Apex {

	VertexPCU::VertexPCU(Vec3 position, Vec4 color, Vec2 uv)
		: m_Pos(position), m_Color(color), m_UV(uv)
	{
	}

	MeshBuilder::MeshBuilder()
		: m_IBO(nullptr), m_VAO(nullptr), m_VBO(nullptr)
	{
		m_Indices[0] = 0;
		m_Indices[1] = 1;
		m_Indices[2] = 2;
		m_Indices[3] = 2;
		m_Indices[4] = 3;
		m_Indices[5] = 0;
	}
	
	MeshBuilder::~MeshBuilder()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_VBO;
		delete m_Layout;
	}
	
	void MeshBuilder::Begin(GLenum drawType)
	{
		m_DrawType = drawType;

		m_VAO->Bind();
		m_IBO->Bind();
	}

	void MeshBuilder::Push(VertexPCU pcu)
	{
		m_Vertices.push_back(pcu);
	}

	void MeshBuilder::End()
	{
		m_VAO->UnBind();
		m_IBO->UnBind();

		while (!m_Layout->m_Elements.empty())
		{
			m_Layout->m_Elements.pop_back();
		}

		m_Layout->m_Stride = 0;
	}

	void MeshBuilder::CreateMesh()
	{
		float positions[] = {
			//PositionCoords		                                                                             //Color                                                                        //TextureCoords
			m_Vertices[0].m_Pos.m_X, m_Vertices[0].m_Pos.m_Y, m_Vertices[0].m_Pos.m_Z,     m_Vertices[0].m_Color.m_X, m_Vertices[0].m_Color.m_Y, m_Vertices[0].m_Color.m_Z, m_Vertices[0].m_Color.m_W,      m_Vertices[0].m_UV.m_X, m_Vertices[0].m_UV.m_Y,  // 0
			m_Vertices[1].m_Pos.m_X, m_Vertices[1].m_Pos.m_Y, m_Vertices[1].m_Pos.m_Z,     m_Vertices[1].m_Color.m_X, m_Vertices[1].m_Color.m_Y, m_Vertices[1].m_Color.m_Z, m_Vertices[1].m_Color.m_W,      m_Vertices[1].m_UV.m_X, m_Vertices[1].m_UV.m_Y,  // 1
			m_Vertices[2].m_Pos.m_X, m_Vertices[2].m_Pos.m_Y, m_Vertices[2].m_Pos.m_Z,     m_Vertices[2].m_Color.m_X, m_Vertices[2].m_Color.m_Y, m_Vertices[2].m_Color.m_Z, m_Vertices[2].m_Color.m_W,      m_Vertices[2].m_UV.m_X, m_Vertices[2].m_UV.m_Y,  // 2
			m_Vertices[3].m_Pos.m_X, m_Vertices[3].m_Pos.m_Y, m_Vertices[3].m_Pos.m_Z,     m_Vertices[3].m_Color.m_X, m_Vertices[3].m_Color.m_Y, m_Vertices[3].m_Color.m_Z, m_Vertices[3].m_Color.m_W,      m_Vertices[3].m_UV.m_X, m_Vertices[3].m_UV.m_Y   // 3
		};

		m_Layout = new VertexBufferLayout();

		m_Layout->m_Elements.push_back({ GL_FLOAT, 3, GL_FALSE });
		m_Layout->m_Elements.push_back({ GL_FLOAT, 4, GL_FALSE });
		m_Layout->m_Elements.push_back({ GL_FLOAT, 2, GL_FALSE });

		for (auto i : m_Layout->m_Elements)
		{
			m_Layout->m_Stride += i.count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}

		m_VAO = new VertexArrayObject();

		m_VBO = new VertexBuffer(positions, 4 * 9 * sizeof(float));

		m_VAO->AddBuffer(*m_VBO, *m_Layout);

		m_IBO = new IndexBuffer(m_Indices, 6);
	}

}