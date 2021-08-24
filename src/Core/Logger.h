#pragma once

#include <string>
#include <stdio.h>
#include <sstream>

namespace Apex {

	enum Severity {
		INFO = 0,
		WARNING = 1,
		PROBLEM = 2,
		FATAL = 3,
	};

	static const char* SeverityNames[] = { "INFO","WARNING","PROBLEM","FATAL" };

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

#define LOG_INFO Apex::LogMessage(INFO,__FUNCTION__,__LINE__).flush()
#define LOG_WARNING Apex::LogMessage(WARNING,__FUNCTION__,__LINE__).flush()
#define LOG_PROBLEM Apex::LogMessage(PROBLEM,__FUNCTION__,__LINE__).flush()
#define LOG_FATAL Apex::LogMessageFatal(__FUNCTION__,__LINE__).flush()
#define LOG(severity) LOG_##severity

#define CHECK(val1,op,val2) \
	if(!(val1 op val2)) Apex::LogMessageFatal(__FUNCTION__,__LINE__).flush() << "Check failed: " << " "


	inline LogMessage::LogMessage(Severity severity, const char* funcName, int line) :
		m_Severity(severity), m_FuncName(funcName), m_Line(line) {
	}

	inline LogMessage::~LogMessage() {
		printLogMessage();
	}

	inline void LogMessage::printLogMessage() {
		fprintf(stderr, "%s: %s: Line Number: %d '%s'\n", SeverityNames[m_Severity],  m_FuncName, m_Line, str().c_str());
	}

	inline LogMessageFatal::LogMessageFatal(const char* funcName, int line) :
		Apex::LogMessage(FATAL, funcName, line) {
	}

	inline LogMessageFatal::~LogMessageFatal() {
		printLogMessage();
		exit(0);
	}

}