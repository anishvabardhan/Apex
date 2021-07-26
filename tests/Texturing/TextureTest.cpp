#include "TextureTest.h"

#include "../Graphics/Shader.h"
#include "../Graphics/BUffers/IndexBuffer.h"
#include "../Graphics/BUffers/VertexArray.h"
#include "../Graphics/Texture.h"
#include "../Maths/Mat4.h"
#include "../Graphics/BitMapFont.h"
#include "../Core/StringUtils.h"

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
			
			Apex::BitMapFont* font = g_Renderer.CreateOrGetBitmapFont("SquirrelFixedFont");

			float positions[] = {
			       //PositionCoords		        //TextureCoords
			    312.0f,  312.0f,  0.0f,           0.0f, 0.0f,  // 0
			    712.0f,  312.0f,  0.0f,           2.0f, 0.0f,  // 1
			    712.0f,  712.0f,  0.0f,           2.0f, 2.0f,  // 2
			    312.0f,  712.0f,  0.0f,           0.0f, 2.0f   // 3
			};
			
			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			Apex::VertexArray* vao = new Apex::VertexArray();
			Apex::VertexBuffer vbo(positions, 4 * 5 * sizeof(float));
			
			Apex::VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(2);
			
			vao->AddBuffer(vbo, layout);
			
			Apex::IndexBuffer ibo(indices, 6);
			
			Apex::Mat4 proj = Apex::Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f);
			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(0.0f, 0.0f, 0.2f));

			Apex::Texture texture("res/Textures/stripes.png");

			Apex::Shader shader("res/Shaders/Basic.shader");
			shader.Bind();

			shader.SetUniformMat4f("u_Proj", proj);

			shader.UnBind();
			
			while (g_App.IsRun())
			{
				g_App.Broadcast();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
				shader.Bind();

				g_Renderer.Drawtext2D(Apex::Vec2(375.0f, 900.0f), "Apex Engine", 25.0f, font, 1.0f, shader);

				texture.Bind(Apex::TEXTURESLOT::SLOT1);
				shader.SetUniform1i("u_Texture", 1);
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
