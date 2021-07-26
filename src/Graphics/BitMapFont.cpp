#include "BitMapFont.h"

#include "../Maths/AABB2.h"
#include "SpriteSheet.h"

namespace Apex {

	BitMapFont::BitMapFont(const std::string& fontName, const SpriteSheet& glyphSheet, float baseAspect)
		: m_fontName(fontName), m_spriteSheet(glyphSheet), m_baseAspect(baseAspect)
	{
	}

	AABB2 BitMapFont::GetUVsForGlyph(int glyphUnicode) const
	{
		AABB2 uv = m_spriteSheet.GetTexCoordsForSpriteCoords(glyphUnicode);

		return uv;
	}

	float BitMapFont::GetStringWidth(const std::string& asciiText, float cellHeight, float aspectScale) const
	{

		float cellWidth = cellHeight * (m_baseAspect * aspectScale);
		return cellWidth * float(asciiText.length());
	}

	const Texture* BitMapFont::GetSpriteSheetTexture() const
	{
		return &m_spriteSheet.GetSpriteSheetTexture();
	}

}