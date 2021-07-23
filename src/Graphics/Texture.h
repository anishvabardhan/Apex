#pragma once

#include <string>

namespace Apex {

	class Texture
	{
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		explicit Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		inline unsigned int GetHandle() { return m_RendererID; }
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	};

}