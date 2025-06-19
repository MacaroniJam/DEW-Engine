#include "dewpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace DEWEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// Will be coloured appropriately
		// Timestamp: [%T], logger name: %n, and message %v%$
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("DEWEngine");

		// Trace: Print all messages, including debug, info, warn, error, critical
		s_CoreLogger->set_level(spdlog::level::trace); 
		

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace); // Set client logger to trace level (print everything)
	}

} 
