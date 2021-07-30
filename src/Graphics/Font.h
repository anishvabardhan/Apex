#pragma once

#include <string>

#include "../Maths/AABB2.h"
#include "SpriteSheet.h"
#include "Texture.h"

namespace Apex {

	class Font
	{
		SpriteSheet m_SpriteSheet;
	public:
		explicit Font(SpriteSheet glyphSheet);
		~Font();

		AABB2 GetGlyphUV(int glyphAscii);
		float GetStringWidth(const std::string& asciiText, float cellHeight);
		const Texture* GetSpriteTexture() const;
		inline SpriteSheet GetSpriteSheet() const { return m_SpriteSheet; }
	};

}