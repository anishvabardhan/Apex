#include "TextureTest.h"

#include "../Graphics/Shader.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/Texture.h"
#include "../Maths/Mat4.h"
#include "../Graphics/Font.h"

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

			Apex::Font font1("OpenGL3", 512.0f, 912.0f, 1.0f);
			Apex::Font font2("19May", 312.0f, 712.0f, 1.0f);
			
			float positions[] = {
			       //PositionCoords		        //TextureCoords
			    312.0f,  312.0f,  0.0f,           0.0f, 0.0f,  // 0
			    712.0f,  312.0f,  0.0f,           1.0f, 0.0f,  // 1
			    712.0f,  712.0f,  0.0f,           1.0f, 1.0f,  // 2
			    312.0f,  712.0f,  0.0f,           0.0f, 1.0f   // 3
			};
			
			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};
			
			Apex::VertexArray* vao = new Apex::VertexArray();
			Apex::VertexBuffer* vbo = new Apex::VertexBuffer(positions, 4 * 5 * sizeof(float));

			Apex::VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(2);

			vao->AddBuffer(*vbo, layout);
			
			Apex::IndexBuffer ibo(indices, 6);
			
			Apex::Texture texture("res/Textures/font.png", NULL);
			texture.Bind();

			Apex::Shader shader("res/Shaders/Basic.shader");
			shader.Bind();

			Apex::Mat4 proj = Apex::Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f);
			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(0.0f, 0.0f, 0.2f));

			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Proj", proj);

			shader.UnBind();
			
			while (g_App.IsRun())
			{
				g_App.Broadcast();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
				shader.Bind();

				font1.DrawFontText(shader);
				font2.DrawFontText(shader);

				shader.SetUniformMat4f("u_Model", model);
				vao->Bind();
				ibo.Bind();

				glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

				vao->UnBind();
				ibo.UnBind();

				g_App.SwappingBuffers();
			}

			
			vao->UnBind();
			ibo.UnBind();
			shader.UnBind();
			
		}
	}
}
