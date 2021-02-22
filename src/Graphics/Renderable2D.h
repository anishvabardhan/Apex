#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include "Maths/Maths.h"

namespace Apex {

	class Renderable2D
	{
	protected:
// Member Variables-------------------------------------------------------------------------------------

		Vec3 m_Position;
		Vec2 m_Size;

		Mat4 m_Model;
		
		VertexArray* m_VAO;
		IndexBuffer* m_IBO;
		VertexBuffer* m_VBO;
		VertexBufferLayout layout;
		Shader& m_Shader;
	public:

// Constructor and Destructor---------------------------------------------------------------------------

		explicit Renderable2D(Vec3 position, Vec2 size, Shader& shader)
			: m_Position(position), m_Size(size), m_Shader(shader)
		{
			CreateVBO();
			CreateIBO();
			CreateVAO();

			Bind();
		}

		~Renderable2D()
		{
			delete m_VAO;
			delete m_IBO;
			delete m_VBO;
		}

//-------------------------------------------------------------------------------------------------------
// Creating Vertex Buffers-------------------------------------------------------------------------------

		void CreateVBO()
		{
			float vertices[] = {
				0, 0, 0,
				0, m_Size.m_Y, 0,
				m_Size.m_X, m_Size.m_Y, 0,
				m_Size.m_X, 0, 0
			};

			m_VBO = new VertexBuffer(vertices, 4 * 3 * sizeof(float));

			layout.Push<float>(3);
		}

// Creating Index Buffers--------------------------------------------------------------------------------

		void CreateIBO()
		{

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			m_IBO = new IndexBuffer(indices, 6);
		}

// Creating Vertex Arrays--------------------------------------------------------------------------------

		void CreateVAO()
		{
			m_VAO = new VertexArray();

			m_VAO->AddBuffer(*m_VBO, layout);
		}

// Binding the Buffers and shaders-----------------------------------------------------------------------

		void Bind()
		{
			m_VBO->Bind();
			m_VAO->Bind();
			m_IBO->Bind();
			m_Shader.Bind();
		}

// UnBinding the Buffers and shaders---------------------------------------------------------------------

		void UnBind()
		{
			m_VBO->UnBind();
			m_VAO->UnBind();
			m_IBO->UnBind();
			m_Shader.UnBind();
		}

// Creating Getter Methods-------------------------------------------------------------------------------

		inline const VertexArray* GetVAO() const { return m_VAO; }
		inline const VertexBuffer* GetVBO() const { return m_VBO; }
		inline const IndexBuffer* GetIBO() const { return m_IBO; }
		inline Shader& GetShader() const { return m_Shader; }

		inline const Vec3& GetPosition() const { return m_Position; }
		inline const Vec2& GetSize() const { return m_Size; }

		inline const Mat4& GetModel() { m_Model = Mat4::translation(m_Position); return m_Model; }

// Creating Setter Methods-------------------------------------------------------------------------------

		inline void SetPosition(Vec3 position) { m_Position = position; }
		inline void SetSize(Vec2 size) { m_Size = size; }
	};

}