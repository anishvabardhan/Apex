#include "SpriteDefinition.h"

#include "../Core/Logger.h"
#include "../Maths/Maths.h"

namespace Apex {

	SpriteDefinition::SpriteDefinition(const tinyxml2::XMLElement& element)
	{
		m_SpriteCoords = ParseXMLAttrib(element, "spriteCoords", Vec2(-1, -1));
		LOG_CHECK(m_SpriteCoords != Vec2(-1, -1)) << "Data couldn't be parsed.";

		m_SpriteDim = ParseXMLAttrib(element, "spriteDimensions", Vec2(-1, -1));
		LOG_CHECK(m_SpriteDim != Vec2(-1, -1)) << "Data couldn't be parsed.";

		m_Tiles = ParseXMLAttrib(element, "tiles", Vec2(-1, -1));
		LOG_CHECK(m_Tiles != Vec2(-1, -1)) << "Data couldn't be parsed.";

		m_Color = ParseXMLAttrib(element, "color", Vec4(-1, -1, -1, -1));
		LOG_CHECK(m_Color != Vec4(-1, -1, -1, -1)) << "Data couldn't be parsed.";
	}

	SpriteDefinition::~SpriteDefinition()
	{
	}

	tinyxml2::XMLElement* SpriteDefinition::InitializeDef(const std::string& path)
	{
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
        doc->LoadFile(path.c_str());
		
		tinyxml2::XMLElement* root = doc->FirstChildElement()->FirstChildElement();

		return root;
	}

}