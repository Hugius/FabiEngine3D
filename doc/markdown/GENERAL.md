# General Information

## 1. Features

### 1.1 Assets

- Multithreaded OBJ file loading
- Multithreaded TGA file loading
- Multithreaded WAV file loading
- Efficient cache management

### 1.2 Rendering

- **Drawables**: sky, terrain, water, model, quad3D, text3D, AABB, quad2D, text2D
- **Textures**: blend, cube, diffuse, dudv, emission, flare, font, height, normal, reflection, refraction, specular
- **Lighting**: ambient lighting, directional lighting, specular lighting, point lighting, spot lighting, cube reflections, cube refractions, planar reflections, planar refractions, shadows
- **Post-processing**: bloom, DOF, motion blur, anti-aliasing, lens flare, gamma correction
- **Miscellaneous**: fog, sky exposure, anisotropic filtering, normal mapping, water effects

### 1.3 Physics

- 3D camera system
- 3D AABB system
- 3D collision detection system
- 3D collision response system
- 3D raycast detection system
- 3D raycast response system

### 1.4 Animations

- 3D mesh animations
- 2D texture animations

### 1.5 Audio

- 3D sounds
- 2D sounds

### 1.6 Scripting

- Custom scripting language
- Engine API
- Math API
- Miscellaneous API

### 1.7 Networking

- Server
- Clients
- TCP messaging
- UDP messaging
- Multithreading

### 1.8 Miscellaneous

- Mouse input
- Keyboard input
- Engine GUI
- Editors
- Realtime statistics
- Realtime logging

## 2. Folder Structure

```text
~
└── app
  └── binaries (do NOT change)
  └── engine (do NOT change)
  └── projects
    └── <your_project>
      └── assets
        └── audio
        └── image
          └── misc
            └── flare_map
          └── model
            └── diffuse_map
            └── emission_map
            └── normal_map
            └── reflection_map
            └── refraction_map
            └── specular_map
          └── quad2d
            └── diffuse_map
          └── quad3d
            └── diffuse_map
            └── emission_map
          └── sky
            └── cube_map
          └── terrain
            └── blend_map
            └── diffuse_map
            └── height_map
            └── normal_map
          └── text2d
            └── font_map
          └── text3d
            └── font_map
          └── water
            └── dudv_map
            └── height_map
            └── normal_map
        └── mesh
      └── domain (do NOT change)
      └── saves (do NOT change)
      └── scripts (do NOT change)
      └── worlds (do NOT change)
└── dev (do NOT change)
└── doc (do NOT change)
└── src (do NOT change)
```

## 3. Executable

&#8594; You can start the engine by running `~\app\binaries\fe3d.exe` &#8592;

## 4. Engine Interface

- **Center Viewport**: 3D display screen
- **Left Viewport**: editors
- **Top Viewport**: project/preview management
- **Right Viewport**: controls & properties
- **Bottom Viewport**: statistics & logging
