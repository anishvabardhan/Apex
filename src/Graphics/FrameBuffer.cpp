#include "FrameBuffer.h"

#include <GL/glew.h>

namespace Apex {

	FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec)
		: m_Specification(spec)
	{
		Invalidate();
	}
	
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_TEXTURE_2D, m_RendererID);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}

	void FrameBuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_TEXTURE_2D, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.s_Width, m_Specification.s_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}
	
	const FrameBufferSpecification& FrameBuffer::GetSpecification() const
	{
		return m_Specification;
	}

	uint32_t FrameBuffer::GetColorAttachmentRendererID() const
	{
		return m_ColorAttachment;
	}

}