#pragma once

#include "../src/Maths/Vec2.h"
#include "../src/Physics/2D/Disc2D.h"
#include "Entity.h"

namespace Apex {

	class Astroid : public Entity
	{
		Vec2 m_Position;
		Vec2 m_Translate;
        Vec2 m_Velocity, m_Accelaration;
		
		int m_NumOfVertices;
		
		float m_Angle;
	public:
		explicit Astroid(Vec2 position, int i);
		~Astroid();

		void OnUpdate(float dt) override;
		void Render() override;

		void Translation();
		void Rotation();

		inline Vec2 GetPostion() const { return m_Position; }
		inline Vec2 GetTranslate() const { return m_Translate; }
	};

}