#pragma once

#include <string>
#include <stdio.h>
#include <sstream>
#include <map>

namespace Apex {

	enum Severity {
		INFO = 0,
		WARNING = 1,
		FATAL = 2
	};

	static const char* SeverityNames[] = { "INFO","WARNING", "FATAL" };

	static std::map<int, const char*>SeverityColor = {
		{0, "\033[0;32m"},
		{1, "\033[0;33m"},
		{2, "\033[0;31m"}
	};

	class LogMessage : public std::ostringstream 
	{
		Severity m_Severity;
		const char* m_FuncName;
		int m_Line;
	public:
		LogMessage(Severity severity, const char* funcName, int line);
		~LogMessage();
	protected:
		void printLogMessage();
	private:
	};

	class LogMessageFatal : public LogMessage 
	{
	public:
		LogMessageFatal(const char* funcName, int line);
		~LogMessageFatal();
	};

#define LOG_INFO Apex::LogMessage(Apex::INFO,__FUNCTION__,__LINE__).flush()
#define LOG_WARNING Apex::LogMessage(Apex::WARNING,__FUNCTION__,__LINE__).flush()
#define LOG_FATAL Apex::LogMessageFatal(__FUNCTION__,__LINE__).flush()
#define LOG(severity) LOG_##severity

#define LOG_CHECK(condition) \
	if(!(condition)) Apex::LogMessageFatal(__FUNCTION__,__LINE__).flush() << "Check failed: " << " "


	inline LogMessage::LogMessage(Severity severity, const char* funcName, int line) 
		: m_Severity(severity), m_FuncName(funcName), m_Line(line) 
	{
	}

	inline LogMessage::~LogMessage() 
	{
		printLogMessage();
	}

	inline void LogMessage::printLogMessage() 
	{
		fprintf(stderr, "[%s%s\033[0m]: \033[0;36m%s: Line Number: %d '%s'\033[0m\n", SeverityColor[m_Severity], SeverityNames[m_Severity],  m_FuncName, m_Line, str().c_str());
	}

	inline LogMessageFatal::LogMessageFatal(const char* funcName, int line)
		: Apex::LogMessage(Apex::FATAL, funcName, line)
	{
	}

	inline LogMessageFatal::~LogMessageFatal() 
	{
		printLogMessage();
		exit(0);
	}

}