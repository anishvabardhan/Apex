#pragma once

#include "Maths/Mat4.h"

namespace Apex {

	class Camera
	{
	public:
		virtual Mat4 CreateCamera() { return Mat4(); }
	};

}