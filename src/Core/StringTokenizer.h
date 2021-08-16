#pragma once

#include <string>
#include <vector>

namespace Apex {

	class StringTokenizer
	{
		std::string m_Input;
		std::string m_Delimiter;
		std::vector<std::string> m_Tokens;
	public:
		StringTokenizer(const std::string& input, const std::string& delimiter = "");
		~StringTokenizer();

		inline std::vector<std::string> GetTokens() const { return m_Tokens; }
		inline size_t GetTokenCount() const { return m_Tokens.size(); }
		inline void SetString(const std::string& newString) { m_Input = newString; }

		void Tokenize(const std::string& delimiter = "");

		const std::string Stringf(const char* format, ...);
	};

}