#pragma once

#include "../Core/XMLParser.h"

namespace Apex {

	class Vec2;
	class Vec4;

	class SpriteDefinition
	{
	public:
		Vec2 m_SpriteCoords;
		Vec2 m_SpriteDim;
		Vec2 m_Tiles;
		Vec4 m_Color;

		SpriteDefinition(const tinyxml2::XMLElement& element);
		~SpriteDefinition();

		static tinyxml2::XMLElement* InitializeDef(const std::string& path);
	};

}