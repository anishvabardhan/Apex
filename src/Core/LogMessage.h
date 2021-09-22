#pragma once

#include <string>
#include <sstream>

namespace Apex {

	//----------------------------------------------------------------------------------------------------------------------------
	// Defining the Logging Checks of all severities

#define LOG_INFO Apex::LogMessage(Apex::INFO, __FILE__, __LINE__)
#define LOG_WARNING Apex::LogMessage(Apex::WARNING,__FILE__,__LINE__)
#define LOG_FATAL Apex::LogMessageFatal(__FILE__,__LINE__)
#define LOG(severity) LOG_##severity

#define LOG_CHECK(condition) \
	if(!(condition)) Apex::LogMessageFatal(__FILE__,__LINE__) << "Check failed: "

	//----------------------------------------------------------------------------------------------------------------------------
	// Defining the SEVERITY Levels

	enum SEVERITY {
		INFO      = 0,
		WARNING   = 1,
		FATAL     = 2
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Declaring Functions

	unsigned int GetMessageBoxIconForSeverity(SEVERITY severity);
	bool IsDebuggerPresent();

	std::string Stringf(const char* messageText, ...);
	void Debugf(const char* messageText, ...);
    void LogToIDE(const std::string& msg);
	
	bool MessageOK(const std::string& messageText, const std::string& severityName, SEVERITY severity);
	bool MessageYesNo(const std::string& messageText, const std::string& severityName, SEVERITY severity);

	//----------------------------------------------------------------------------------------------------------------------------
	// global variables

	static const char* SeverityNames[] = { "INFO","WARNING", "FATAL" };

	//----------------------------------------------------------------------------------------------------------------------------
	// Creating the base Logging Class

	class LogMessage : public std::ostringstream 
	{
		//------------------------------------------------------------------------------------------------------------------------
		// Member Variables

		SEVERITY m_Severity;
		const char* m_FileName;
		int m_Line;
	public:				
		//------------------------------------------------------------------------------------------------------------------------
		//Construtor/Destructors

		LogMessage(SEVERITY severity, const char* fileName = nullptr, int line = 0);
		~LogMessage();
	protected:
		//------------------------------------------------------------------------------------------------------------------------
		// Methods

	    void Log(SEVERITY severity);
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Creating the child class LoggingFatal for fatal severity

	class LogMessageFatal : public LogMessage 
	{
	public:
		//------------------------------------------------------------------------------------------------------------------------
		//Construtor/Destructors

		LogMessageFatal(const char* fileName, int line);
		~LogMessageFatal();
	};

}