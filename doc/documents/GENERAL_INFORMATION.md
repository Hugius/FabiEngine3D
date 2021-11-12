# General Information

## Features

### Asset Loading

- Multithreaded OBJ mesh file loading
- Multithreaded PNG texture file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system

### Rendering

- **3D rendering**: sky, terrain, water, model, billboard
- **2D rendering**: image, text
- **Textures**: blend, cube, diffuse, displacement, dudv, emission, flare, height, image, normal, reflection, specular
- **Graphics**: ambient lighting, directional lighting, specular lighting, point lighting, spot lighting, shadows, cube reflections, planar reflections, fog, skyHDR
- **Post processing**: bloom, DOF, motion blur, anti-aliasing, lens flare

### Audio

- Custom music playlist
- 2D audio playback
- 3D audio playback

### Physics

- 3D AABB system
- 3D Collision detection system
- 3D Collision response system
- 3D Raycasting system
- 3D camera system
- Custom math library

### Networking

- Central networking server
- Multiple networking clients
- TCP messaging
- UDP messaging

### Miscellaneous

- Engine GUI
- Realtime statistics
- Realtime logging console
- Keyboard input
- Mouse input
- Custom interpreted gameplay programming language ("FabScript")

## Entry Point

> You can start the engine by running `~\app\binaries\fe3d.exe`

## Folder Structure

### Overview

```text
~
└── app
  └── binaries (do NOT touch)
  └── engine (do NOT touch)
  └── game
    └── my_game
      └── assets
        └── audio
        └── fonts
        └── meshes
        └── textures
          └── blend_maps
          └── cube_maps
          └── diffuse_maps
          └── displacement_maps
          └── dudv_maps
          └── emission_maps
          └── flare_maps
          └── height_maps
          └── image_maps
          └── normal_maps
          └── reflection_maps
          └── specular_maps
      └── data (do NOT touch)
      └── saves (do NOT touch)
      └── scenes (do NOT touch)
      └── scripts (do NOT touch)
└── dev (do NOT touch)
└── doc (do NOT touch)
└── src (do NOT touch)
```

### Explanation

- `~\app\`: contains the executable engine application.
  - `binaries\`: contains the `.exe` file
  - `engine\`: contains runtime engine files
  - `game\`: contains all your projects
    - `assets\`: contains all project assets
    - `data\`: contains all project editor data
    - `saves\`: contains all project save files
    - `scenes\`: contains all project scene files
    - `scripts\`: contains all project script files
- `~\dev\`: contains the engine development systems.
- `~\doc\`: contains the engine documentation.
- `~\src\`: contains the engine source code.

## Engine Interface

<img src="doc/images/engine.png" width="100%"/>

- Left viewport: editor menus and project settings
- Top viewport: project management & game preview management
- Right viewport: controls & scene editor properties
- Bottom viewport: statistics & logging console
- Mid viewport: 3D display screen

## Development Order

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

## Project Management

- You can **create/edit/save/delete** a project in the top viewport.
- 1 project = 1 game.
- Every **project** is a different **game** and must have a **unique** name.
- A project has its own folder in the engine `projects\` directory.
- An important note is to **NOT** change anything in this directory!

## Project Settings

- Every project/game has its own settings file.
- All settings will be saved in `projects\<your_project>\settings.fe3d`.
- FXAA (default: ON). **Range**: ON or OFF.
- Shadow quality (default: 2048). **Range**: 512 to 8192.
- Reflection quality (default: 256). **Range**: 128 to 2048.
- Refraction quality (default: 256). **Range**: 128 to 2048.
- Max audio channels (default: 128). **Range**: 32 to 512.
