#include "SpriteAnimation.h"

#include "../Graphics/SpriteSheet.h"
#include "../Graphics/Texture.h"
#include "../Maths/AABB2.h"

namespace Apex {

	SpriteAnimation::SpriteAnimation(const SpriteSheet& spriteSheet,  float duration, int start, int end)
		: m_Elapsed(0), m_Duration(duration), m_Start(start), m_End(end), m_CurrentIndex(start), m_IsPlaying(true)
	{
		m_SpriteSheet = new SpriteSheet(spriteSheet.GetSpriteSheetTexture(), spriteSheet.GetLayout().m_X, spriteSheet.GetLayout().m_Y);
	}

	SpriteAnimation::~SpriteAnimation()
	{
		delete m_SpriteSheet;
	}

	void SpriteAnimation::Update(float deltaTime)
	{
		if (!m_IsPlaying)
		{
			deltaTime = 0.0f;
		}
		
		m_Elapsed += 16.0f * deltaTime;

		float elapsedFraction;
		elapsedFraction = m_Elapsed / m_Duration;
		
		if (m_Duration <= m_Elapsed)
		{
			m_Elapsed = 0.0f;
		}
		else
		{
			int temp = elapsedFraction * GetSpritesNumber();
			m_CurrentIndex = m_Start + temp;
		}
	}

	AABB2 SpriteAnimation::GetTexCoords()
	{
		return m_SpriteSheet->GetTexCoords(m_CurrentIndex);
	}

	Texture* SpriteAnimation::GetTexture()
	{
		return &m_SpriteSheet->GetSpriteSheetTexture();
	}

}