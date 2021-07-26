#pragma once

#include "../Graphics/Texture.h"

namespace Apex {

	struct FrameBufferSpecification
	{
		uint32_t s_Width, s_Height;
		uint32_t s_Samples = 1;

		bool s_SwapChainTarget = false;
	};

	class FrameBuffer
	{
		unsigned int m_RendererID;
		unsigned int m_ColorAttachment;
		FrameBufferSpecification m_Specification;
	public:
		FrameBuffer(const FrameBufferSpecification& spec);
		~FrameBuffer();

		void Bind();
		void UnBind();

		void Invalidate();

		const FrameBufferSpecification& GetSpecification() const;
		uint32_t GetColorAttachmentRendererID() const;
	};

}