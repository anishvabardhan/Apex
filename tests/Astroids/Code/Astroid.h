#pragma once

#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Physics/2D/Disc2D.h"
#include "Entity.h"

namespace Apex {

	class Astroid : public Entity
	{
	public:
		Vec2 m_Position;
		Vec2 m_Translate;
		Vec2 m_Velocity;
		Vec2 m_Accelaration;
		
		Vec3 m_BodyVertices[6];

		int m_NumOfVertices;
		
		float m_Radius;
		float m_Angle;
		float m_Min;
		float m_Max;
	public:
		explicit Astroid(Vec2 position, Vec2 translate, float min, float max);
		~Astroid();

		void OnUpdate(float dt) override;
		void Render() override;

		void Translation();
		void Rotation();

		inline float GetRadius() const { return m_Radius; }
		inline Vec2 GetPosition() const { return m_Position; }
		inline Vec2 GetTranslate() const { return m_Translate; }
	};

}