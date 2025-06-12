# DEW-Engine
**Description:** This project will focus on me learning how to build a game engine using [The Chrono Game Engine Playlist on Youtube](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=GPZ5s0109yT-QrVI)

## .exes/Sub-Modules
Logging System: [spdlog](https://github.com/gabime/spdlog)
Project Generation: [Premake](https://github.com/premake/premake-core)

## Notes
- We are using multiple renderers so to make it simple we are going to implement render API abstraction to avoid conflicts yet we still need to be render-API specific.

- Even though we will be building our engine with C++, we still want to implement a higher-level language like C# and Lua...(ew).

- For now, we will focus on Windows and OpenGl but we are still abstract for future aspects.

- We want to build our engine into a DLL and make an exe. After that, we link our engine to the exe file.

- Output Directory: $(SolutionDir)bin\$(Configuration)-$(Platform)\$(ProjectName)\ So this file path, specifically bin stores all of our stuff, including binaries, libraries and project files.
- Intermediate Directory: $(SolutionDir)bin-int\$(Configuration)-$(Platform)\$(ProjectName)\ So this file path is for older files like obj files that are created after compilation.

- Sandbox will be our .exe and DEWEngine will be our .dll

- For Logging, we will add the [spdlog](https://github.com/gabime/spdlog) as a submodule. All third-party libraries will be in the "vendor" folder in the DEWEngine folder.

- We made the log messages function as Macros to give us the ability to strip the code from distribution builds.

- For generating project files for different platforms we will be using [Premake](https://github.com/premake/premake-core) which takes advantage of Lua...EW!!
  - For Premake we will make another vendor folder in which we will create a bin folder to add the exe to, however this is for the entire solution as opposed for just the DEWEngine Solution alone.

## Elements of our Game Engine
- [Entry Point](#entry-point)
- [Application Layer](#application-layer)
- [Window Layer](#window-layer)
  - [Inputs](#inputs)
  - [Events](#events)
- [Renderer](#renderer)
- [Render API Abstraction](#render-api-abstraction)
- [Debugging Support](#debugging-support)
- [Scripting Languague](#scripting-language)
- [Memory Systems](#memory-systems)
- [Entity-Component System (ECS)](#entity-component-system-(ecs))
- [Physics](#physics)
- [File I/O](#file-i/o)

  ## Entry Point
  **Notes**
  - Creating a DEWEngine.h to be used by DEWEngine Applications
  - EntryPoint.h creates the app by calling the CreateApplication() function in SanboxApp and it will call the Run() function inside Application.h that will execute the Run function in Application.cpp. After its used has lasted, it will be deleted by EntryPoint.h.
