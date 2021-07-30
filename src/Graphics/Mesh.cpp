#include "Mesh.h"

namespace Apex {

	Mesh::Mesh(const Vec2& position, Vec2 meshDim, const std::string& path)
	{
		float positions[] = {
			                    //PositionCoords		                      //TextureCoords
        position.m_X,                position.m_Y,                0.0f,           0.0f, 0.0f,  // 0
        position.m_X + meshDim.m_X,  position.m_Y,                0.0f,           4.0f, 0.0f,  // 1
        position.m_X + meshDim.m_X,  position.m_Y + meshDim.m_Y,  0.0f,           4.0f, 4.0f,  // 2
        position.m_X,                position.m_Y + meshDim.m_Y,  0.0f,           0.0f, 4.0f   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		VertexBuffer* vbo = new VertexBuffer(positions, 4 * 5 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push(3);
		layout.Push(2);

		m_VAO->AddBuffer(*vbo, layout);

		m_IBO = new IndexBuffer(indices, 6);

		m_Texture = new Texture(path);
	}

	Mesh::Mesh(const Vec2& position, Vec2 meshDim)
	{
		float positions[] = {
			               //PositionCoords		                        //TextureCoords
        position.m_X,                position.m_Y,                         0.0f, 0.0f,  // 0
        position.m_X + meshDim.m_X,  position.m_Y,                         1.0f, 0.0f,  // 1
        position.m_X + meshDim.m_X,  position.m_Y + meshDim.m_Y,           1.0f, 1.0f,  // 2
        position.m_X,                position.m_Y + meshDim.m_Y,           0.0f, 1.0f   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		VertexBuffer* vbo = new VertexBuffer(positions, 4 * 5 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push(2);
		layout.Push(2);

		m_VAO->AddBuffer(*vbo, layout);

		m_IBO = new IndexBuffer(indices, 6);

		m_Texture = nullptr;
	}
	
	Mesh::~Mesh()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_Texture;
	}

}