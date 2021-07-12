#include "TextureTest.h"

#include "../Graphics/Shader.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Texture.h"
#include "../Maths/Mat4.h"
#include "../Graphics/Text.h"

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
			FT_Library library;

			if (FT_Init_FreeType(&library))
			{
				std::cout << "Error Occurred!" << std::endl;
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			Apex::Text text(48);

			float positions[] = {
			       //PositionCoords		        //TextureCoords
			    412.5f,  412.5f,  0.0f,           0.0f, 0.0f,  // 0
			    612.5f,  412.5f,  0.0f,           2.0f, 0.0f,  // 1
			    612.5f,  612.5f,  0.0f,           2.0f, 2.0f,  // 2
			    412.5f,  612.5f,  0.0f,           0.0f, 2.0f   // 3
			};
			
			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};
			
			Apex::VertexBuffer vbo(positions, 4 * 5 * sizeof(float));
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)12);
			
			Apex::IndexBuffer ibo(indices, 6);


			if (!text.LoadFont(library, "res/Fonts/arial.ttf"))
			{
				std::cout << "ERROR!" << std::endl;
			}

			Apex::Mat4 proj = Apex::Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -1.0f, 1.0f);
			//Apex::Mat4 proj = Apex::Mat4::perspective(60.0f, 1024.0f / 1024.0f, 0.1f, 100.0f);
			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(0.0f, 0.0f, 0.2f));

			Apex::Shader shader("res/Shaders/Basic.shader");
			shader.Bind();
			
			Apex::Texture texture("res/Textures/stripes.png");
			texture.Bind();

			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Model", model);
			shader.SetUniformMat4f("u_Proj", proj);

			Apex::Shader shader2("res/Shaders/Text.shader");
			shader2.Bind();

			shader2.SetUniform1i("u_Text", 1);
			shader2.SetUniformMat4f("u_Projection", proj);
			shader2.SetUniform4f("u_TextColor", 0.5f, 0.5f, 0.5f, 1.0f);

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();
			shader2.UnBind();

			while (g_App.IsRun())
			{
				g_App.Broadcast();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				vbo.Bind();
				ibo.Bind();
				shader.Bind();

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				shader2.Bind();

				text.RenderText("OpenGL3-Textures", 0.0f, 976.0f, Apex::Vec2(1.0f, 1.0f));

				g_App.SwappingBuffers();
			}

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();
			shader2.UnBind();
		}
	}
}
