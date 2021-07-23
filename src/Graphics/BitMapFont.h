#pragma once

#include <string>

namespace Apex {

	class AABB2;
	class SpriteSheet;
	class Texture;

	class BitMapFont
	{
		const	SpriteSheet& m_spriteSheet;
		float			m_baseAspect = 1.0f;
		std::string		m_fontName;
	public:
		explicit BitMapFont(const std::string& fontName, const SpriteSheet& glyphSheet, float baseAspect);


		AABB2		GetUVsForGlyph(int glyphUnicode) const;
		float		GetGlyphAspect(int glyphUnicode) const { return m_baseAspect; (void)(glyphUnicode); }
		float		GetStringWidth(const std::string& asciiText, float cellHeight, float aspectScale) const;
		const	    Texture* GetSpriteSheetTexture() const;
	private:
		friend class Renderer;
	};

}