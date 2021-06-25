#include "TextureTest.h"

#include <Windows.h>
#include <GL/GL.h>

TextureTest::TextureTest()
	: g_Renderer(nullptr)
{
}

TextureTest::~TextureTest()
{
	delete g_Renderer;
}

void TextureTest::Init()
{
	if (g_App.Init())
	{
		while (g_App.IsRun())
		{
			g_App.Broadcast();

			g_Renderer->InitRender();

			g_Renderer->Push();

			Apex::Renderer::BeginQuads();

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f( 20.0f,  20.0f, 0.0f);
			glVertex3f(820.0f,  20.0f, 0.0f);
			glVertex3f(820.0f, 620.0f, 0.0f);
			glVertex3f( 20.0f, 620.0f, 0.0f);

			Apex::Renderer::End();

			g_Renderer->Pop();

			g_Renderer->Flush();

			g_App.SwappingBuffers();
		}
	}
}
