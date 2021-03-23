#include "Player.h"

Player::Player(Apex::Vec3 position, Apex::Shader shader)
	: g_Position(position), g_Shader(shader)
{
	Init();
}

Player::~Player()
{
	delete g_IBO;
	delete g_VBO;
	delete g_VAO;
}

void Player::Init()
{
	g_Model = Apex::Mat4::translation(g_Position) * Apex::Mat4::rotation(g_RotateAngle, Apex::Vec3(0, 0, 1));

	CreateBuffer();
}

void Player::CreateBuffer()
{
	float vertices[] = {
		  0, -10, 0,     1.0f, 1.0f, 1.0f, 1.0f,  //0
		-20, -20, 0, 	 1.0f, 1.0f, 1.0f, 1.0f,  //1
		  0,  20, 0, 	 1.0f, 1.0f, 1.0f, 1.0f,  //2
		 20, -20, 0,	 1.0f, 1.0f, 1.0f, 1.0f	  //3
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

void Player::Bind() const
{
	g_VBO->Bind();
	g_IBO->Bind();
	g_VAO->Bind();
	g_Shader.Bind();
}

void Player::UnBind() const
{
	g_VBO->UnBind();
	g_IBO->UnBind();
	g_VAO->UnBind();
	g_Shader.UnBind();
}
