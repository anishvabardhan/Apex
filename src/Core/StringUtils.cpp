#include "StringUtils.h"

#include <stdarg.h>

const int STRINGF_STACK_LOCAL_TEMP_LENGTH = 2048;

namespace Apex {

	std::string StringUtils::Stringf(const char* format, ...)
	{
		char textLiteral[STRINGF_STACK_LOCAL_TEMP_LENGTH];
		va_list variableArgumentList;
		va_start(variableArgumentList, format);
		vsnprintf_s(textLiteral, STRINGF_STACK_LOCAL_TEMP_LENGTH, _TRUNCATE, format, variableArgumentList);
		va_end(variableArgumentList);
		textLiteral[STRINGF_STACK_LOCAL_TEMP_LENGTH - 1] = '\0';

		return std::string(textLiteral);
	}

	std::string StringUtils::Stringf(const int maxLength, const char* format, ...)
	{
		char textLiteralSmall[STRINGF_STACK_LOCAL_TEMP_LENGTH];
		char* textLiteral = textLiteralSmall;
		if (maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH)
			textLiteral = new char[maxLength];

		va_list variableArgumentList;
		va_start(variableArgumentList, format);
		vsnprintf_s(textLiteral, maxLength, _TRUNCATE, format, variableArgumentList);
		va_end(variableArgumentList);
		textLiteral[maxLength - 1] = '\0';

		std::string returnValue(textLiteral);
		if (maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH)
			delete[] textLiteral;

		return returnValue;
	}

}