#include "Font.h"

#include <GL/glew.h>

namespace Apex {

	Font::Font(std::string text, float xpos, float ypos, float scale)
	{
		fontMap = {
		{'A', {Vec2(0.073f, 0.700f), {}}}, {'a', {Vec2(0.073f, 0.574f), {}}}, {'0', {Vec2(0.010f, 0.763f), {}}},
		{'B', {Vec2(0.136f, 0.700f), {}}}, {'b', {Vec2(0.136f, 0.574f), {}}}, {'1', {Vec2(0.073f, 0.763f), {}}},
		{'C', {Vec2(0.199f, 0.700f), {}}}, {'c', {Vec2(0.199f, 0.574f), {}}}, {'2', {Vec2(0.136f, 0.763f), {}}},
		{'D', {Vec2(0.262f, 0.700f), {}}}, {'d', {Vec2(0.262f, 0.574f), {}}}, {'3', {Vec2(0.199f, 0.763f), {}}},
		{'E', {Vec2(0.325f, 0.700f), {}}}, {'e', {Vec2(0.325f, 0.574f), {}}}, {'4', {Vec2(0.262f, 0.763f), {}}},
		{'F', {Vec2(0.388f, 0.700f), {}}}, {'f', {Vec2(0.388f, 0.574f), {}}}, {'5', {Vec2(0.325f, 0.763f), {}}},
		{'G', {Vec2(0.451f, 0.700f), {}}}, {'g', {Vec2(0.451f, 0.565f), {}}}, {'6', {Vec2(0.388f, 0.763f), {}}},
		{'H', {Vec2(0.514f, 0.700f), {}}}, {'h', {Vec2(0.514f, 0.574f), {}}}, {'7', {Vec2(0.451f, 0.763f), {}}},
		{'I', {Vec2(0.577f, 0.700f), {}}}, {'i', {Vec2(0.577f, 0.574f), {}}}, {'8', {Vec2(0.514f, 0.763f), {}}},
		{'J', {Vec2(0.640f, 0.700f), {}}}, {'j', {Vec2(0.640f, 0.574f), {}}}, {'9', {Vec2(0.577f, 0.763f), {}}},
		{'K', {Vec2(0.703f, 0.700f), {}}}, {'k', {Vec2(0.703f, 0.574f), {}}}, {' ', {Vec2(0.010f, 0.439f), {}}},
		{'L', {Vec2(0.766f, 0.700f), {}}}, {'l', {Vec2(0.766f, 0.574f), {}}}, {'+', {Vec2(0.703f, 0.826f), {}}},
		{'M', {Vec2(0.826f, 0.700f), {}}}, {'m', {Vec2(0.829f, 0.574f), {}}}, {'-', {Vec2(0.829f, 0.820f), {}}},
		{'N', {Vec2(0.892f, 0.700f), {}}}, {'n', {Vec2(0.892f, 0.574f), {}}}, {'=', {Vec2(0.829f, 0.763f), {}}},
		{'O', {Vec2(0.950f, 0.700f), {}}}, {'o', {Vec2(0.955f, 0.574f), {}}}, {'/', {Vec2(0.950f, 0.826f), {}}},
		{'P', {Vec2(0.010f, 0.637f), {}}}, {'p', {Vec2(0.010f, 0.502f), {}}}, {'>', {Vec2(0.892f, 0.763f), {}}},
		{'Q', {Vec2(0.073f, 0.637f), {}}}, {'q', {Vec2(0.073f, 0.502f), {}}}, {'<', {Vec2(0.766f, 0.763f), {}}},
		{'R', {Vec2(0.136f, 0.637f), {}}}, {'r', {Vec2(0.136f, 0.511f), {}}}, {',', {Vec2(0.766f, 0.817f), {}}},
		{'S', {Vec2(0.199f, 0.637f), {}}}, {'s', {Vec2(0.199f, 0.511f), {}}}, {'.', {Vec2(0.892f, 0.817f), {}}},
		{'T', {Vec2(0.262f, 0.637f), {}}}, {'t', {Vec2(0.262f, 0.511f), {}}}, {'?', {Vec2(0.950f, 0.763f), {}}},
		{'U', {Vec2(0.325f, 0.637f), {}}}, {'u', {Vec2(0.325f, 0.511f), {}}}, {';', {Vec2(0.703f, 0.763f), {}}},
		{'V', {Vec2(0.388f, 0.637f), {}}}, {'v', {Vec2(0.388f, 0.511f), {}}}, {':', {Vec2(0.640f, 0.763f), {}}},
		{'W', {Vec2(0.451f, 0.637f), {}}}, {'w', {Vec2(0.451f, 0.511f), {}}}, {'#', {Vec2(0.199f, 0.826f), {}}},
		{'X', {Vec2(0.514f, 0.637f), {}}}, {'x', {Vec2(0.514f, 0.511f), {}}}, {'@', {Vec2(0.010f, 0.700f), {}}},
		{'Y', {Vec2(0.577f, 0.637f), {}}}, {'y', {Vec2(0.577f, 0.502f), {}}}, {'%', {Vec2(0.323f, 0.826f), {}}},
		{'Z', {Vec2(0.640f, 0.637f), {}}}, {'z', {Vec2(0.640f, 0.511f), {}}}, {'&', {Vec2(0.388f, 0.826f), {}}}
		};

		BuildFont(text, xpos, ypos, scale);
	}
	
	Font::~Font()
	{
	}
	
	void Font::BuildFont(std::string text, float xpos, float ypos, float scale)
	{
		m_Text = text;

		for (auto i : m_Text)
		{
			fontMap[i].quadCoord.push_back(Vec2(xpos, ypos));

			float positions[] = {
				                          //PositionCoords		                                                  //TextureCoords
                0.0f,                 0.0f,                 0.0f,           fontMap[i].texCoord.m_X,         fontMap[i].texCoord.m_Y,          // 0
                0.0f + (25 * scale),  0.0f,                 0.0f,           fontMap[i].texCoord.m_X + 0.04f, fontMap[i].texCoord.m_Y,          // 1
                0.0f + (25 * scale),  0.0f + (25 * scale),  0.0f,           fontMap[i].texCoord.m_X + 0.04f, fontMap[i].texCoord.m_Y + 0.04f,  // 2
                0.0f,                 0.0f + (25 * scale),  0.0f,           fontMap[i].texCoord.m_X,         fontMap[i].texCoord.m_Y + 0.04f   // 3
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			VertexArray* vao = new VertexArray();
			VertexBuffer* vbo = new VertexBuffer(positions, 4 * 5 * sizeof(float));

			VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(2);

			vao->AddBuffer(*vbo, layout);

			m_VAO.push_back(vao);

			m_IBO.push_back(new IndexBuffer(indices, 6));

			xpos += 25.0f * scale;
		}

		for (int i = 0; i < m_Text.size(); i++)
		{
			m_VAO[i]->UnBind();
			m_IBO[i]->UnBind();
		}
	}

	void Font::DrawFontText(Shader shader)
	{
		shader.Bind();

		std::map<char, int> duplicate;

		for (int i = 0; i < m_Text.size(); i++)
		{
			duplicate[m_Text[i]]++;

			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(fontMap[m_Text[i]].quadCoord[duplicate[m_Text[i]] - 1].m_X, fontMap[m_Text[i]].quadCoord[duplicate[m_Text[i]] - 1].m_Y, 0.2f));
			shader.SetUniformMat4f("u_Model", model);

			m_VAO[i]->Bind();
			m_IBO[i]->Bind();
			
			glDrawElements(GL_TRIANGLES, m_IBO[i]->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_VAO[i]->UnBind();
			m_IBO[i]->UnBind();
		}
	}

}