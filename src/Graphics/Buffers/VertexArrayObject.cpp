#include "VertexArrayObject.h"

namespace Apex {

	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArrayObject::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexArrayObject::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArrayObject::UnBind() const
	{
		glBindVertexArray(0);
	}

}