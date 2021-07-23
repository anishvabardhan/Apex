#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Strings;

namespace Apex {

	class StringUtils
	{
	public:
		static std::string Stringf(const char* format, ...);
		static std::string Stringf(const int maxLength, const char* format, ...);
	};

}