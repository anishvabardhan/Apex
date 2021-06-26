#include "TextureTest.h"

#include "stb_image.h"

int width, height, bpp;
static GLuint texName;

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

			glShadeModel(GL_FLAT);
			glEnable(GL_DEPTH_TEST);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			stbi_set_flip_vertically_on_load(1);

			GLubyte* texImage;

			texImage = stbi_load("tests/Texturing/Images/cimg.png", &width, &height, &bpp, 4);

			glGenTextures(1, &texName);
			glBindTexture(GL_TEXTURE_2D, texName);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
			glBindTexture(GL_TEXTURE_2D, 0);

			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

			g_Renderer->Push();

			glBindTexture(GL_TEXTURE_2D, texName);

			Apex::Renderer::BeginQuads();

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(100.0f, 100.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(924.0f, 100.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(924.0f, 668.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(100.0f, 668.0f, 0.0f);

			Apex::Renderer::End();

			g_Renderer->Pop();

			g_Renderer->Flush();

			glDisable(GL_TEXTURE_2D);

			g_App.SwappingBuffers();
		}
	}
}
