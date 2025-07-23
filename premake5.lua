-- This file is used to generate project files for the DEWEngine using Premake5.
workspace "DEWEngine"
	architecture "x64" -- Target platform
	startproject "Sandbox" -- The project that will be opened by default when the workspace is loaded

	configurations{
		"Debug", -- Full on debug code that we use to develop everything developed
		"Release", -- Optimized code with alot of debugging info stripped yet not necessarily for the public
		"Dist" -- Everything stripped, optimized and ready for public release
	}

-- Define the output directory for the compiled binaries
	-- The output directory will be structured as: bin/<configuration>-<system>-<architecture>
	-- using the tokens %{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture} to create the path
	-- where %{cfg.buildcfg} is the build configuration (Debug, Release, Dist),
	-- %{cfg.system} is the system (Windows, Linux, etc.),
	-- and %{cfg.architecture} is the architecture (x86, x64, etc.)
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
	-- Creating Lua lookup table for IncludeDir
IncludeDir = {} -- create a table known as IncludeDir
IncludeDir["GLFW"] = "DEWEngine/vendor/GLFW/include" -- Added GLFW to table, key = "GLFW", value = file path

include "DEWEngine/vendor/GLFW" -- Include GLFW premake file. Its file contents are copied and pasted to this file



project "DEWEngine"
	location "DEWEngine" -- Folder where the project files will be generated
	kind "SharedLib" -- Type of project, in this case a DLL
	language "C++"
	buildoptions {"/utf-8"} 

	-- Output directory for the compiled binaries
		-- This will create a directory structure like bin/Debug-Windows-x64/DEWEngine
		-- .. outputdir .. is a string concatenation that appends the output directory to the base path
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 

	objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- Intermediate directory for object files

	pchheader "dewpch.h" -- Precompiled header file
	pchsource "DEWEngine/src/dewpch.cpp" -- Source file for the precompiled header

	files{
		"%{prj.name}/src/**.h", -- Recursively search for (which mean **) and include all header files in the src directory
		"%{prj.name}/src/**.cpp" -- Recursively search for and include all cpp files in the src directory
	}

	-- Include directories for the project
	includedirs {
		"%{prj.name}/src", -- Include the src directory of the DEWEngine project
		"%{prj.name}/vendor/spdlog/include", -- Include the spdlog library for logging
		"%{IncludeDir.GLFW}" -- Include the GLFW library directory from the IncludeDir table
	}

	links{
		"GLFW", -- Link the GLFW library to the DEWEngine project
		"opengl32.lib" -- Link the OpenGL library, which is required for rendering
	}


	filter "system:windows"
		cppdialect "C++17" -- Use C++17 compile flag as standard
		staticruntime "On" -- Linking runtime libraries staticly
		systemversion "latest" -- Use the latest version of the Windows SDK, uses another SDK if line is not used

		-- Define preprocessor directives for Windows platform and DLL export
		defines{
			"DEW_PLATFORM_WINDOWS",
			"DEW_BUILD_DLL"
		}

		-- Commands to run after the build is complete
		postbuildcommands{ 

			-- Copy the compiled DLL to the Sandbox project directory
				-- This uses the COPY command to copy the built DLL to the Sandbox project directory
				-- The %{cfg.buildtarget.relpath} token is used to get the relative path of the built target
				-- The "../bin/" .. outputdir .. "/Sandbox" is the target directory where the DLL will be copied
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	

	filter "configurations:Debug"
		defines "DEW_DEBUG" -- Define the DEW_DEBUG preprocessor directive for Debug configuration
		buildoptions "/MDd" -- Link against the multi-threaded debug DLL runtime library
		symbols "On" -- Enable debug symbols for the Debug configuration

	filter "configurations:Release"
		defines "DEW_RELEASE" -- Define the DEW_RELEASE preprocessor directive for Release configuration
		buildoptions "/MD" -- Link against the multi-threaded DLL runtime library
		optimize "On" -- Enable optimizations for the Release configuration

	filter "configurations:Dist"
		defines "DEW_DIST" -- Define the DEW_DIST preprocessor directive for Dist configuration
		buildoptions "/MD" 
		optimize "On" 




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- executable application
	language "C++"
	buildoptions {"/utf-8"}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	
	includedirs {
		"DEWEngine/vendor/spdlog/include",
		"DEWEngine/src"
	}

	links{
		"DEWEngine" -- Link the Sandbox project with the DEWEngine library
	}

	filter "system:windows"
		cppdialect "C++17" 
		staticruntime "On" 
		systemversion "latest" 

		
		defines{
			"DEW_PLATFORM_WINDOWS"
		}

	
	filter "configurations:Debug"
		defines "DEW_DEBUG" 
		buildoptions "/MDd"
		symbols "On" 

	filter "configurations:Release"
		defines "DEW_RELEASE"
		buildoptions "/MD"
		optimize "On" 

	filter "configurations:Dist"
		defines "DEW_DIST"
		buildoptions "/MD"
		optimize "On" 

