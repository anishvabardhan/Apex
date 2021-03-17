#pragma once

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/Shader.h"

#include "Maths/Mat4.h"

class Player
{
	Apex::Vec3 g_Position;
	Apex::Mat4 g_Model;

	Apex::VertexArray* g_VAO;
	Apex::VertexBuffer* g_VBO;
	Apex::IndexBuffer* g_IBO;
	Apex::VertexBufferLayout g_Layout;
	Apex::Shader& g_Shader;
public:
	explicit Player(Apex::Vec3 position, Apex::Shader shader);
	~Player();

	void Init();
	void CreateBuffer();

	void Bind() const;
	void UnBind() const;

	inline Apex::Mat4 GetPlayerPosition() { g_Model = Apex::Mat4::translation(g_Position); return g_Model; }

	inline Apex::Vec3 GetPosition() const { return g_Position; }
	inline void SetPosition(Apex::Vec3 position) { g_Position = position; }

	inline Apex::VertexArray* GetVAO() const { return g_VAO; }
	inline Apex::VertexBuffer* GetVBO() const { return g_VBO; }
	inline Apex::IndexBuffer* GetIBO() const { return g_IBO; }
	inline Apex::VertexBufferLayout GetLayout() const { return g_Layout; }
	inline Apex::Shader& GetShader() const { return g_Shader; }
};