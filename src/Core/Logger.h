#pragma once

#include <string>
#include <stdio.h>
#include <sstream>
#include <map>

#include <GL/glew.h>

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
		const char* m_FileName;
		int m_Line;
	public:
		LogMessage(Severity severity, const char* fileName, int line);
		~LogMessage();
	protected:
		void printLogMessage(const char* exitText = nullptr);
	private:
	};

	class LogMessageFatal : public LogMessage 
	{
	public:
		LogMessageFatal(const char* fileName, int line);
		~LogMessageFatal();
	};

#define LOG_INFO Apex::LogMessage(Apex::INFO,__FILE__,__LINE__).flush()
#define LOG_WARNING Apex::LogMessage(Apex::WARNING,__FILE__,__LINE__).flush()
#define LOG_FATAL Apex::LogMessageFatal(__FILE__,__LINE__).flush()
#define LOG(severity) LOG_##severity

#define LOG_CHECK(condition) \
	if(!(condition)) Apex::LogMessageFatal(__FILE__,__LINE__).flush() << "Check failed: "

	inline LogMessage::LogMessage(Severity severity, const char* fileName, int line)
		: m_Severity(severity), m_FileName(fileName), m_Line(line)
	{
	}

	inline LogMessage::~LogMessage() 
	{
		printLogMessage("");
	}

	inline void LogMessage::printLogMessage(const char* exitText) 
	{
		fprintf(stderr, "[%s%s\033[0m]: \033[0;36m%s(Line %d): %s'%s' %s\033[0m\n", SeverityColor[m_Severity], SeverityNames[m_Severity], m_FileName, m_Line, SeverityColor[m_Severity], str().c_str(), exitText);
	}

	inline LogMessageFatal::LogMessageFatal(const char* fileName, int line)
		: Apex::LogMessage(Apex::FATAL, fileName, line)
	{
	}

	inline LogMessageFatal::~LogMessageFatal() 
	{
		printLogMessage(", Application closed abruptly!");
		exit(0);
	}

}