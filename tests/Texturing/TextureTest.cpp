#include "TextureTest.h"

#include "../Graphics/Buffers/VertexArray.h"
#include "../Graphics/Buffers/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Font.h"
#include "../Maths/Maths.h"

TextureTest::TextureTest()
{
}

TextureTest::~TextureTest()
{
	delete g_FrameBuffer;
}

void TextureTest::Init()
{
	if (g_App.Init())
	{
		{			
			// Create the Bitmap Font-----------------------------------------------------------------------

			Apex::Font* font = g_Renderer.CreateBitmapFont("res/Textures/NewFont.png");

			//----------------------------------------------------------------------------------------------
			// Create a quad with a texture attachment------------------------------------------------------

			Apex::Mesh* quad = new Apex::Mesh(Apex::Vec2(312.0f, 312.0f), Apex::Vec2(400.0f, 400.0f), "res/Textures/stripes.png");
			
			//----------------------------------------------------------------------------------------------
            // Create a Screen Quad for the Framebuffer------------------------------------------------------

			Apex::Mesh* screenQuad = new Apex::Mesh(Apex::Vec2(0.0f, 0.0f), Apex::Vec2(1024.0f, 1024.0f));

			//----------------------------------------------------------------------------------------------
            // Create an Orthgraphic Camera-----------------------------------------------------------------

			Apex::Mat4 proj = Apex::Mat4::orthographic(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f);

			//----------------------------------------------------------------------------------------------
            // Create a Basic Shader and Screen Shader for renderables and framebuffer respectively-------

			Apex::Shader shader("res/Shaders/Basic.shader");
			Apex::Shader screenShader("res/Shaders/Screen.shader");

			//----------------------------------------------------------------------------------------------
			// Create the Frambuffer----------------------------------------------------------------------

			g_FrameBuffer = new Apex::FrameBuffer();

			//----------------------------------------------------------------------------------------------
			// GAME LOOP------------------------------------------------------------------------------------

			while (g_App.IsRun())
			{  
				// The Message Loop-------------------------------------------------------------------------
				
				g_App.Broadcast();

				//------------------------------------------------------------------------------------------
				// Bind the FrameBuffer---------------------------------------------------------------------

				g_FrameBuffer->Bind();

				//------------------------------------------------------------------------------------------
				// Bind the Shader--------------------------------------------------------------------------

				shader.Bind();

				//------------------------------------------------------------------------------------------
				// Set the Uniforms-------------------------------------------------------------------------

				shader.SetUniformMat4f("u_Proj", proj);

				//------------------------------------------------------------------------------------------
				// Render the Text--------------------------------------------------------------------------

				g_Renderer.Drawtext(Apex::Vec2(0.0f, 974.0f), "(APEX ENGINE)", 50.0f, font, shader);
				g_Renderer.Drawtext(Apex::Vec2(0.0f, 949.0f), "OpenGL3-Textures", 25.0f, font, shader);

				//------------------------------------------------------------------------------------------
				// Render the Qaud--------------------------------------------------------------------------

				g_Renderer.DrawQuad(quad, shader);

				//------------------------------------------------------------------------------------------
				// UnBind the FrameBuffer-------------------------------------------------------------------

				g_FrameBuffer->UnBind();

				//------------------------------------------------------------------------------------------
				// Bind the Screen Shader-------------------------------------------------------------------

				screenShader.Bind();

				//------------------------------------------------------------------------------------------
				// Bind the Framebuffer Color Attachment----------------------------------------------------

				glBindTexture(GL_TEXTURE_2D, g_FrameBuffer->GetColorAttachmentID());

				//------------------------------------------------------------------------------------------
				// Render the FrameBuffer-------------------------------------------------------------------

				g_Renderer.DrawFrameBuffer(screenQuad);

				//------------------------------------------------------------------------------------------
				// Swap Front and Back Buffer---------------------------------------------------------------

				g_App.SwappingBuffers();
			}

			delete quad;
		}
	}
}
