#pragma once

#include "../External/tinyxml2.h"
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Maths/Vec4.h"

typedef tinyxml2::XMLElement XMLelement;

namespace Apex {

	class Vec2;
	class Vec3;
	class Vec4;

	int ParseXMLAttrib(const XMLelement& element, const std::string& attribName, int value);
	float ParseXMLAttrib(const XMLelement& element, const std::string& attribName, float value);
	Vec2 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec2& value);
	Vec3 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec3& value);
	Vec4 ParseXMLAttrib(const XMLelement& element, const std::string& attribName, const Vec4& value);

}