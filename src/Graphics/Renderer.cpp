#include "Renderer.h"

#include <GL/glew.h>

namespace Apex {

	Renderer::Renderer()
	{
		glViewport(0, 0, 1024, 1024);
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

	void Renderer::Drawtext(const Vec2& position, const std::string& asciiText, float quadHeight, Font* font, Shader shader)
	{
		font->GetSpriteSheet().GetSpriteSheetTexture().Bind(TEXTURESLOT::SLOT0);

		float cellWidth = quadHeight;
		
		AABB2 quadPos;
		AABB2 uvPos;
		
		quadPos.m_Mins.m_Y = position.m_Y;
		quadPos.m_Maxs.m_Y = position.m_Y + quadHeight;

		for (size_t i = 0; i < asciiText.size(); i++)
		{
			quadPos.m_Mins.m_X = (i * cellWidth) + position.m_X;
			quadPos.m_Maxs.m_X = ((i + 1) * cellWidth) + position.m_X;

			uvPos = font->GetGlyphUV(asciiText[i]);

			float positions[] = {
				               //PositionCoords		                        //TextureCoords
				quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f,       uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y,
				quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f,       uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y,
				quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f,	    uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y,
				quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f,       uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			VertexArray* vao = new VertexArray();

			VertexBuffer* vbo = new VertexBuffer(positions, 4 * 5 * sizeof(float));

			VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(2);

			vao->AddBuffer(*vbo, layout);

			IndexBuffer* ibo = new IndexBuffer(indices, 6);

			Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Model", model);

			vao->Bind();
			ibo->Bind();

			glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);

			ibo->UnBind();
			vao->UnBind();

			delete vbo;
			delete ibo;
			delete vao;
		}
	}

	void Renderer::DrawQuad(Mesh* mesh, Shader shader)
	{
		Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));

		mesh->GetTexture()->Bind(TEXTURESLOT::SLOT1);

		shader.SetUniform1i("u_Texture", 1);
		shader.SetUniformMat4f("u_Model", model);

		mesh->GetVAO()->Bind();
		mesh->GetIBO()->Bind();

		glDrawElements(GL_TRIANGLES, mesh->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->GetIBO()->UnBind();
		mesh->GetVAO()->UnBind();
	}

	void Renderer::DrawFrameBuffer(Mesh* mesh)
	{
		mesh->GetVAO()->Bind();
		mesh->GetIBO()->Bind();

		glDrawElements(GL_TRIANGLES, mesh->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->GetIBO()->UnBind();
		mesh->GetVAO()->UnBind();
	}

	Font* Renderer::CreateBitmapFont(const std::string& path)
	{
		Texture* texture = new Texture(path);

		SpriteSheet* bitMapsheet = new SpriteSheet(*texture, 16, 16);
		Font* newFont = new Font(*bitMapsheet);
		return newFont;
	}

}