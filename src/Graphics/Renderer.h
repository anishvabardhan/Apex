#pragma once

#include <deque>

#include "Renderable2D.h"
#include "Tests/Astroids/Astroid.h"
#include "Tests/Astroids/Player.h"

namespace Apex {

	class Renderer
	{
	public:
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Draw(const Renderable2D& renderable) const;
		void Draw(const Astroid& renderable) const;
		void Draw(const Player& renderable) const;
	};

}