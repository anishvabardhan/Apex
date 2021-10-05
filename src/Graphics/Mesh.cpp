#include "Mesh.h"

#include "MeshBuilder.h"

namespace Apex {

	Mesh::Mesh(std::vector<VertexPCU> vertices, VertexBufferLayout layout)
	{

		float positions[] = {
			//PositionCoords		                                                                    //Color                                                                 //TextureCoords
vertices[0].m_Pos.m_X, vertices[0].m_Pos.m_Y, vertices[0].m_Pos.m_Z,     vertices[0].m_Color.m_X, vertices[0].m_Color.m_Y, vertices[0].m_Color.m_Z, vertices[0].m_Color.m_W,      vertices[0].m_UV.m_X, vertices[0].m_UV.m_Y,  // 0
vertices[1].m_Pos.m_X, vertices[1].m_Pos.m_Y, vertices[1].m_Pos.m_Z,     vertices[1].m_Color.m_X, vertices[1].m_Color.m_Y, vertices[1].m_Color.m_Z, vertices[1].m_Color.m_W,      vertices[1].m_UV.m_X, vertices[1].m_UV.m_Y,  // 1
vertices[2].m_Pos.m_X, vertices[2].m_Pos.m_Y, vertices[2].m_Pos.m_Z,     vertices[2].m_Color.m_X, vertices[2].m_Color.m_Y, vertices[2].m_Color.m_Z, vertices[2].m_Color.m_W,      vertices[2].m_UV.m_X, vertices[2].m_UV.m_Y,  // 2
vertices[3].m_Pos.m_X, vertices[3].m_Pos.m_Y, vertices[3].m_Pos.m_Z,     vertices[3].m_Color.m_X, vertices[3].m_Color.m_Y, vertices[3].m_Color.m_Z, vertices[3].m_Color.m_W,      vertices[3].m_UV.m_X, vertices[3].m_UV.m_Y   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArrayObject();

		m_VBO = new VertexBuffer(positions, 4 * 9 * sizeof(float));

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = new IndexBuffer(indices, 6);
	}

	Mesh::~Mesh()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_VBO;
	}

}