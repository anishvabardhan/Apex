#pragma once

#include "Physics/2D/Disc2D.h"
#include "Maths/Vec2.h"

namespace Apex {

	class DebugSystem
	{
	public:
		DebugSystem();
		~DebugSystem();

		static void DebugCircle(float scale);
		static void DebugLine();
	};

}