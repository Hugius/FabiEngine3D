# Features
### Asset Loading
- Multithreaded PNG texture file loading
- Multithreaded OBJ mesh file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system  
### Rendering
- **3D rendering**: sky, terrain, water, model, billboard
- **2D rendering**: image, text
- **Graphics**: ambient lighting, directional lighting, specular reflections, point lights, shadows, sky reflections, realtime scene reflections, fog
- **Textures**: diffuse, cube, normal, reflection, light, height, gui, flare, dudv, displacement, blend, billboard
- **Post processing**: bloom, DOF, motion blur, anti aliasing, sky HDR, lens flare
### Audio
- Custom music playlist
- 2D audio playback
- 3D audio playback (volume distance, stereo panning)
### Physics
- AABB system
- Collision detection
- Collision response
- Raycasting system
- 3D camera system
- Custom math library
### Miscellaneous
- Keyboard input
- Mouse input
- Custom "FabScript" functional interpreted gameplay programming language.

# Engine Interface
![interface](../images/interface.png)
The engine GUI is divided into 5 sections:
- Left viewport: editor menus and project settings
- Top viewport: project management & game preview management
- Right viewport: controls & scene editor properties
- Bottom viewport: statistics & logging console
- Mid viewport: 3D display screen

# Folder Structures
The engine root directory holds 6 folders and 1 file:
- `binaries\`: holds the **.exe file** and library DLLs (do **NOT** touch).
- `engine_assets\`: holds all **engine resources** (do **NOT** touch).
- `game_assets\`:  holds all your **game resources**.
- `projects\`: holds all of your **projects** (do **NOT** touch).
- `config.fe3d`: technical configuration for game exporting.

# Development Order
- **Project management**
  > In the top-viewport you can create, edit, save and delete projects. 1 project = 1 game.
- **Environment editor**
  > This is where you can create environment entities. There are 3 types of environments: sky, terrain, water.
- **Model editor**
  > This is where you can create model entities composed of a mesh, textures, AABBs and other properties.
- **Animation editor**
  > This is where you can create custom animations using keyframe. Types of animation: translation, rotation, scaling.
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

# Project Management
- You can **create/edit/save/delete** a project in the top viewport.
- 1 project = 1 game.
- Every **project** is a different **game** and must have a **unique** name.
- A project has its own folder in the engine `projects\` directory.
- An important note is to **NOT** change anything in this directory!

# Project Settings
- Every project/game has its own settings.
- All settings will be saved in `projects\<your_project>\game_settings.fe3d`.
- MSAA quality (default: 4). **Range**: 1 to 32.
- Shadow quality (default: 2048). **Range**: 512 to 8192.
- Reflection quality (default: 256). **Range**: 128 to 2048.
- Refraction quality (default: 256). **Range**: 128 to 2048.
- Max audio channels (default: 128). **Range**: 32 to 512.
