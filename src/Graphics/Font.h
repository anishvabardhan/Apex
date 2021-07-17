#pragma once

#include <string>
#include <vector>

#include "../Maths/Maths.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

namespace Apex {

	struct fontSpec
	{
		Vec2 texCoord;
		std::vector<Vec2> quadCoord;
	};

	class Font
	{
		std::string m_Text;
		std::vector<VertexArray*> m_VAO;
		std::vector<IndexBuffer*> m_IBO;
	public:
		explicit Font(std::string text, float xpos, float ypos, float scale);
		~Font();

		void BuildFont(std::string text, float xpos, float ypos, float scale);
		void DrawFontText(Shader shader);
	};

}