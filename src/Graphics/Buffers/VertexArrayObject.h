#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Apex {

	class VertexArrayObject
	{
// Member Variables-------------------------------------------------------------------------------------

		unsigned int m_RendererID;
	public:
		VertexArrayObject();
		~VertexArrayObject();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void UnBind() const;
	};

}