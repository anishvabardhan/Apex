#include "SpriteSheet.h"

namespace Apex {

	SpriteSheet::SpriteSheet(const Texture& texture, int tilesWide, int tilesHigh)
		: m_SpriteSheetTexture(texture), m_SpriteLayout(Vec2(tilesWide, tilesHigh))
	{
	}

	SpriteSheet::~SpriteSheet()
	{
	}
	
	AABB2 SpriteSheet::GetTexCoordsForSpriteCoords(const Vec2& spriteCoords) const
	{
		AABB2 texCoords;
		texCoords.m_Mins.m_X = (spriteCoords.m_X) * 1.f / (m_SpriteLayout.m_X);
		texCoords.m_Mins.m_Y = (spriteCoords.m_Y) * 1.f / (m_SpriteLayout.m_Y);

		texCoords.m_Maxs.m_X = (spriteCoords.m_X + 1) * 1.f / (m_SpriteLayout.m_X);
		texCoords.m_Maxs.m_Y = (spriteCoords.m_Y + 1) * 1.f / (m_SpriteLayout.m_Y);

		texCoords.m_Mins.m_Y = 1.0f - texCoords.m_Mins.m_Y;
		texCoords.m_Maxs.m_Y = 1.0f - texCoords.m_Maxs.m_Y;

		return texCoords;
	}
	
	AABB2 SpriteSheet::GetTexCoordsForSpriteCoords(int spriteIndex) const
	{
		Vec2 spriteCoords;

		spriteCoords.m_X = int(spriteIndex % (int)m_SpriteLayout.m_Y);
		spriteCoords.m_Y = int(spriteIndex / (int)m_SpriteLayout.m_Y);

		return GetTexCoordsForSpriteCoords(spriteCoords);
	}
	
	int SpriteSheet::GetNumSprites() const
	{
		return m_SpriteLayout.m_X * m_SpriteLayout.m_Y;
	}

}