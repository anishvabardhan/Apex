#pragma once

#include "../Maths/Vec2.h"

#include "Texture.h"
#include "../Maths/AABB2.h"

namespace Apex {

	class SpriteSheet
	{
		const Texture& m_SpriteSheetTexture;
		Vec2 m_SpriteLayout;
	public:
		SpriteSheet(const Texture& texture, int tilesWide, int tilesHigh);
		~SpriteSheet();

		AABB2 GetTexCoords(int charAscii);
		const Texture& GetSpriteSheetTexture() const { return m_SpriteSheetTexture; }
	};

}