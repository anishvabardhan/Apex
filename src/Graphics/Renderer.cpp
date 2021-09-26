#include "Renderer.h"

#include "../Core/LogMessage.h"

#include <GL/glew.h>

namespace Apex {

	static Renderer* m_Renderer = nullptr;

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
		//Setup OpenGL3 Viewport
		
		glViewport(0, 0, 1024, 1024);

		//--------------------------------------------------------------------------------------------------
        //Set Matrix Mode to Projection Matrix
		
		glMatrixMode(GL_PROJECTION);

		//--------------------------------------------------------------------------------------------------
		//Set Current Matrix as Identity Matrix

		glLoadIdentity();

		//--------------------------------------------------------------------------------------------------
		//Multiply Orthographic Matrix to Current Matrix

		glOrtho(0.0f, 1024.0f, 0.0f, 1024.0f, -2.0f, 2.0f);

		//--------------------------------------------------------------------------------------------------
		//Set Matrix Mode to ModelView Matrix

		glMatrixMode(GL_MODELVIEW);

		//--------------------------------------------------------------------------------------------------
		//Set Current Matrix as Identity Matrix

		glLoadIdentity();

		//--------------------------------------------------------------------------------------------------
		//Clear Buffers to Preset Values

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		//--------------------------------------------------------------------------------------------------
		//Specify Clear Values for the Color Buffers

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

	Renderer* Renderer::GetInstance()
	{
		return m_Renderer;
	}

	void Renderer::EnableBlend(enum APEX_BLEND_FACTOR src, enum APEX_BLEND_FACTOR dest, enum APEX_BLEND_OP mode)
	{
		glEnable(GL_BLEND);

		glBlendFunc(src, dest);

		glBlendEquation(mode);
	}

	void Renderer::DisableBlend()
	{
		glDisable(GL_BLEND);
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

	void Renderer::DrawMesh(const Vec2& position, const std::string& asciiText, float quadHeight, Font* font, Shader shader)
	{
		font->GetSpriteSheet().GetSpriteSheetTexture().Bind(TEXTURESLOT::SLOT0);

		float quadWidth = quadHeight;
		
		AABB2 quadPos;
		AABB2 uvPos;
		
		quadPos.m_Mins.m_Y = position.m_Y;
		quadPos.m_Maxs.m_Y = position.m_Y + quadHeight;

		for (size_t i = 0; i < asciiText.size(); i++)
		{
			quadPos.m_Mins.m_X = (i * quadWidth) + position.m_X;
			quadPos.m_Maxs.m_X = ((i + 1) * quadWidth) + position.m_X;

			uvPos = font->GetGlyphUV(asciiText[i]);

			float positions[] = {
				               //PositionCoords		                      //Color                    //TextureCoords
				quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,    uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y,
				quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,    uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y,
				quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,    uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y,
				quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,    uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			VertexArray* vao = new VertexArray();
			LOG_CHECK(vao != nullptr) << "Data is null";

			VertexBuffer* vbo = new VertexBuffer(positions, 4 * 9 * sizeof(float));
			LOG_CHECK(vbo != nullptr) << "Data is null";

			VertexBufferLayout layout;
			layout.Push(3);
			layout.Push(4);
			layout.Push(2);

			vao->AddBuffer(*vbo, layout);

			IndexBuffer* ibo = new IndexBuffer(indices, 6);
			LOG_CHECK(vbo != nullptr) << "Data is null";

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

	void Renderer::DrawMesh(const Vec2& position, const Vec2& dimensions, const Texture& texture, const AABB2& texCoords, const Vec4& color, Shader shader)
	{
		texture.Bind(TEXTURESLOT::SLOT2);

		float positions[] = {
			                     //PositionCoords		                                             //Color                                   //TextureCoords
            position.m_X,                  position.m_Y, 0.0f,                    color.m_X, color.m_Y, color.m_Z, color.m_W,    texCoords.m_Mins.m_X, texCoords.m_Maxs.m_Y,
            position.m_X + dimensions.m_X, position.m_Y, 0.0f,                    color.m_X, color.m_Y, color.m_Z, color.m_W,    texCoords.m_Maxs.m_X, texCoords.m_Maxs.m_Y,
            position.m_X + dimensions.m_X, position.m_Y + dimensions.m_Y, 0.0f,	  color.m_X, color.m_Y, color.m_Z, color.m_W,    texCoords.m_Maxs.m_X, texCoords.m_Mins.m_Y,
            position.m_X,                  position.m_Y + dimensions.m_Y, 0.0f,   color.m_X, color.m_Y, color.m_Z, color.m_W,    texCoords.m_Mins.m_X, texCoords.m_Mins.m_Y
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexArray* vao = new VertexArray();
		LOG_CHECK(vao != nullptr) << "Data is null";

		VertexBuffer* vbo = new VertexBuffer(positions, 4 * 9 * sizeof(float));
		LOG_CHECK(vbo != nullptr) << "Data is null";

		VertexBufferLayout layout;
		layout.Push(3);
		layout.Push(4);
		layout.Push(2);

		vao->AddBuffer(*vbo, layout);

		IndexBuffer* ibo = new IndexBuffer(indices, 6);
		LOG_CHECK(ibo != nullptr) << "Data is null";

		Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
		shader.SetUniform1i("u_Texture", 2);
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

	void Renderer::DrawMesh(Mesh* mesh, Shader shader)
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

	void Renderer::DrawMesh(Mesh* mesh)
	{
		mesh->GetVAO()->Bind();
		mesh->GetIBO()->Bind();

		glDrawElements(GL_TRIANGLES, mesh->GetIBO()->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->GetIBO()->UnBind();
		mesh->GetVAO()->UnBind();
	}

	void Renderer::CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next)
	{
		glBindTexture(GL_TEXTURE_2D, current->GetColorAttachmentID());
		glBindTexture(GL_TEXTURE_2D, next->GetColorAttachmentID());

		glBindFramebuffer(GL_READ_FRAMEBUFFER, current->GetFrameBufferID());

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, next->GetFrameBufferID());

		glBlitFramebuffer(0, 0, 1024, 1024, 0, 0, 1024, 1024, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::ClearColor() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Font* Renderer::GetOrCreateFont(const std::string& path)
	{
		if (m_LoadedFonts.find(path) != m_LoadedFonts.end())
		{
			return m_LoadedFonts[path];
		}
		else
		{
			Texture* texture = new Texture(path);
			LOG_CHECK(texture != nullptr) << "Data is null";

			SpriteSheet* bitMapsheet = new SpriteSheet(*texture, 16, 16);
			LOG_CHECK(bitMapsheet != nullptr) << "Data is null";

			Font* font = new Font(*bitMapsheet);
			LOG_CHECK(font != nullptr) << "Data is null";

			m_LoadedFonts[path] = font;

			return font;
		}
	}

	Texture* Renderer::GetOrCreateTexture(const std::string& path)
	{
		if (m_LoadedTextures.find(path) != m_LoadedTextures.end())
		{
			return m_LoadedTextures[path];
		}
		else
		{
			Texture* texture = new Texture(path);
			LOG_CHECK(texture != nullptr) << "Data is null";

			m_LoadedTextures[path] = texture;

			return texture;
		}
	}

	Shader* Renderer::GetOrCreateShader(const std::string& path)
	{
		if (m_LoadedShaders.find(path) != m_LoadedShaders.end())
		{
			return m_LoadedShaders[path];
		}
		else
		{
			Shader* shader = new Shader(path);
			LOG_CHECK(shader != nullptr) << "Data is null";

			m_LoadedShaders[path] = shader;

			return shader;
		}
	}

}