#pragma once

namespace Apex {

	class Texture;
	class AABB2;
	class SpriteSheet;

	enum SPRITEANIMATIONMODE
	{
		PLAY_ONCE,
		PLAY_LOOP
	};

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
		SPRITEANIMATIONMODE	m_SpriteAnimMode;
	public:
		SpriteAnimation(const SpriteSheet& spriteSheet, SPRITEANIMATIONMODE playMode, float duration, int start, int end);
		~SpriteAnimation();

		void Update(float deltaSeconds);
		AABB2 GetTexCoords();
		Texture* GetTexture();			    
		void Reset();	

		inline bool IsPlaying() const { return m_IsPlaying; }
		inline int	GetNumSprites() const { return (m_EndIndex - m_StartIndex) + 1; }
	};

}