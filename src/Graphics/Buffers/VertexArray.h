#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Apex {

	class VertexArray
	{
// Member Variables-------------------------------------------------------------------------------------

		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void UnBind() const;
	};

}