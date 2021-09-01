#pragma once

#include <Windows.h>
#include <string>
#include <stdarg.h>
#include <sstream>
#include <map>

namespace Apex {

	//----------------------------------------------------------------------------------------------------------------------------
	// Defining the SEVERITY Levels-----------------------------------------------------------------------------------------------

	enum SEVERITY {
		INFO      = 0,
		WARNING   = 1,
		FATAL     = 2
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Declaring Functions--------------------------------------------------------------------------------------------------------

	unsigned int GetMessageBoxIconForSeverity(SEVERITY severity);
	inline std::string Stringf(const char* messageText, ...);
	inline void Debugf(const char* messageText, ...);
	inline bool MessageOK(const std::string& messageText, const std::string& severityName, SEVERITY severity);
	inline bool MessageYesNo(const std::string& messageText, const std::string& severityName, SEVERITY severity);

	//----------------------------------------------------------------------------------------------------------------------------
	// Declaring a string array of severity levels--------------------------------------------------------------------------------

	static const char* SeverityNames[] = { "INFO","WARNING", "FATAL" };

	//----------------------------------------------------------------------------------------------------------------------------
	// Declaring a HashMap of colors for severity levels--------------------------------------------------------------------------

	static std::map<int, const char*>SeverityColor = {
		{0, "\033[0;32m"},
		{1, "\033[0;33m"},
		{2, "\033[0;31m"}
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Calling pre-Defined WINAPI Message Box Icons for different levels of severity----------------------------------------------

	unsigned int GetMessageBoxIconForSeverity(SEVERITY severity)
	{
		switch (severity)
		{
		case Apex::WARNING: return MB_ICONEXCLAMATION;
		case Apex::FATAL:   return MB_ICONHAND;
		default:            return MB_ICONEXCLAMATION;
		}
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Creating the base Logging Class--------------------------------------------------------------------------------------------

	class LogMessage : public std::ostringstream 
	{
		//------------------------------------------------------------------------------------------------------------------------
		// Member Variables-------------------------------------------------------------------------------------------------------

		SEVERITY m_Severity;
		const char* m_FileName;
		int m_Line;
	public:				
		//------------------------------------------------------------------------------------------------------------------------
		//Construtor/Destructors--------------------------------------------------------------------------------------------------

		LogMessage(SEVERITY severity, const char* fileName = nullptr, int line = 0);
		~LogMessage();
	protected:
		//------------------------------------------------------------------------------------------------------------------------
		// Methods----------------------------------------------------------------------------------------------------------------

		void printLogMessage(SEVERITY severity);
	};

	//----------------------------------------------------------------------------------------------------------------------------
	// Creating the child class LoggingFatal for fatal severity-------------------------------------------------------------------

	class LogMessageFatal : public LogMessage 
	{
	public:
		//------------------------------------------------------------------------------------------------------------------------
		//Construtor/Destructors--------------------------------------------------------------------------------------------------

		LogMessageFatal(const char* fileName, int line);
		~LogMessageFatal();
	};

	//----------------------------------------------------------------------------------------------------------------------------
	//---------------------------------xx Defining the Methods/Functions xx-------------------------------------------------------

	inline LogMessage::LogMessage(SEVERITY severity, const char* fileName, int line)
		: m_Severity(severity), m_FileName(fileName), m_Line(line)
	{
	}

	inline LogMessage::~LogMessage() 
	{
		printLogMessage(m_Severity);
	}

	inline void LogMessage::printLogMessage(SEVERITY severity)
	{
		if (severity == Apex::INFO)
		{
			Debugf("\n------------------------------------------------------------------------------\n");
			Debugf("\n[%s%s\033[0m]: %s(Line %d): %s\n", SeverityColor[m_Severity], SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
			Debugf("\n------------------------------------------------------------------------------\n");
		}
		else
		{
			std::string messageText;
			bool isDebuggerPresent = (IsDebuggerPresent() == TRUE);

			if (isDebuggerPresent)
			{
				messageText += "\nWould you like to break and debug?\n";
			}

			messageText += Apex::Stringf("\n[%s]: %s(Line %d): %s\n", SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());

			Debugf("\n------------------------------------------------------------------------------\n");
			Debugf("\n[%s%s\033[0m]: %s(Line %d): %s\n", SeverityColor[m_Severity], SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
			Debugf("\n------------------------------------------------------------------------------\n");

			if (isDebuggerPresent)
			{
				bool isYesNo = Apex::MessageYesNo(messageText, SeverityNames[m_Severity], severity);
				
				if (isYesNo)
				{
					__debugbreak();
				}
			}
			else
			{
				Apex::MessageOK(messageText, SeverityNames[m_Severity], severity);
			}
		}
	}

	inline LogMessageFatal::LogMessageFatal(const char* fileName, int line)
		: Apex::LogMessage(Apex::FATAL, fileName, line)
	{
	}

	inline LogMessageFatal::~LogMessageFatal() 
	{
		printLogMessage(Apex::FATAL);
		exit(0);
	}

	inline std::string Stringf(const char* messageText, ...)
	{
		char text[2048];
		va_list VAList;
		va_start(VAList, messageText);
		vsnprintf_s(text, 2048, _TRUNCATE, messageText, VAList);
		va_end(VAList);
		text[2047] = '\0';

		return std::string(text);
	}

	inline void Debugf(const char* messageText, ...)
	{
		char debugText[2048];
		va_list VAList;
		va_start(VAList, messageText);
		vsnprintf_s(debugText, 2048, _TRUNCATE, messageText, VAList);
		va_end(VAList);
		debugText[2047] = '\0';

		if (IsDebuggerPresent())
		{
			OutputDebugStringA(debugText);
		}

		std::cout << debugText;
	}

	inline bool IsDebuggerPresent()
	{
		static HINSTANCE hInstKernel32 = GetModuleHandle(TEXT("KERNEL32"));
		if (!hInstKernel32)
			return false;

		static BOOL isDebuggerPresentFunc = (BOOL)GetProcAddress(hInstKernel32, "IsDebuggerPresent");
		if (!isDebuggerPresentFunc)
			return false;

		return isDebuggerPresentFunc == TRUE;
	}

	inline bool MessageOK(const std::string& messageText, const std::string& severityName, SEVERITY severity)
	{
		bool isOK = true;

		UINT msgIcon = Apex::GetMessageBoxIconForSeverity(severity);
		int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_OK | msgIcon | MB_TOPMOST);
		isOK = (buttonClicked == IDOK);

		return isOK;
	}

	inline bool MessageYesNo(const std::string& messageText, const std::string& severityName, SEVERITY severity)
	{
		bool isYes = true;

		UINT msgIcon = Apex::GetMessageBoxIconForSeverity(severity);
		int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_YESNO | msgIcon | MB_TOPMOST);
		isYes = (buttonClicked == IDYES);

		return isYes;
	}

	//----------------------------------------------------------------------------------------------------------------------------
	// Defining the Logging Checks of all severities------------------------------------------------------------------------------

#define LOG_INFO Apex::LogMessage(Apex::INFO, __FILE__, __LINE__).flush()
#define LOG_WARNING Apex::LogMessage(Apex::WARNING,__FILE__,__LINE__).flush()
#define LOG_FATAL Apex::LogMessageFatal(__FILE__,__LINE__).flush()
#define LOG(severity) LOG_##severity

#define LOG_CHECK(condition) \
	if(!(condition)) Apex::LogMessageFatal(__FILE__,__LINE__).flush() << "Check failed: "

}