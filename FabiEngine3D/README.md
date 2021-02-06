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
- **Textures**: diffuse, cube, normal, reflectionpart, light, height, gui, flare, dudv, displacement, blend, billboard
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
![interface](engine/readme/interface.png)  
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
- `user\`: this folder is where all your game assets are stored. It also holds the project files

## Development order
- **Project management**
  > In the top-viewport you can create, edit, save and delete projects. 1 project = 1 game
- **Environment editor**
  > This is where you can create environment entities. There are 3 types of environments: sky, terrain, water
- **Model editor**
  > This is where you can create model entities composed of a mesh, textures, AABBs and other properties
- **Animation editor**
  > This is where you can create custom animations using keyframe. Types of animation: translation, rotation, scaling
- **Billboard editor**
  > This is where you can create billboard entities composed of texture/color/text and other properties
- **Audio editor**
  > This is where you can create audio entities composed of an audio file
- **Scene editor**
  > This is where you bring all the created environment, models, animations, billboards and audio together into a scene
- **Script editor**
  > This is where you define your game logic. There are 3 types of logic: initialization, update, destruction
- **Project settings**
  > This is where you can setup mostly graphical properties of your game such as shadow quality, reflection quality, etc

## Project management
- You can create, edit/load, save and delete a project
- Every **project** is a different **game** and must have a **unique** name
- A project has its own folder in the engine "user\projects\" directory
- An important note is to **NOT** change anything in this directory!
- The only directory that you can change is the `user\assets\`folder

## Environment editor
### Sky
![sky](engine/readme/sky_editor.png)
- The sky environment is rendered as a **skybox**, which has 6 different texturs
- You can load these 6 images from `user\assets\textures\cube_maps\`
- The cubemap resolutions must be the same and the bit depth must be **24bit**
- Image format must be **PNG**
- Properties include: lightness, color, rotation speed
### Terrain
![terrain](engine/readme/terrain_editor.png)
- The terrain environment is generated with a **height map** texture
- A terrain can have a **diffuse map** texture, but can also be textured using a **blend mapping**
- In total a terrain can be textured with up to 4 different textures!
- All of these rendered textures can be improved with **normal mapping**
- Properties include: max height, UV-repeat, lighting
- **Height map**: grayscale 24bit BMP file from `user\assets\textures\height_maps\`
- **Blend map**: colored 24bit PNG file from `user\assets\textures\blend_maps\`
- **Diffuse maps**: colored 24bit PNG file from `user\assets\textures\diffuse_maps\`
- **Normal maps**: colored 24bit PNG file from `user\assets\textures\normal_maps\`
### Water
![water](engine/readme/water_editor.png)
- The water environment is simply a **flat plane** in 3D space
- Properties include: position, size, wave height, specular factor & intensity, wave/ripple speed, UV-repeat, color, edge transparency
- You also have the option to show a created terrain while creating a water environment, mainly for having a reference
- Custom color (RGB)
- Sky & terrain reflection (on/off, only shown when above water surface)
- Water refraction (on/off, **Warning**: huge performance impact!)
- Rippling effect (on/off, **DUDV map** needed: colored 24bit PNG from `user\assets\textures\dudv_maps\`)
- Waves (on/off, **displacement map** needed: grayscale 24bit PNG from `user\assets\textures\displacement_maps\`)
- Specular reflection (on/off, **normal map** needed: colored 24bit PNG from `user\assets\textures\normal_maps\`)    

## Model editor
![model](engine/readme/model_editor.png)
- You can create, edit, delete models that can be added to a scene or placed with scripting
- A model must **at least** consist of a mesh
- Textures can be added to the model as well as a custom color
- Properties include: size, culling, alpha removal, instanced rendering, color, UV-repeat, level of detail
- Lighting: specular reflection (+ factor & intensity), lightness, shadowed, sky reflection, scene reflection
- You can also add 1 or more **AABBs** to the model. Every individual box has a position and size. These AABBs are bound to the model's transformation
### Normal mesh
- **Mesh**: OBJ format mesh file from  `user\assets\meshes`
- **Diffuse map**: colored 24bit PNG file from `user\assets\textures\diffuse_maps\`
- **Light map**: colored 24bit PNG file from `user\assets\textures\light_maps\`
- **Reflectionpart map**: colored 24bit PNG file from `user\assets\textures\reflection_maps\`
- **Normal map**: colored 24bit PNG file from `user\assets\textures\normal_maps\`
### Multitextured/multiparted mesh
- A mesh can consist of **multiple parts** (including textures for every part)
- In the **.obj** file, you need to specify when a certain part of vertices starts
- You can start a mesh part by writing `FE3D_PART <name>` in the OBJ file
- You can bind a **diffuse** map to the part by writing `FE3D_DIFFUSE_MAP <path><filename>` on the line after
- You can bind a **light** map to the part by writing `FE3D_LIGHT_MAP <path><filename>` on the line after
- You can bind a **reflectionpart** map to the part by writing `FE3D_REFLECTION_MAP <path><filename>` on the line after
- You can bind a **normal** map to the part by writing `FE3D_NORMAL_MAP <path><filename>` on the line after

## Animation editor
![model](engine/readme/animation_editor.png)
- You can create, edit, delete animations that can be appied to **models** during gameplay or in the scene editor
- You can select a **preview model** for the animation playback
- An animation consists of 1 or more **keyframes**
- Every keyframe has a different **target** transformation
- Every keyframe has a different animation **speed**, with 2 types to choose from: **linear & exponential**
- Rotational transformations can each have a different **rotation origin**
- If the model has **multiple parts**, each part has its own transformation every keyframe
- The **last** animation keyframe should be the same as the **initial** frame

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
