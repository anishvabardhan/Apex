#include "SpriteAnimation.h"

#include "../Graphics/SpriteSheet.h"
#include "../Graphics/Texture.h"
#include "../Maths/AABB2.h"

namespace Apex {



	SpriteAnimation::SpriteAnimation(const SpriteSheet& spriteSheet,  float duration, int start, int end)
		: m_ElapsedSeconds(0), m_DurationSeconds(duration), m_StartIndex(start), m_EndIndex(end), m_CurrentIndex(start), m_IsPlaying(true)
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
		
		m_ElapsedSeconds += deltaTime;
		m_FractionElapsed = m_ElapsedSeconds / m_DurationSeconds;
		
		if (m_ElapsedSeconds >= m_DurationSeconds)
		{
			Reset();
		}
		else
		{
			m_CurrentIndex = m_StartIndex + (int)(m_FractionElapsed * GetNumSprites());
		}
	}

	AABB2 SpriteAnimation::GetTexCoords()
	{
		return m_SpriteSheet->GetTexCoords(m_CurrentIndex);
	}

	Texture* SpriteAnimation::GetTexture()
	{
		Texture* texture = &m_SpriteSheet->GetSpriteSheetTexture();

		return texture;
	}
	void SpriteAnimation::Reset()
	{
		m_ElapsedSeconds = 0.0f;
	}

}