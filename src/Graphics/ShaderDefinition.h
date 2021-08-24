#pragma once

#include "../Core/XMLParser.h"

#include <string>

namespace Apex {

	class ShaderDefinition
	{
	public:
		std::string m_FilePath = "INVALID";
		std::string m_BlendOp;
		std::string m_BlendSRC;
		std::string m_BlendDST;

		ShaderDefinition(const tinyxml2::XMLElement& element);
		~ShaderDefinition();

		static tinyxml2::XMLElement* InitializeDef(const std::string& path);
	};

}