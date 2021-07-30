#pragma once

namespace Apex {

	class FrameBuffer
	{
		unsigned int m_FrameBufferID;
		unsigned int m_ColorAttachment;
	public:
		FrameBuffer();
		~FrameBuffer();

		void Bind();
		void UnBind();

		void Invalidate();

		unsigned int GetFrameBufferID() const;
		unsigned int GetColorAttachmentID() const;
	};

}