#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Apex {

	class VertexBuffer
	{
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;
	};

}