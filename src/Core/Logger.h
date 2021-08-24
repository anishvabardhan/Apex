#pragma once

#include <string>
#include <sstream>
#include <stdio.h>

#undef ERROR

namespace Apex {

	enum SEVERITY {
		INFO    = 0,
		WARNING = 1,
		ERROR   = 2,
		FATAL   = 3
	};

	static const char* SeverityNames[] = {
		"INFO",
		"ERROR",
		"PROBLEM",
		"FATAL"
	};

	class Logger : public std::ostringstream 
	{
		SEVERITY m_Severity;
		const char* m_FileName;
		const char* m_FuncName;
		int m_Line;
	public:
		Logger(SEVERITY severity, const char* fileName, const char* funcName, int line);
		~Logger();
	protected:
		void printLogMessage();
	};

	class LoggerFatal : public Logger
	{
	public:
		LoggerFatal(const char* fileName, const char* funcName, int line);
		~LoggerFatal();
	};

#define LOG_INFO Logger(INFO,__FILE__,__FUNCTION__,__LINE__).flush()
#define LOG_WARNING Logger(WARNING,__FILE__,__FUNCTION__,__LINE__).flush()
#define LOG_ERROR Logger(ERROR,__FILE__,__FUNCTION__,__LINE__).flush()
#define LOG_FATAL LoggerFatal(__FILE__,__FUNCTION__,__LINE__).flush()
#define LOG(severity) LOG_##severity

#define CHECK_OP(val1,op,val2) \
	if(!(val1 op val2)) LoggerFatal(__FILE__,__FUNCTION__,__LINE__).flush() << "Check failed: " << " "

	Logger::Logger(SEVERITY severity, const char* fileName, const char* funcName, int line)
		: m_Severity(severity), m_FileName(fileName), m_FuncName(funcName), m_Line(line) 
	{

	}

	Logger::~Logger() 
	{
		if(SeverityNames[m_Severity] != "FATAL")
			printLogMessage();
	}

	void Logger::printLogMessage() 
	{
		fprintf(stderr, "[%s]: %s:%s:%d '%s'\n", SeverityNames[m_Severity], m_FileName, m_FuncName, m_Line, str().c_str());
	}

	LoggerFatal::LoggerFatal(const char* fileName, const char* funcName, int line)
		: Logger(FATAL, fileName, funcName, line) 
	{

	}

	LoggerFatal::~LoggerFatal() 
	{
		printLogMessage();
		abort();
	}

}