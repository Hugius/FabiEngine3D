# General Information

## 1. Features

### 1.1 Asset Loading

- Multithreaded OBJ mesh file loading
- Multithreaded PNG texture file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system

### 1.2 Rendering

- **3D Rendering**: sky, terrain, water, model, billboard
- **2D Rendering**: image, text
- **Textures**: blend, cube, diffuse, displacement, dudv, emission, flare, height, image, normal, reflection, specular
- **Graphics**: ambient lighting, directional lighting, specular lighting, point lighting, spot lighting, shadows, cube reflections, planar reflections, fog, sky exposure
- **Post Processing**: bloom, DOF, motion blur, anti-aliasing, lens flare

### 1.3 Audio

- Custom music playlist
- 2D audio playback
- 3D audio playback

### 1.4 Physics

- 3D AABB system
- 3D Collision detection system
- 3D Collision response system
- 3D Raycasting system
- 3D camera system
- Custom math library

### 1.5 Networking

- Central networking server
- Multiple networking clients
- TCP messaging
- UDP messaging

### 1.6 Miscellaneous

- Engine GUI
- Realtime statistics
- Realtime logging
- Keyboard input
- Mouse input
- Custom interpreted programming language ("FabScript")

## 2. Folder Structure

> You can start the engine by running `~\app\binaries\fe3d.exe`

### 2.1 Overview

```text
~
└── app
  └── binaries (do NOT touch)
  └── engine (do NOT touch)
  └── projects
    └── <your_project>
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

### 2.2 Explanation

- `~\app\`: contains the engine application
  - `binaries\`: contains the engine executable
  - `engine\`: contains runtime engine files
  - `projects\`: contains all your projects
    - `assets\`: contains all project assets
      - `audio\`: contains all project audio files
      - `fonts\`: contains all project font files
      - `meshes\`: contains all project mesh files
      - `textures\`: contains all project texture files
    - `data\`: contains all project editor data
    - `saves\`: contains all project save files
    - `scenes\`: contains all project scene files
    - `scripts\`: contains all project script files
- `~\dev\`: contains the engine development systems
- `~\doc\`: contains the engine documentation
- `~\src\`: contains the engine source code

## 3. Engine Interface

<img src="images/engine.png" width="100%"/>

- **Left Viewport**: editors & settings
- **Top Viewport**: project management & preview management
- **Right Viewport**: controls & properties
- **Bottom Viewport**: statistics & logging
- **Mid Viewport**: 3D display screen

## 3. Terminology

- **Boolean**: can only be `true` or `false`
- **Integer**: a number (example: `3`)
- **Decimal**: a floating point number (example: `3.1415`)
- **Vector2**: a collection of 2 decimals
- **Vector3**: a collection of 3 decimals
- **String**: a concatenation of characters(example: `hello123!@#`)
