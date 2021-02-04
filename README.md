# FabiEngine3D
FabiEngine3D is a small game engine for simple 3D games.  
It contains various features such as: asset loading, 2D & 3D rendering, audio, user input, physics, scripting and an engine GUI to work with.  
The engine only uses 2 libraries: OpenGL 4.5 & SDL2. It is written in C++17 and works only on Windows.
## Features
### Asset loading
- Multithreaded PNG texture file loading
- Multithreaded OBJ mesh file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system  
### Rendering
- **3D rendering**: sky, terrain, water, model, billboard
- **2D rendering**: image, text
- **Graphics**: ambient lighting, directional lighting, specular reflections, point lights, shadows, sky reflections, realtime scene reflections, fog
- **Textures**: diffuse, cube, normal, reflection(part), light, height, gui, flare, dudv, displacement, blend, billboard
- **Post processing**: bloom, DOF, motion blur, anti aliasing, sky HDR, lens flare
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
![interface](https://www.linkpicture.com/q/Screenshot_49_23.png)  
The engine GUI is divided into 5 sections:
- Left viewport: editor menus and project settings
- Top viewport: project management & game preview management
- Right viewport: controls & scene editor properties
- Bottom viewport: statistics & logging console
- Mid viewport: 3D display screen
## Folder structures
The engine root directory has 3 folders:
- `bin\`: this folder holds the .exe file and all corresponding DLLs (do **NOT** touch)
- `engine\`: this folder holds all engine resources such as libraries & shaders (do **NOT** touch)
- `user\`: this folder is where all your game assets are stored. It also holds the project files.
## Development order
- **Project management**
  > In the top-viewport you can create, edit, save and delete projects. 1 project = 1 game.
- **Environment editor**
  > This is where you can create environment entities. There are 3 types of environments: sky, terrain, water.
- **Model editor**
  > This is where you can create model entities composed of a mesh, textures, AABBs and other properties.
- **Animation editor**
  > This is where you can create custom animations using keyframe interpolation. Types of animation: translation, rotation, scaling.
- **Billboard editor**
  > This is where you can create billboard entities composed of texture/color/text and other properties.
- **Audio editor**
  > This is where you can create audio entities composed of an audio file.
- **Scene editor**
  > This is where you bring all the created environment, models, animations, billboards and audio together into a scene.
- **Script editor**
  > This is where you define your game logic. There are 3 types of logic: initialization, update, destruction.
- **Project settings**
  > This is where you can setup mostly graphical properties of your game such as shadow quality, reflection quality, etc.
## Project management
You can create, edit/load, save and delete a project. Every project is a different game and must have a unique name. A project has its own folder in the engine "user\projects\" directory. An important note is to **NOT** change anything in this directory! The only directory that you can change is the `user\assets\`folder.
## Environment editor
### Sky
The sky environment is rendered as a **skybox**, which has 6 different textures. You can load these 6 images from `user\assets\textures\cube_maps\`. The cubemap resolutions must be the same and the bit depth must be **24bit**. Image format must be **PNG**. You can also edit some properties: lightness, color, rotation speed.
![sky](https://www.linkpicture.com/q/sky.png)
### Terrain
The terrain environment is generated with a **height map** texture. A terrain can have a **diffuse map** texture, but can also be textured using a **blend mapping**. The R,G,B channels represent different textures. So in total a terrain can be textured with up to 4 different textures! All of these rendered textures can also be improved with **normal mapping**. You can also edit some properties: max height, UV-repeat, lighting.
- **Height map**: grayscale 24bit BMP from `user\assets\textures\height_maps\`
- **Blend map**: colored 24bit PNG from `user\assets\textures\blend_maps\`
- **Diffuse maps**: colored 24bit PNG from`user\assets\textures\diffuse_maps\`
- **Normal maps**: colored 24bit PNG from `user\assets\textures\normal_maps\`  
![terrain](https://www.linkpicture.com/q/Screenshot_46_26.png)
### Water
The water environment is simply a flat plane in 3D space. You can style the water rendering in multiple ways:
- Custom color (RGB)
- Sky & terrain reflection (on/off, only shown when above water surface)
- Water refraction (on/off, **Warning**: huge performance impact!)
- Rippling effect (on/off, **DUDV map** needed: colored 24bit PNG from `user\assets\textures\dudv_maps\`)
- Waves (on/off, **displacement map** needed: grayscale 24bit PNG from `user\assets\textures\displacement_maps\`)
- Specular reflection (on/off, **normal map** needed: colored 24bit PNG from `user\assets\textures\normal_maps\`)  

Properties: position, size, wave height, specular factor & intensity, wave/ripple speed, UV-repeat, color, edge transparency.  
You also have the option to show a created terrain while creating a water environment, mainly for having a reference for the position and size of the water plane.
![water](https://www.linkpicture.com/q/Screenshot_47_19.png)
## Model editor
## Animation editor
## Billboard editor
## Audio editor
## Scene editor
## Script editor
## Project settings
## FabScript
## Game execution
## Miscellaneous
### Best practices
### Performance
### Config file
