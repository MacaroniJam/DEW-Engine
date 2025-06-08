#include "Log.h"

namespace DEWEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// Will be coloured appropriately
		// Timestamp: [%T], logger name: %n, and message %v%$
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("DEWENGINE");
		s_ClientLogger = spdlog::stdout_color_mt("APP");
	}

} 
