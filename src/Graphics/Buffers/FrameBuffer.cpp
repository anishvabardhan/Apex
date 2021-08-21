#include "FrameBuffer.h"

#include "../Graphics/Texture.h"

#include <GL/glew.h>
#include <iostream>

namespace Apex {

	FrameBuffer::FrameBuffer()
	{
		Invalidate();
	}
	
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBufferID);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBufferID);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Invalidate()
	{
		glGenFramebuffers(1, &m_FrameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int FrameBuffer::GetFrameBufferID() const
	{
		return m_FrameBufferID;
	}

	unsigned int FrameBuffer::GetColorAttachmentID() const
	{
		return m_ColorAttachment;
	}

}