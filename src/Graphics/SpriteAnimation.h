#pragma once

namespace Apex {

	class Texture;
	class AABB2;
	class SpriteSheet;

	class SpriteAnimation
	{
		SpriteSheet* m_SpriteSheet;
		bool m_IsPlaying;
		float m_Duration;
		float m_Elapsed;
		int m_Start;
		int m_End;
		int m_CurrentIndex;
	public:
		SpriteAnimation(const SpriteSheet& spriteSheet, float duration, int start, int end);
		~SpriteAnimation();

		void Update(float deltaTime);
		AABB2 GetTexCoords();
		Texture* GetTexture();			    

		inline int GetSpritesNumber() const { return m_End - m_Start + 1; }
	};

}