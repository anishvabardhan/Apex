#pragma once

namespace Apex {

	class Texture;
	class AABB2;
	class SpriteSheet;

	class SpriteAnimation
	{
		bool m_IsPlaying;
		float m_DurationSeconds;
		float m_ElapsedSeconds;
		float m_FractionElapsed;
		int m_StartIndex;
		int m_EndIndex;
		int m_CurrentIndex;

		SpriteSheet* m_SpriteSheet;
	public:
		SpriteAnimation(const SpriteSheet& spriteSheet, float duration, int start, int end);
		~SpriteAnimation();

		void Update(float deltaTime);
		AABB2 GetTexCoords();
		Texture* GetTexture();			    
		void Reset();	

		inline int	GetNumSprites() const { return (m_EndIndex - m_StartIndex) + 1; }
	};

}