#pragma once

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/Shader.h"

class Astroid
{
	Apex::Vec3 g_Position;

	Apex::VertexBuffer* g_VBO;
	Apex::IndexBuffer* g_IBO;
	Apex::VertexArray* g_VAO;
	Apex::VertexBufferLayout* g_Layout;
	Apex::Shader g_Shader;
public:
	Astroid(Apex::Vec3 position)
		:g_Position(position)
	{
		Init();
	};

	~Astroid() {}
	
	void Init() 
	{
		CreateBuffer();
	}

	void CreateBuffer()
	{
		float vertices[] = {
			0.0f,  0.0f,  0.0f,        0.5f, 0.5f, 0.5f, 1.0f,
			0.0f,  20.0f, 0.0f,        0.5f, 0.5f, 0.5f, 1.0f,
			20.0f, 20.0f, 0.0f,        0.5f, 0.5f, 0.5f, 1.0f,
			20.0f, 0.0f,  0.0f,        0.5f, 0.5f, 0.5f, 1.0f
		};

		g_VBO = new Apex::VertexBuffer(vertices, sizeof(vertices));

		g_Layout->Push<float>(3);
		g_Layout->Push<float>(4);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		g_IBO = new Apex::IndexBuffer(indices, 6);

		g_VAO = new Apex::VertexArray();

		g_VAO->AddBuffer(*g_VBO, *g_Layout);

		g_VBO->Bind();
		g_IBO->Bind();
		g_VAO->Bind();
	}

	void Bind()
	{
		g_VBO->Bind();
		g_IBO->Bind();
		g_VAO->Bind();
	}
	void UnBind()
	{
		g_VBO->UnBind();
		g_IBO->UnBind();
		g_VAO->UnBind();
	}

	Apex::Vec3 GetAstroidPosition() const { return g_Position; }
	void SetAstroidPosition(Apex::Vec3 position) { g_Position = position; }
};