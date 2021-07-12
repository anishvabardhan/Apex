#pragma once

#include <string>
#include <map>

#include "../Maths/Maths.h"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Apex {

	struct Character {
		unsigned int s_TextureID;
		Vec2 s_Size;
		Vec2 s_Bearing;
		unsigned int s_Advance;
	};

	class Text
	{
		int m_Height;
		std::map<char, Character> m_Characters;
		unsigned int m_VAO, m_VBO;
	public:
		Text();
		Text(int height);

		bool LoadFont(FT_Library& library, std::string path);

		void RenderText(std::string text, float x, float y, Vec2 scale);

		void CleanUp();
	};

}