#pragma once

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/Shader.h"

#include "Maths/Mat4.h"

class Astroid
{
	Apex::Vec3 g_Position;
	Apex::Mat4 g_Model;

	Apex::VertexBuffer* g_VBO;
	Apex::IndexBuffer* g_IBO;
	Apex::VertexArray* g_VAO;
	Apex::VertexBufferLayout g_Layout;
	Apex::Shader& g_Shader;
public:
	Astroid(Apex::Vec3 position, Apex::Shader& shader)
		:g_Position(position), g_Shader(shader)
	{
		Init();
	};

	~Astroid() 
	{
		delete g_IBO;
		delete g_VAO;
		delete g_VBO;
	}
	
	void Init() 
	{
		CreateBuffer();
	}

	void CreateBuffer()
	{
		float vertices[] = {
			0.0f,  0.0f,  0.0f,        0.5f, 0.5f, 0.5f, 1.0f,   //0
			0.0f,  50.0f, 0.0f,        0.5f, 0.5f, 0.5f, 1.0f,	 //1
			50.0f, 50.0f, 0.0f,        0.5f, 0.5f, 0.5f, 1.0f,	 //2
			50.0f, 0.0f,  0.0f,        0.5f, 0.5f, 0.5f, 1.0f	 //3
		};

		g_VBO = new Apex::VertexBuffer(vertices, sizeof(vertices));

		g_Layout.Push<float>(3);
		g_Layout.Push<float>(4);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		g_IBO = new Apex::IndexBuffer(indices, 6);

		g_VAO = new Apex::VertexArray();

		g_VAO->AddBuffer(*g_VBO, g_Layout);

		g_VBO->Bind();
		g_IBO->Bind();
		g_VAO->Bind();
		g_Shader.Bind();
	}

	void Bind() const
	{
		g_VBO->Bind();
		g_IBO->Bind();
		g_VAO->Bind();
		g_Shader.Bind();
	}
	void UnBind() const
	{
		g_VBO->UnBind();
		g_IBO->UnBind();
		g_VAO->UnBind();
		g_Shader.UnBind();
	}

	inline Apex::Mat4& GetAstroidPosition() { g_Model = Apex::Mat4::translation(g_Position); return g_Model; }

	inline Apex::Vec3 GetPosition() const { return g_Position; }
	inline void SetPosition(Apex::Vec3 position) { g_Position = position; }

	inline Apex::VertexBuffer* GetVBO() const { return g_VBO; }
	inline Apex::IndexBuffer* GetIBO() const { return g_IBO; }
	inline Apex::VertexArray* GetVAO() const { return g_VAO; }
	inline Apex::Shader& GetShader() const { return g_Shader; }
};