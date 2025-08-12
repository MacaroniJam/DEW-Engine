#pragma once

// Windows only thing
#ifdef DEW_PLATFORM_WINDOWS

	// Trying to build the DLL for DEW Engine
	#ifdef DEW_BUILD_DLL

		// If we are building the DLL, we need to export the symbols from the DLL
		#define DEW_API __declspec(dllexport)
	#else
		// If we are not building the DLL, we need to import the symbols from the DLL
		#define DEW_API __declspec(dllimport)
	#endif

#else
	#error "DEW Engine only supports Windows platform for now."
#endif

//Used for debugging purposes
#ifdef DEW_DEBUG
	#define DEW_ENABLE_ASSERTS // Enable asserts in debug mode
#endif

#ifdef DEW_ENABLE_ASSERTS
	// Checks a condition x and logs a message. If it fails, a break point is added for debugging.
	#define DEW_ASSERT(x, ...) { if (!(x)) { DEW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define DEW_CORE_ASSERT(x, ...) { if (!(x)) { DEW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define DEW_ASSERT(x, ...)
	#define DEW_CORE_ASSERT(x, ...)
#endif

// Shift the binary representation of 1 to the left by x positions
// 1 = 01 (1), 1 << 0 = 10 (2), 1 << 1 = 100 (4), 1 << 2 = 1000 (8) etc.
#define BIT(x) (1 << x) 

// Macro for binding event functions to be used by dispatcher
#define DEW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
