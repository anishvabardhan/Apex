#pragma once

#include "../External/tinyxml2.h"
#include "../Maths/Vec2.h"
#include "../Maths/Vec3.h"
#include "../Maths/Vec4.h"
#include "../Maths/AABB2.h"

typedef tinyxml2::XMLElement XMLelement;

namespace Apex {

	class Vec2;
	class Vec3;
	class Vec4;
	class AABB2;

	int ParseXMLAttrib(const XMLelement& element, const char* attribName, int value);
	const char* ParseXMLAttrib(const XMLelement& element, const char* attribName, const char* value);
	bool ParseXMLAttrib(const XMLelement& element, const char* attribName, bool value);
	float ParseXMLAttrib(const XMLelement& element, const char* attribName, float value);
	Vec2 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec2& value);
	Vec3 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec3& value);
	Vec4 ParseXMLAttrib(const XMLelement& element, const char* attribName, const Vec4& value);
	AABB2 ParseXMLAttrib(const XMLelement& element, const char* attribName, const AABB2& value);

	int ParseXMLInnerText(const XMLelement& element, int value);
	const char* ParseXMLInnerText(const XMLelement& element, const char* value);
	bool ParseXMLInnerText(const XMLelement& element, bool value);
	float ParseXMLInnerText(const XMLelement& element, float value);
	Vec2 ParseXMLInnerText(const XMLelement& element, const Vec2& value);
	Vec3 ParseXMLInnerText(const XMLelement& element, const Vec3& value);
	Vec4 ParseXMLInnerText(const XMLelement& element, const Vec4& value);
	AABB2 ParseXMLInnerText(const XMLelement& element, const AABB2& value);

}