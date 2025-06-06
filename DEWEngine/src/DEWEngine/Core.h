#pragma once

// Windows only thing
#ifdef DEW_PLATFORM_WINDOWS

	// Trying to build the DLL for DEW Engine
	#ifdef DEW_BUILD_DLL

		// If we are building the DLL, we need to export the symbols
		#define DEW_API __declspec(dllexport)
	#else
		// If we are not building the DLL, we need to import the symbols
		#define DEW_API __declspec(dllimport)
	#endif

#else
	#error "DEW Engine only supports Windows platform for now."

#endif