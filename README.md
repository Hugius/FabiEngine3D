# FabiEngine3D
FabiEngine3D is a small game engine for simple 3D games.  
It contains various features such as: asset loading, 2D & 3D rendering, audio, user input, physics, scripting and an engine GUI to work with.  
The engine only uses 2 libraries: OpenGL 4.5 & SDL2. It is written in C++17 and works only on Windows.
## Features
### Asset loading
- Multithreaded PNG texture file loading
- Multithreaded OBJ model file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system  
### Rendering
- **3D rendering**: sky, terrain, water, model, billboard
- **2D rendering**: image, text
- **Graphics**: ambient lighting, directional lighting, specular reflections, point lights, shadows, sky reflections, realtime scene reflections, fog
- **Textures**: diffuse mapping, normal mapping, reflection(part) mapping, light mapping
- **Post processing**: bloom, DOF / distant blur, motion blur, anti aliasing, sky HDR, lens flare
### Audio
- Custom music playlist
- 2D audio playback
- 3D audio playback
### Input
- Keyboard input
- Mouse input
- Controller input
### Physics
- AABB system
- Collision detection
- Collision response
- Raycasting system
- 3D camera system
- Custom math library
### Scripting
- Custom "FabScript" interpreted language
- Types: integer, decimal, string, boolean, vec3
- Functional programming
- Core engine communication
- Variables & lists
- Looping
- Arithmetic operations: increase, decrease, multiply, divide
- Logical operations: if, elif, else, is, not, and or
## Engine interface
![interface](https://www.linkpicture.com/q/Screenshot_45_29.png)  
The engine GUI is divided into 5 sections:
- Left viewport: editor menus and project settings
- Top viewport: project management & game preview management
- Right viewport: controls & scene editor properties
- Bottom viewport: statistics & logging console
- Mid viewport: 3D display screen
## Folder structures
The engine root directory has 3 folders:
- "bin\": this folder holds the .exe file and all corresponding DLLs (do NOT touch)
- "engine\": this folder holds all engine resources such as libraries & shaders (do NOT touch)
- "user\": this folder is where all your game assets are stored. It also holds the project files.
## Development order
## Scripting system
## Best practices
