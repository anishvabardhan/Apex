#include "Renderer.h"

#include "../Core/LogMessage.h"
#include "VertexPCU.h"
#include "MeshBuilder.h"
#include <vector>

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

	void Renderer::Drawtext(const Vec2& position, const std::string& asciiText, float quadHeight, Font* font, Shader shader)
	{
		font->GetSpriteSheet().GetSpriteSheetTexture().Bind(TEXTURESLOT::SLOT0);

		float quadWidth = quadHeight;
		
		AABB2 quadPos;
		AABB2 uvPos;
		
		quadPos.m_Mins.m_Y = position.m_Y;
		quadPos.m_Maxs.m_Y = position.m_Y + quadHeight;

		for (size_t i = 0; i < asciiText.size(); i++)
		{
			MeshBuilder* mb = new MeshBuilder();

			quadPos.m_Mins.m_X = (i * quadWidth) + position.m_X;
			quadPos.m_Maxs.m_X = ((i + 1) * quadWidth) + position.m_X;

			uvPos = font->GetGlyphUV(asciiText[i]);

			mb->Push(VertexPCU(Vec3(quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y)));
			mb->Push(VertexPCU(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y)));
			mb->Push(VertexPCU(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y)));
			mb->Push(VertexPCU(Vec3(quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y)));
			mb->CopyToGPU();

			Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
			shader.SetUniform1i("u_Texture", 0);
			shader.SetUniformMat4f("u_Model", model);

			DrawMesh(mb->GetMesh());

			delete mb;
		}
	}

	void Renderer::DrawQuad(const Vec2& position, const Vec2& dimensions, const Texture& texture, const AABB2& texCoords, const Vec4& color, Shader shader)
	{
		texture.Bind(TEXTURESLOT::SLOT2);

		MeshBuilder* mb = new MeshBuilder();

		mb->Push(VertexPCU(Vec3(position.m_X,                  position.m_Y,                  0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Mins.m_X, texCoords.m_Maxs.m_Y)));
		mb->Push(VertexPCU(Vec3(position.m_X + dimensions.m_X, position.m_Y,                  0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Maxs.m_X, texCoords.m_Maxs.m_Y)));
		mb->Push(VertexPCU(Vec3(position.m_X + dimensions.m_X, position.m_Y + dimensions.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Maxs.m_X, texCoords.m_Mins.m_Y)));
		mb->Push(VertexPCU(Vec3(position.m_X,                  position.m_Y + dimensions.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Mins.m_X, texCoords.m_Mins.m_Y)));
		mb->CopyToGPU();

		Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
		shader.SetUniform1i("u_Texture", 2);
		shader.SetUniformMat4f("u_Model", model);
		
		DrawMesh(mb->GetMesh());

		delete mb;
	}

	void Renderer::DrawQuad(const Vec2& position, Vec2 meshDim, Vec4 color, const std::string& path, Shader shader)
	{
		MeshBuilder* mb = new MeshBuilder();
		Texture* texture = new Texture(path);

		mb->Push(VertexPCU(Vec3(position.m_X,               position.m_Y              , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(0.0f, 0.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X + meshDim.m_X, position.m_Y              , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(1.0f, 0.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X + meshDim.m_X, position.m_Y + meshDim.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(1.0f, 1.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X,               position.m_Y + meshDim.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(0.0f, 1.0f)));
		mb->CopyToGPU();

		Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));

		texture->Bind(TEXTURESLOT::SLOT1);

		shader.SetUniform1i("u_Texture", 1);
		shader.SetUniformMat4f("u_Model", model);

		DrawMesh(mb->GetMesh());

		delete mb;
		delete texture;
	}

	void Renderer::DrawFrameBuffer(const Vec2& position, Vec2 meshDim)
	{
		MeshBuilder* mb = new MeshBuilder();

		mb->Push(VertexPCU(Vec3(position.m_X              , position.m_Y              , 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X + meshDim.m_X, position.m_Y              , 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X + meshDim.m_X, position.m_Y + meshDim.m_Y, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)));
		mb->Push(VertexPCU(Vec3(position.m_X              , position.m_Y + meshDim.m_Y, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)));
		mb->CopyToGPU();

		mb->GetMesh()->m_VAO->Bind();
		mb->GetMesh()->m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, mb->GetMesh()->m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

		mb->GetMesh()->m_IBO->UnBind();
		mb->GetMesh()->m_VAO->UnBind();

		delete mb;
	}

	void Renderer::DrawMesh(Mesh* mesh)
	{
		mesh->m_VAO->Bind();
		mesh->m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, mesh->m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

		mesh->m_IBO->UnBind();
		mesh->m_VAO->UnBind();
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

	Font* Renderer::CreateBitmapFont(const std::string& path)
	{
		Texture* texture = new Texture(path);
		LOG_CHECK(texture != nullptr) << "Data is null";

		SpriteSheet* bitMapsheet = new SpriteSheet(*texture, 16, 16);
		LOG_CHECK(bitMapsheet != nullptr) << "Data is null";

		Font* newFont = new Font(*bitMapsheet);
		LOG_CHECK(newFont != nullptr) << "Data is null";

		return newFont;
	}

	Texture* Renderer::CreateTexture(const std::string& path)
	{
		Texture* texture = new Texture(path);
		LOG_CHECK(texture != nullptr) << "Data is null";

		return texture;
	}

}