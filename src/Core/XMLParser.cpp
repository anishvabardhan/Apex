#include "XMLParser.h"

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
	
	const char* ParseXMLAttrib(const XMLelement& element, const char* attribName, const char* value)
	{
		const char* text = value;
		const char* valueText = element.Attribute(attribName);

		if (valueText)
			text = valueText;

		return text;
	}
	
	bool ParseXMLAttrib(const XMLelement& element, const char* attribName, bool value)
	{
		bool val = value;
		const char* boolText = element.Attribute(attribName);

		if (boolText)
		{
			bool temp;
			std::string text = boolText;
			
			if (text == "true")
				temp = true;
			else
				temp = false;

			val = temp;
		}

		return val;
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
		return Vec2();
	}
	
	Vec3 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec3& value)
	{
		return Vec3();
	}
	
	Vec4 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec4& value)
	{
		return Vec4();
	}
	
	AABB2 ParseXMLAttrib(const XMLelement& element, const char* attribName, const AABB2& value)
	{
		return AABB2();
	}
	
	int ParseXMLInnerText(const XMLelement& element, int value)
	{
		return 0;
	}
	
	const char* ParseXMLInnerText(const XMLelement& element, const char* value)
	{
		return 0;
	}
	
	bool ParseXMLInnerText(const XMLelement& element, bool value)
	{
		return false;
	}
	
	float ParseXMLInnerText(const XMLelement& element, float value)
	{
		return 0.0f;
	}
	
	Vec2 ParseXMLInnerText(const XMLelement& element, const Vec2& value)
	{
		return Vec2();
	}
	
	Vec3 ParseXMLInnerText(const XMLelement& element, const Vec3& value)
	{
		return Vec3();
	}
	
	Vec4 ParseXMLInnerText(const XMLelement& element, const Vec4& value)
	{
		return Vec4();
	}
	
	AABB2 ParseXMLInnerText(const XMLelement& element, const AABB2& value)
	{
		return AABB2();
	}

}