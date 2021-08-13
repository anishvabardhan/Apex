#include "TextureTest.h"

#include "../Graphics/Buffers/VertexArray.h"
#include "../Graphics/Buffers/IndexBuffer.h"
#include "../Graphics/SpriteAnimation.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Font.h"
#include "../Maths/Maths.h"

TextureTest::TextureTest()
	: g_Time(60)
{
}

TextureTest::~TextureTest()
{
	delete g_CurrentFrameBuffer;
	delete g_NextFrameBuffer;
}

void TextureTest::Init()
{
	if (g_App.Init())
	{
		{
			g_Time.SetSeed();

			// Create the Bitmap Font-----------------------------------------------------------------------

			Apex::Font* font = g_Renderer.CreateBitmapFont("res/Textures/NewFont.png");

			Apex::SpriteSheet* sheet = new Apex::SpriteSheet(*g_Renderer.CreateTexture("res/Textures/bird.png"), 5, 3);
			Apex::SpriteAnimation* animation = new Apex::SpriteAnimation(*sheet, Apex::SPRITEANIMATIONMODE::PLAY_LOOP, 10.0, 0, 14);
			
			//----------------------------------------------------------------------------------------------
			// Create a quad with a texture attachment------------------------------------------------------

			Apex::Mesh* quad = new Apex::Mesh(Apex::Vec2(312.0f, 312.0f), Apex::Vec2(400.0f, 400.0f), Apex::Vec3(1.0f, 1.0f, 1.0f), "res/Textures/stripes.png");

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
			// Create the Frambuffers----------------------------------------------------------------------

			g_CurrentFrameBuffer = new Apex::FrameBuffer();
			g_NextFrameBuffer = new Apex::FrameBuffer();

			//----------------------------------------------------------------------------------------------
			// GAME LOOP------------------------------------------------------------------------------------

			while (g_App.IsRun())
			{  
				// The Message Loop-------------------------------------------------------------------------
				
				g_App.Broadcast();

				g_Time.Update();

				//------------------------------------------------------------------------------------------
				// Bind the Current FrameBuffer-------------------------------------------------------------

				g_CurrentFrameBuffer->Bind();

				g_Renderer.ClearColor();
				g_Renderer.Clear();

				//------------------------------------------------------------------------------------------
				// Bind the Shader--------------------------------------------------------------------------

				shader.Bind();

				//------------------------------------------------------------------------------------------
				// Set the Uniforms-------------------------------------------------------------------------

				shader.SetUniformMat4f("u_Proj", proj);

				//------------------------------------------------------------------------------------------
				// Render the Animated Qaud-----------------------------------------------------------------

				animation->Update(g_Time.GetTimeDelta());

				g_Renderer.DrawQuad(Apex::Vec2(25.0f, 25.0f), Apex::Vec2(100.0f, 100.0f), *animation->GetTexture(), Apex::AABB2(animation->GetTexCoords().m_Mins, animation->GetTexCoords().m_Maxs), Apex::Vec4(1.0f, 1.0f, 1.0f, 1.0f), shader);

				//------------------------------------------------------------------------------------------
				// Render the Text--------------------------------------------------------------------------

				g_Renderer.Drawtext(Apex::Vec2(0.0f, 974.0f), "APEX ENGINE", 50.0f, font, shader);
				g_Renderer.Drawtext(Apex::Vec2(0.0f, 949.0f), "OpenGL3-Textures", 25.0f, font, shader);

				//------------------------------------------------------------------------------------------
				// Render the Qaud--------------------------------------------------------------------------

				g_Renderer.DrawQuad(quad, shader);

				//------------------------------------------------------------------------------------------
				// UnBind the Current FrameBuffer-----------------------------------------------------------

				g_CurrentFrameBuffer->UnBind();
				
				g_Renderer.ClearColor();
				g_Renderer.Clear();

				//------------------------------------------------------------------------------------------
				// Bind the Screen Shader-------------------------------------------------------------------

				screenShader.Bind();

				//------------------------------------------------------------------------------------------
				// Copy from Current to Destination Framebuffer---------------------------------------------

				g_Renderer.CopyFrameBuffer(g_CurrentFrameBuffer, g_NextFrameBuffer);
				
				g_Renderer.DrawFrameBuffer(screenQuad);

				//------------------------------------------------------------------------------------------
				// Swap Front and Back Buffer---------------------------------------------------------------

				g_App.SwappingBuffers();
			}

			delete quad;
		}
	}
}
