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
			Apex::FrameBufferSpecification fbSpec;
			fbSpec.s_Width = 1024;
			fbSpec.s_Height = 1024;
			g_FrameBuffer = new Apex::FrameBuffer(fbSpec);

			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

			float positions[] = {
			       //PositionCoords		        //TextureCoords
			    412.0f,  412.0f,  0.0f,           0.0f, 0.0f,  // 0
			    612.0f,  412.0f,  0.0f,           1.0f, 0.0f,  // 1
			    612.0f,  612.0f,  0.0f,           1.0f, 1.0f,  // 2
			    412.0f,  612.0f,  0.0f,           0.0f, 1.0f   // 3
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

			Apex::Mat4 proj = Apex::Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -1.0f, 1.0f);
			Apex::Mat4 model = Apex::Mat4::translation(Apex::Vec3(0.0f, 0.0f, 0.2f));

			Apex::Shader shader("res/Shaders/Basic.shader");
			shader.Bind();
			
			Apex::Texture texture("res/Textures/font.png", g_FrameBuffer->GetColorAttachmentRendererID());
			texture.Bind();

			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Model", model);
			shader.SetUniformMat4f("u_Proj", proj);

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();

			while (g_App.IsRun())
			{
				g_App.Broadcast();

				g_FrameBuffer->Bind();

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				vbo.Bind();
				ibo.Bind();
				shader.Bind();

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

				g_FrameBuffer->UnBind();
				g_App.SwappingBuffers();
			}

			vbo.UnBind();
			ibo.UnBind();
			shader.UnBind();
		}
	}
}
