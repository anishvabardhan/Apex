#pragma once

#include "LogMessage.h"

namespace Apex {

	void EngineStartup()
	{
		LogStartup();
		LOG_INFO << "Application Initialised!!";
	}

	void EngineUpdate()
	{

	}

	void EngineShutdown()
	{
		LOG_INFO << "Application Shutdown!!";
		LogShutdown();
	}
}