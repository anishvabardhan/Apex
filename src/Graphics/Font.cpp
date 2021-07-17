#include "Font.h"

#include <GL/glew.h>

#include <map>

namespace Apex {

	std::map<char, Vec4> fontMap = {
		{'A', Vec4(0.073f, 0.700f, 0.0f, 0.0f)}, {'a', Vec4(0.073f, 0.574f, 0.0f, 0.0f)}, {'0', Vec4(0.010f, 0.763f, 0.0f, 0.0f)},
		{'B', Vec4(0.136f, 0.700f, 0.0f, 0.0f)}, {'b', Vec4(0.136f, 0.574f, 0.0f, 0.0f)}, {'1', Vec4(0.073f, 0.763f, 0.0f, 0.0f)},
		{'C', Vec4(0.199f, 0.700f, 0.0f, 0.0f)}, {'c', Vec4(0.199f, 0.574f, 0.0f, 0.0f)}, {'2', Vec4(0.136f, 0.763f, 0.0f, 0.0f)},
		{'D', Vec4(0.262f, 0.700f, 0.0f, 0.0f)}, {'d', Vec4(0.262f, 0.574f, 0.0f, 0.0f)}, {'3', Vec4(0.199f, 0.763f, 0.0f, 0.0f)},
		{'E', Vec4(0.325f, 0.700f, 0.0f, 0.0f)}, {'e', Vec4(0.325f, 0.574f, 0.0f, 0.0f)}, {'4', Vec4(0.262f, 0.763f, 0.0f, 0.0f)},
		{'F', Vec4(0.388f, 0.700f, 0.0f, 0.0f)}, {'f', Vec4(0.388f, 0.574f, 0.0f, 0.0f)}, {'5', Vec4(0.325f, 0.763f, 0.0f, 0.0f)},
		{'G', Vec4(0.451f, 0.700f, 0.0f, 0.0f)}, {'g', Vec4(0.451f, 0.565f, 0.0f, 0.0f)}, {'6', Vec4(0.388f, 0.763f, 0.0f, 0.0f)},
		{'H', Vec4(0.514f, 0.700f, 0.0f, 0.0f)}, {'h', Vec4(0.514f, 0.574f, 0.0f, 0.0f)}, {'7', Vec4(0.451f, 0.763f, 0.0f, 0.0f)},
		{'I', Vec4(0.577f, 0.700f, 0.0f, 0.0f)}, {'i', Vec4(0.577f, 0.574f, 0.0f, 0.0f)}, {'8', Vec4(0.514f, 0.763f, 0.0f, 0.0f)},
		{'J', Vec4(0.640f, 0.700f, 0.0f, 0.0f)}, {'j', Vec4(0.640f, 0.574f, 0.0f, 0.0f)}, {'9', Vec4(0.577f, 0.763f, 0.0f, 0.0f)},
		{'K', Vec4(0.703f, 0.700f, 0.0f, 0.0f)}, {'k', Vec4(0.703f, 0.574f, 0.0f, 0.0f)}, {' ', Vec4(0.010f, 0.439f, 0.0f, 0.0f)},
		{'L', Vec4(0.766f, 0.700f, 0.0f, 0.0f)}, {'l', Vec4(0.766f, 0.574f, 0.0f, 0.0f)}, {'+', Vec4(0.703f, 0.826f, 0.0f, 0.0f)},
		{'M', Vec4(0.829f, 0.700f, 0.0f, 0.0f)}, {'m', Vec4(0.829f, 0.574f, 0.0f, 0.0f)}, {'-', Vec4(0.829f, 0.820f, 0.0f, 0.0f)},
		{'N', Vec4(0.892f, 0.700f, 0.0f, 0.0f)}, {'n', Vec4(0.892f, 0.574f, 0.0f, 0.0f)}, {'=', Vec4(0.829f, 0.763f, 0.0f, 0.0f)},
		{'O', Vec4(0.950f, 0.700f, 0.0f, 0.0f)}, {'o', Vec4(0.955f, 0.574f, 0.0f, 0.0f)}, {'/', Vec4(0.950f, 0.826f, 0.0f, 0.0f)},
		{'P', Vec4(0.010f, 0.637f, 0.0f, 0.0f)}, {'p', Vec4(0.010f, 0.502f, 0.0f, 0.0f)}, {'>', Vec4(0.892f, 0.763f, 0.0f, 0.0f)},
		{'Q', Vec4(0.073f, 0.637f, 0.0f, 0.0f)}, {'q', Vec4(0.073f, 0.502f, 0.0f, 0.0f)}, {'<', Vec4(0.766f, 0.763f, 0.0f, 0.0f)},
		{'R', Vec4(0.136f, 0.637f, 0.0f, 0.0f)}, {'r', Vec4(0.136f, 0.511f, 0.0f, 0.0f)}, {',', Vec4(0.766f, 0.817f, 0.0f, 0.0f)},
		{'S', Vec4(0.199f, 0.637f, 0.0f, 0.0f)}, {'s', Vec4(0.199f, 0.511f, 0.0f, 0.0f)}, {'.', Vec4(0.892f, 0.817f, 0.0f, 0.0f)},
		{'T', Vec4(0.262f, 0.637f, 0.0f, 0.0f)}, {'t', Vec4(0.262f, 0.511f, 0.0f, 0.0f)}, {'?', Vec4(0.950f, 0.763f, 0.0f, 0.0f)},
		{'U', Vec4(0.325f, 0.637f, 0.0f, 0.0f)}, {'u', Vec4(0.325f, 0.511f, 0.0f, 0.0f)}, {';', Vec4(0.703f, 0.763f, 0.0f, 0.0f)},
		{'V', Vec4(0.388f, 0.637f, 0.0f, 0.0f)}, {'v', Vec4(0.388f, 0.511f, 0.0f, 0.0f)}, {':', Vec4(0.640f, 0.763f, 0.0f, 0.0f)},
		{'W', Vec4(0.451f, 0.637f, 0.0f, 0.0f)}, {'w', Vec4(0.451f, 0.511f, 0.0f, 0.0f)}, {'#', Vec4(0.199f, 0.826f, 0.0f, 0.0f)},
		{'X', Vec4(0.514f, 0.637f, 0.0f, 0.0f)}, {'x', Vec4(0.514f, 0.511f, 0.0f, 0.0f)}, {'@', Vec4(0.010f, 0.700f, 0.0f, 0.0f)},
		{'Y', Vec4(0.577f, 0.637f, 0.0f, 0.0f)}, {'y', Vec4(0.577f, 0.502f, 0.0f, 0.0f)}, {'%', Vec4(0.323f, 0.826f, 0.0f, 0.0f)},
		{'Z', Vec4(0.640f, 0.637f, 0.0f, 0.0f)}, {'z', Vec4(0.640f, 0.511f, 0.0f, 0.0f)}, {'&', Vec4(0.388f, 0.826f, 0.0f, 0.0f)}
	};

	Font::Font()
	{
	}
	
	Font::~Font()
	{
	}
	
	void Font::BuildFont(std::string text, float xpos, float ypos, float scale)
	{
		m_Text = text;

		for (auto i : m_Text)
		{
			fontMap[i].m_Z = xpos;
			fontMap[i].m_W = ypos;

			float positions[] = {
				                          //PositionCoords		                                                  //TextureCoords
                0.0f,                 0.0f,                 0.0f,           fontMap[i].m_X,         fontMap[i].m_Y,          // 0
                0.0f + (25 * scale),  0.0f,                 0.0f,           fontMap[i].m_X + 0.04f, fontMap[i].m_Y,          // 1
                0.0f + (25 * scale),  0.0f + (25 * scale),  0.0f,           fontMap[i].m_X + 0.04f, fontMap[i].m_Y + 0.04f,  // 2
                0.0f,                 0.0f + (25 * scale),  0.0f,           fontMap[i].m_X,         fontMap[i].m_Y + 0.04f   // 3
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

		for (int i = 0; i < m_Text.size(); i++)
		{
			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(fontMap[m_Text[i]].m_Z, fontMap[m_Text[i]].m_W, 0.2f));
			shader.SetUniformMat4f("u_Model", model);

			m_VAO[i]->Bind();
			m_IBO[i]->Bind();
			
			glDrawElements(GL_TRIANGLES, m_IBO[i]->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_VAO[i]->UnBind();
			m_IBO[i]->UnBind();
		}
	}

}