#include "LogMessage.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdarg.h>
#include <iostream>
#include <stdint.h>

namespace Apex {

	void LogStartup()
	{
		std::string logFileName = "Log/";
		logFileName += "Log";

		std::string defaultLogFile = logFileName + ".txt";

		if (!CreateDirectoryA("Log/", NULL))
		{
		}
	}

	void LogShutdown()
	{
	}

	unsigned int GetMessageBoxIconForSeverity(SEVERITY severity)
	{
		switch (severity)
		{
		case Apex::WARNING:           return MB_ICONEXCLAMATION;
		case Apex::FATAL:             return MB_ICONHAND;
		default:                      return MB_ICONEXCLAMATION;
		}
	};

	LogMessage::LogMessage(SEVERITY severity, const char* fileName, int line)
		: m_Severity(severity), m_FileName(fileName), m_Line(line)
	{
	}

    LogMessage::~LogMessage()
	{
		printLogMessage(m_Severity);
	}

	void LogMessage::printLogMessage(SEVERITY severity)
	{
		std::string messageText;

		if (severity == Apex::INFO)
		{
			Debugf("\n------------------------------------------------------------------------------\n");
			Debugf("\n[%s%s\033[0m]: %s(Line %d): %s\n", SeverityColor[m_Severity], SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
			Debugf("\n------------------------------------------------------------------------------\n");
		}
		else
		{
			if (severity == Apex::WARNING)
			{
			}
			else if (severity == Apex::FATAL)
			{
			}

			bool isDebuggerPresent = (Apex::IsDebuggerPresent() == TRUE);

			if (isDebuggerPresent)
			{
				messageText += "\nWould you like to break and debug?\n";
			}

			messageText += Apex::Stringf("\n[%s]: %s(Line %d): %s\n", Apex::SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());

			Debugf("\n------------------------------------------------------------------------------\n");
			Debugf("\n[%s%s\033[0m]: %s(Line %d): %s\n", Apex::SeverityColor[m_Severity], Apex::SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
			Debugf("\n------------------------------------------------------------------------------\n");

			if (isDebuggerPresent)
			{
				bool isYesNo = Apex::MessageYesNo(messageText, Apex::SeverityNames[m_Severity], severity);

				if (isYesNo)
				{
					__debugbreak();
				}
			}
			else
			{
				Apex::MessageOK(messageText, Apex::SeverityNames[m_Severity], severity);
			}
		}
	}

	LogMessageFatal::LogMessageFatal(const char* fileName, int line)
		: LogMessage(Apex::FATAL, fileName, line)
	{
	}

	LogMessageFatal::~LogMessageFatal()
	{
		printLogMessage(Apex::FATAL);
		exit(0);
	}

    std::string Stringf(const char* messageText, ...)
	{
		char text[2048];
		va_list VAList;
		va_start(VAList, messageText);
		vsnprintf_s(text, 2048, _TRUNCATE, messageText, VAList);
		va_end(VAList);
		text[2047] = '\0';

		return std::string(text);
	}

	void Debugf(const char* messageText, ...)
	{
		char text[2048];
		va_list VAList;
		va_start(VAList, messageText);
		vsnprintf_s(text, 2048, _TRUNCATE, messageText, VAList);
		va_end(VAList);
		text[2047] = '\0';

		if (IsDebuggerPresent())
		{
			OutputDebugStringA(text);
		}

		std::cout << text;
	}

	bool IsDebuggerPresent()
	{
		typedef BOOL(__stdcall IsAvailable)();

		static HINSTANCE hInstKernel32 = GetModuleHandle(TEXT("KERNEL32"));
		if (!hInstKernel32)
			return false;

		static IsAvailable* isDebuggerPresentFunc = (IsAvailable*)GetProcAddress(hInstKernel32, "IsDebuggerPresent");
		if (!isDebuggerPresentFunc)
			return false;

		static BOOL isDebuggerAvailable = isDebuggerPresentFunc();

		return isDebuggerAvailable == TRUE;
	}

	bool MessageOK(const std::string& messageText, const std::string& severityName, SEVERITY severity)
	{
		bool isOK = true;

		UINT msgIcon = Apex::GetMessageBoxIconForSeverity(severity);
		int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_OK | msgIcon | MB_TOPMOST);
		isOK = (buttonClicked == IDOK);

		return isOK;
	}

	bool Apex::MessageYesNo(const std::string& messageText, const std::string& severityName, SEVERITY severity)
	{
		bool isYes = true;

		UINT msgIcon = Apex::GetMessageBoxIconForSeverity(severity);
		int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_YESNO | msgIcon | MB_TOPMOST);
		isYes = (buttonClicked == IDYES);

		return isYes;
	}

}