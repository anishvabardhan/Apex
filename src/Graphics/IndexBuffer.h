#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Apex {

	class IndexBuffer
	{
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		inline unsigned int GetCount() const { return m_Count; }
	};

}