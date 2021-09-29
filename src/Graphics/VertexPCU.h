#pragma once

#include "../Maths/Maths.h"

namespace Apex {

	struct VertexPCU
	{
		Vec3 m_Pos;
		Vec4 m_Color;
		Vec2 m_UV;

		VertexPCU(Vec3 position, Vec4 color, Vec2 uv);
	};

}