#include "XMLParser.h"

#include "StringTokenizer.h"

namespace Apex {

	int ParseXMLAttrib(const XMLelement& element, const char* attribName, int value)
	{
		int intValue = value;
		const char* intText = element.Attribute(attribName);

		if (intText)
		{
			int temp = atoi(intText);
			intValue = temp;
		}

		return intValue;
	}
	
	float ParseXMLAttrib(const XMLelement& element, const char* attribName, float value)
	{
		float val = value;
		const char* floatText = element.Attribute(attribName);

		if (floatText)
		{
			float temp = atof(floatText);
			val = temp;
		}

		return val;
	}

	Vec2 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec2& value)
	{
		Vec2 vec2 = value;
		const char* vecText = element.Attribute(attribName);

		if (vecText)
		{
			std::string temp = vecText;
			std::string newX, newY;
			size_t commaIndex = 0;

			commaIndex = temp.find(",", commaIndex);
			
			newX = std::string(temp, 0, commaIndex);
			newY = std::string(temp, commaIndex + 1);

			vec2.m_X = atof(newX.c_str());
			vec2.m_Y = atof(newY.c_str());
		}

		return vec2;
	}
	
	Vec3 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec3& value)
	{
		Vec3 vec3 = value;
		const char* vecText = element.Attribute(attribName);

		if (vecText)
		{
			StringTokenizer tokenizer(vecText, ",");
			tokenizer.Tokenize();

			std::vector<std::string> tokens(3);

			tokens = tokenizer.GetTokens();

			vec3.m_X = strtof(tokens[0].c_str(), nullptr);
			vec3.m_Y = strtof(tokens[1].c_str(), nullptr);
			vec3.m_Z = strtof(tokens[2].c_str(), nullptr);
		}

		return vec3;
	}
	
	Vec4 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec4& value)
	{
		Vec4 vec4 = value;
		const char* vecText = element.Attribute(attribName);

		if (vecText)
		{
			StringTokenizer tokenizer(vecText, ",");
			tokenizer.Tokenize();

			std::vector<std::string> tokens(4);

			tokens = tokenizer.GetTokens();

			vec4.m_X = strtof(tokens[0].c_str(), nullptr);
			vec4.m_Y = strtof(tokens[1].c_str(), nullptr);
			vec4.m_Z = strtof(tokens[2].c_str(), nullptr);
			vec4.m_W = strtof(tokens[3].c_str(), nullptr);
		}

		return vec4;
	}

}