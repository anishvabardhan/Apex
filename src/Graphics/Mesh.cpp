#include "Mesh.h"

#include "../Core/LogMessage.h"

namespace Apex {

	Mesh::Mesh(const Vec2& position, Vec2 meshDim, Vec3 color, const std::string& path)
	{
		float positions[] = {
			//PositionCoords		                                         //Color                  //TextureCoords
            position.m_X,                position.m_Y,                0.0f,     color.m_X, color.m_Y, color.m_Z, 1.0f,      0.0f, 0.0f,  // 0
            position.m_X + meshDim.m_X,  position.m_Y,                0.0f,     color.m_X, color.m_Y, color.m_Z, 1.0f,      1.0f, 0.0f,  // 1
            position.m_X + meshDim.m_X,  position.m_Y + meshDim.m_Y,  0.0f,     color.m_X, color.m_Y, color.m_Z, 1.0f,      1.0f, 1.0f,  // 2
            position.m_X,                position.m_Y + meshDim.m_Y,  0.0f,     color.m_X, color.m_Y, color.m_Z, 1.0f,      0.0f, 1.0f   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		LOG_CHECK(m_VAO != nullptr) << "Data is null";

		m_VBO = new VertexBuffer(positions, 4 * 9 * sizeof(float));
		LOG_CHECK(m_VBO != nullptr) << "Data is null";

		VertexBufferLayout layout;
		layout.Push(3);
		layout.Push(4);
		layout.Push(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = new IndexBuffer(indices, 6);
		LOG_CHECK(m_IBO != nullptr) << "Data is null";

		m_Texture = new Texture(path);
		LOG_CHECK(m_Texture != nullptr) << "Data is null";
	}

	Mesh::Mesh(const Vec2& position, const Vec2& meshDim, const Vec4& color, const AABB2& uvPos)
	{
		float positions[] = {
			//PositionCoords		                                             //Color                                    //TextureCoords
            position.m_X,                position.m_Y,                0.0f,     color.m_X, color.m_Y, color.m_Z, color.m_W,      uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y,  // 0
            position.m_X + meshDim.m_X,  position.m_Y,                0.0f,     color.m_X, color.m_Y, color.m_Z, color.m_W,      uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y,  // 1
            position.m_X + meshDim.m_X,  position.m_Y + meshDim.m_Y,  0.0f,     color.m_X, color.m_Y, color.m_Z, color.m_W,      uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y,  // 2
            position.m_X,                position.m_Y + meshDim.m_Y,  0.0f,     color.m_X, color.m_Y, color.m_Z, color.m_W,      uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		LOG_CHECK(m_VAO != nullptr) << "Data is null";

		m_VBO = new VertexBuffer(positions, 4 * 9 * sizeof(float));
		LOG_CHECK(m_VBO != nullptr) << "Data is null";

		VertexBufferLayout layout;
		layout.Push(3);
		layout.Push(4);
		layout.Push(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = new IndexBuffer(indices, 6);
		LOG_CHECK(m_IBO != nullptr) << "Data is null";

		m_Texture = nullptr;
	}

	Mesh::Mesh(const Vec2& position, Vec2 meshDim)
	{
		float positions[] = {
			//PositionCoords		                              //Color               //TextureCoords
            position.m_X,                position.m_Y,                 1.0f, 1.0f, 1.0f, 1.0f,        0.0f, 0.0f,  // 0
            position.m_X + meshDim.m_X,  position.m_Y,                 1.0f, 1.0f, 1.0f, 1.0f,        1.0f, 0.0f,  // 1
            position.m_X + meshDim.m_X,  position.m_Y + meshDim.m_Y,   1.0f, 1.0f, 1.0f, 1.0f,        1.0f, 1.0f,  // 2
            position.m_X,                position.m_Y + meshDim.m_Y,   1.0f, 1.0f, 1.0f, 1.0f,        0.0f, 1.0f   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		LOG_CHECK(m_VAO != nullptr) << "Data is null";

		m_VBO = new VertexBuffer(positions, 4 * 8 * sizeof(float));
		LOG_CHECK(m_VBO != nullptr) << "Data is null";

		VertexBufferLayout layout;
		layout.Push(2);
		layout.Push(4);
		layout.Push(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = new IndexBuffer(indices, 6);
		LOG_CHECK(m_IBO != nullptr) << "Data is null";

		m_Texture = nullptr;
	}

	Mesh::Mesh(const AABB2& position, AABB2 uvPos)
	{
		float positions[] = {
			//PositionCoords		                   //Color                           //TextureCoords
            position.m_Mins.m_X,  position.m_Mins.m_Y, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,        uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y,  // 0
            position.m_Maxs.m_X,  position.m_Mins.m_Y, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,        uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y,  // 1
            position.m_Maxs.m_X,  position.m_Maxs.m_Y, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,        uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y,  // 2
            position.m_Mins.m_X,  position.m_Maxs.m_Y, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,        uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y   // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = new VertexArray();
		LOG_CHECK(m_VAO != nullptr) << "Data is null";

		m_VBO = new VertexBuffer(positions, 4 * 9 * sizeof(float));
		LOG_CHECK(m_VBO != nullptr) << "Data is null";

		VertexBufferLayout layout;
		layout.Push(3);
		layout.Push(4);
		layout.Push(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = new IndexBuffer(indices, 6);
		LOG_CHECK(m_IBO != nullptr) << "Data is null";

		m_Texture = nullptr;
	}

	Mesh::~Mesh()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_VBO;

		if (m_Texture != nullptr)
			delete m_Texture;
	}

}