#include "Renderer.h"

#include "Buffers/IndexBuffer.h"
#include "Shader.h"
#include "Buffers/VertexArray.h"
#include "BitMapFont.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "../Core/StringUtils.h"

namespace Apex {

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::InitRender()
	{

		//--------------------------------------------------------------------------------------------------
		//Setup OpenGL3 Viewport----------------------------------------------------------------------------
		
		glViewport(0, 0, 1024, 1024);

		//--------------------------------------------------------------------------------------------------
        //Set Matrix Mode to Projection Matrix-----------------------------------------------------------
		
		glMatrixMode(GL_PROJECTION);

		//--------------------------------------------------------------------------------------------------
		//Set Current Matrix as Identity Matrix-------------------------------------------------------------

		glLoadIdentity();

		//--------------------------------------------------------------------------------------------------
		//Multiply Orthographic Matrix to Current Matrix----------------------------------------------------

		glOrtho(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f);

		//--------------------------------------------------------------------------------------------------
		//Set Matrix Mode to ModelView Matrix---------------------------------------------------------------

		glMatrixMode(GL_MODELVIEW);

		//--------------------------------------------------------------------------------------------------
		//Set Current Matrix as Identity Matrix-------------------------------------------------------------

		glLoadIdentity();

		//--------------------------------------------------------------------------------------------------
		//Clear Buffers to Preset Values--------------------------------------------------------------------

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		//--------------------------------------------------------------------------------------------------
		//Specify Clear Values for the Color Buffers--------------------------------------------------------

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Renderer::BeginLineLoop()
	{
		glBegin(GL_LINE_LOOP);
	}

	void Renderer::BeginLineStrip()
	{
		glBegin(GL_LINE_STRIP);
	}

	void Renderer::BeginPolygon()
	{
		glBegin(GL_POLYGON);
	}

	void Renderer::BeginQuads()
	{
		glBegin(GL_QUADS);
	}

	void Renderer::End()
	{
		glEnd();
	}

	void Renderer::Flush()
	{
		glFlush();
	}

	void Renderer::Push()
	{
		glPushMatrix();
	}

	void Renderer::Pop()
	{
		glPopMatrix();
	}

	void Renderer::Drawtext2D(const Vec2& drawMins, const std::string& asciiText, float cellHeight, const BitMapFont* font, float aspectScale, Shader shader)
	{
		font->m_spriteSheet.GetSpriteSheetTexture().Bind(Apex::TEXTURESLOT::SLOT0);
		float cellWidth = cellHeight * (font->m_baseAspect * aspectScale);
		Vec2 drawMaxs = Vec2(drawMins.m_X + cellWidth, drawMins.m_Y + cellHeight);
		float cursorMins;
		float cursorMaxs;
		float lineMins = drawMins.m_Y;
		float lineMaxs = drawMaxs.m_Y;

		VertexArray* vao = new VertexArray();

		for (size_t i = 0; i < asciiText.size(); ++i)
		{
			cursorMins = ((float)i * cellWidth) + drawMins.m_X;
			cursorMaxs = ((float)(i + 1) * cellWidth) + drawMins.m_X;
			AABB2 uv = font->GetUVsForGlyph(asciiText[i]);

			float positions[] = {
				     //PositionCoords		              //TextureCoords
				cursorMins, lineMins, 0.0f,       uv.m_Mins.m_X, uv.m_Maxs.m_Y,
				cursorMaxs, lineMins, 0.0f,       uv.m_Maxs.m_X, uv.m_Maxs.m_Y,
				cursorMaxs, lineMaxs, 0.0f,		  uv.m_Maxs.m_X, uv.m_Mins.m_Y,
				cursorMins, lineMaxs, 0.0f,       uv.m_Mins.m_X, uv.m_Mins.m_Y
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			VertexBuffer vbo(positions, 4 * 5 * sizeof(float));

			VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(2);

			vao->AddBuffer(vbo, layout);

			Apex::IndexBuffer ibo(indices, 6);

			Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Model", model);

			vao->Bind();
			ibo.Bind();

			glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

			ibo.UnBind();
			vao->UnBind();
		}
	}

	Texture* Renderer::CreateOrGetTexture(const std::string& path)
	{
		if (m_loadedTextures.find(path) != m_loadedTextures.end())
		{
			return m_loadedTextures.at(path);
		}
		else
		{
			Texture* newTexture = new Texture(path);
			m_loadedTextures[path] = newTexture;
			return newTexture;
		}
	}

	BitMapFont* Renderer::CreateOrGetBitmapFont(const char* bitmapFontName)
	{
		std::string path = StringUtils::Stringf("res/Textures/SquirrelFixedFont.png", bitmapFontName);
		std::map<std::string, BitMapFont*>::iterator found = m_loadedFonts.find(bitmapFontName);
		if (found != m_loadedFonts.end())
		{
			return found->second;
		}
		else
		{
			SpriteSheet* bitMapsheet = new SpriteSheet(*CreateOrGetTexture(path), 16, 16);
			BitMapFont* newFont = new BitMapFont(bitmapFontName, *bitMapsheet, 1.0f);
			m_loadedFonts[bitmapFontName] = newFont;
			return newFont;
		}
	}

}