#pragma once

#include <string>
#include <vector>

namespace Apex {

	class StringTokenizer
	{
		std::string	m_InputString;
		std::string	m_DelimiterString;
		std::vector<std::string> m_Tokens;
		bool m_QuoteCheck = false;
	public:
		StringTokenizer(const std::string& input, const std::string& delimiter = "") : m_InputString(input), m_DelimiterString(delimiter) {}
		~StringTokenizer() {}

		std::vector<std::string> GetTokens() const { return m_Tokens; }
		size_t GetTokenCount() const { return m_Tokens.size(); }
		bool IsQuoteCheck() const { return m_QuoteCheck; }
			 
		void SetString(const std::string& newString) { m_InputString = newString; }
		void Tokenize(const std::string& delimiter = "");
		size_t HandleQuotation(size_t prevDelimiterIndex);
		void TrimEmpty();
		void SetQuoteCheck(bool flag) { m_QuoteCheck = flag; }
	};

}