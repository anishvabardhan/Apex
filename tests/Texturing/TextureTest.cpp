#include "TextureTest.h"

#include "Graphics/Shader.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/Texture.h"

TextureTest::TextureTest()
{
}

TextureTest::~TextureTest()
{
}

void TextureTest::Init()
{
	if (g_App.Init())
	{
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			float positions[] = {
			   //PositionCoords		 //TextureCoords
				-0.5f, -0.5f,           0.0f, 0.0f,  // 0
				 0.5f, -0.5f,           1.0f, 0.0f,  // 1
				 0.5f,  0.5f,           1.0f, 1.0f,  // 2
				-0.5f,  0.5f,           0.0f, 1.0f   // 3
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			Apex::VertexBuffer vbo(positions, 4 * 4 * sizeof(float));

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)8);

			Apex::IndexBuffer ibo(indices, 6);

			Apex::Shader shader("res/Shaders/Basic.shader");
			shader.Bind();

			Apex::Texture texture("res/Textures/tex.png");
			texture.Bind();
			shader.SetUniform1i("u_Texture", 0);

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();

			while (g_App.IsRun())
			{
				g_App.Broadcast();

				glClear(GL_COLOR_BUFFER_BIT);

				shader.Bind();

				vbo.Bind();
				ibo.Bind();

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				g_App.SwappingBuffers();
			}

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();
		}
	}
}
