#pragma once

#include <string>
#include <queue>
#include <vector>

namespace Apex {

	//----------------------------------------------------------------------------------------------

	struct LogMsg
	{
		std::string text;
	};

	//----------------------------------------------------------------------------------------------

	typedef void (*LogCallback)(const LogMsg& msg);

	//----------------------------------------------------------------------------------------------
	// SystemFunctions

	void LogStartup();
	void LogShutdown();
	void LogPrint(const char* format, ...);
	void LogFLush();

	//----------------------------------------------------------------------------------------------
	//Class Declaration

	class Logger {
		std::queue<std::string> m_LogQueue;
		std::vector<LogCallback> m_Sinks;
	public:
		//----------------------------------------------------------------------------------------------
		//Constructors/Destructors

		Logger();
		~Logger(); 

		//----------------------------------------------------------------------------------------------
		//Methods

		void AddSink(LogCallback cb);
		void RemoveSink(LogCallback cb);
		void AddLogMessage(const std::string& msg);
		void Flush();

		//----------------------------------------------------------------------------------------------
		//Static Methods

		static void LogToFile(const LogMsg& msg);
		static Logger* CreateInstance();
		static void DestroyInstance();
	};

}