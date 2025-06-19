#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // Spdlog output stream for logging custom types like our events etc.

namespace DEWEngine {
	class DEW_API Log
	{

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; // Core logger for the engine
		static std::shared_ptr<spdlog::logger> s_ClientLogger; // Client logger for the application

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	};


}

// DEWEngine Log Macros
// MacroName(...) Macro can take any number of arguments
// ::Namespace::LogClass::GetLogger->LogLevel (spaced out from macro name for clarity)
// All arguments passed in Macro will replace __VA_ARGS__

// Core log macros
#define DEW_CORE_TRACE(...)      ::DEWEngine::Log::GetCoreLogger()->trace(__VA_ARGS__) // trace message
#define DEW_CORE_INFO(...)       ::DEWEngine::Log::GetCoreLogger()->info (__VA_ARGS__) // info message
#define DEW_CORE_WARN(...)       ::DEWEngine::Log::GetCoreLogger()->warn (__VA_ARGS__) // warning message
#define DEW_CORE_ERROR(...)      ::DEWEngine::Log::GetCoreLogger()->error (__VA_ARGS__) // error message
#define DEW_CORE_CRITICAL(...)   ::DEWEngine::Log::GetCoreLogger()->critical (__VA_ARGS__) // critical message

// Client log macros
#define DEW_TRACE(...)           ::DEWEngine::Log::GetClientLogger()->trace(__VA_ARGS__) // trace message
#define DEW_INFO(...)            ::DEWEngine::Log::GetClientLogger()->info (__VA_ARGS__) // info message
#define DEW_WARN(...)            ::DEWEngine::Log::GetClientLogger()->warn (__VA_ARGS__) // warning message
#define DEW_ERROR(...)           ::DEWEngine::Log::GetClientLogger()->error (__VA_ARGS__) // error message
#define DEW_CRITICAL(...)        ::DEWEngine::Log::GetClientLogger()->critical (__VA_ARGS__) // critical message

