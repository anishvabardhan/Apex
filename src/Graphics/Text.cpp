#include "Text.h"

namespace Apex {

	Text::Text()
	{
	}

	Text::Text(int height)
		: m_Height(height)
	{
	}

	bool Text::LoadFont(FT_Library& library, std::string path)
	{
		FT_Face fontFace;

		if (FT_New_Face(library, path.c_str(), 0, &fontFace))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return false;
		}

		FT_Set_Pixel_Sizes(fontFace, 0, m_Height);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
			{
				continue;
			}

			unsigned int textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				fontFace->glyph->bitmap.width,
				fontFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				fontFace->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_Characters[c] = {
				textureId,
				Vec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
				Vec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
				(unsigned int)fontFace->glyph->advance.x
			};
		}

		FT_Done_Face(fontFace);

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		return true;
	}

	void Text::RenderText(std::string text, float x, float y, Vec2 scale)
	{		
		glActiveTexture(GL_TEXTURE1);

		glBindVertexArray(m_VAO);

		for (int i = 0; i < text.size(); i++)
		{
			Character c = m_Characters[text[i]];

			float xPos = x + c.s_Bearing.m_X * scale.m_X;
			float yPos = y - (c.s_Size.m_Y - c.s_Bearing.m_Y) * scale.m_Y;

			float width = c.s_Size.m_X * scale.m_X;
			float height = c.s_Size.m_Y * scale.m_Y;

			float vertices[6 * 4] = {
			    xPos,         yPos + height,     0.0f, 0.0f ,
			    xPos,         yPos,              0.0f, 1.0f ,
			    xPos + width, yPos,              1.0f, 1.0f ,
			    							     
			    xPos,         yPos + height,     0.0f, 0.0f ,
			    xPos + width, yPos,              1.0f, 1.0f ,
			    xPos + width, yPos + height,     1.0f, 0.0f 
			};

			glBindTexture(GL_TEXTURE_2D, c.s_TextureID);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			x += (c.s_Advance >> 6) * scale.m_X;
		}

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Text::CleanUp()
	{
	}

}