# DEW-Engine
**Description:** This project will focus on me learning how to build a game engine using [The Chrono Game Engine Playlist on Youtube](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=GPZ5s0109yT-QrVI)

## Notes
- We are using multiple renderers so to make it simple we are going to implement render API abstraction to avoid conflicts yet we still need to be render-API specific.

- Even though we will be building our engine with C++, we still want to implement a higher-level language like C# and Lua...(ew).

- For now, we will focus on Windows and OpenGl but we are still abstract for future aspects.

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

