#pragma once

#include "Maths/Vec3.h";

namespace Apex {

	class Ship
	{
		Vec3 m_Position;
	public:
		explicit Ship(Vec3 position);
		~Ship();

		void Render();

		void Translation(float x = 0, float y = 0);
		void Rotation(float angle);

		inline Vec3 GetPosition() const { return m_Position; }
		static inline Vec3 GetNosePosition() { return Vec3(0.0f, 15.0f, 0.0f); }

		inline void SetPosition(Vec3 position) { m_Position = position; }
	};

}