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

// Shift the binary representation of 1 to the left by x positions
// 1 = 01 (1), 1 << 0 = 10 (2), 1 << 1 = 100 (4), 1 << 2 = 1000 (8) etc.
#define BIT(x) ( 1 << x) 