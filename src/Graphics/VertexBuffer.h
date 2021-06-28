#pragma once

#include <GL/glew.h>

namespace Apex {

	class VertexBuffer
	{
// Member Variables-------------------------------------------------------------------------------------

		unsigned int m_RendererID;
	public:
		explicit VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;
	};

}