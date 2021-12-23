# General Information

## 1. Features

### 1.1 Assets

- Multithreaded OBJ file loading
- Multithreaded PNG file loading
- Multithreaded BMP file loading
- Multithreaded WAV file loading
- Efficient cache management

### 1.2 Rendering

- **3D Rendering**: sky, terrain, water, model, billboard
- **2D Rendering**: image, text
- **Textures**: blend, cube, diffuse, displacement, DUDV, emission, flare, height, image, normal, reflection, specular
- **Lighting**: ambient lighting, directional lighting, specular lighting, point lighting, spot lighting
- **Post Processing**: bloom, DOF, motion blur, anti aliasing, lens flare, gamma correction
- **Miscellaneous**: shadows, cube reflections, planar reflections, fog, sky exposure, anisotropic filtering

### 1.3 Physics

- 3D AABB system
- 3D collision detection system
- 3D collision response system
- 3D raycasting system
- 3D camera system

### 1.4 Animations

- 2D sprite animations
- 3D mesh animations

### 1.5 Audio

- 2D sounds
- 3D sounds

### 1.6 Scripting

- Custom scripting language
- Engine API
- Math API

### 1.7 Networking

- Central networking server
- Multiple networking clients
- TCP messaging
- UDP messaging

### 1.8 Miscellaneous

- Engine GUI
- Editors
- Realtime statistics
- Realtime logging
- Keyboard input
- Mouse input

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
        └── font
        └── mesh
        └── texture
          └── blend_map
          └── cube_map
          └── diffuse_map
          └── displacement_map
          └── dudv_map
          └── emission_map
          └── flare_map
          └── height_map
          └── normal_map
          └── reflection_map
          └── specular_map
      └── data (do NOT touch)
      └── saves (do NOT touch)
      └── scripts (do NOT touch)
      └── worlds (do NOT touch)
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
      - `font\`: contains all project font files
      - `mesh\`: contains all project mesh files
      - `texture\`: contains all project texture files
    - `data\`: contains all project editor data
    - `saves\`: contains all project save files
    - `worlds\`: contains all project world files
    - `scripts\`: contains all project script files
- `~\dev\`: contains the engine development systems
- `~\doc\`: contains the engine documentation
- `~\src\`: contains the engine source code

## 3. Engine Interface

- **Left Viewport**: editors
- **Top Viewport**: project management & preview management
- **Right Viewport**: controls & properties
- **Bottom Viewport**: statistics & logging
- **Mid Viewport**: 3D display screen

## 4. Terminology

- **String**: a concatenation of characters(example: `hello123!@#`)
- **Decimal3**: a collection of 3 decimals
- **Decimal2**: a collection of 2 decimals
- **Decimal**: a floating point number (example: `3.1415`)
- **Integer**: a number (example: `3`)
- **Boolean**: can only be `true` or `false`
- **Enumeration**: a limited amount of types (example: MALE, FEMALE, OTHER)
- **Vector**: a mathematical element that has both a direction and a magnitude
- **Normalized Vector**: a vector with magnitude of exactly 1
- **Vertex**: a coordinate (XYZ) in 3D mesh
- **Fragment**: every pixel that can possibly end up on your screen
- **UV Coordinate**: a coordinate (XY) which used for mapping a 2D texture onto a 3D mesh
- **Normal Vector**: a normalized vector that points in the opposite direction of a surface which is used for lighting calculations
- **First Person View**: everything is viewed directly through the "eyes" of the camera
- **Third Person View**: everything is viewed indirectly from a distance
- **Global Illumination**: an indirect form of global lighting
- **Gimbal Lock**: incorrect rotation as a result of 2 parallel rotation axes
- **RGB**: Red Green Blue
- **Mouse**: the physical peripheral known as "the mouse"
- **Cursor**: the pointer within FabiEngine3D that is moved using the mouse
- **Wireframe**: a rendering mode that only draws lines/wires between all vertices
- **Face Culling**: an optimization technique where non-visible vertices are not rendered
- **Instancing**: an optimization technique that is efficient for rendering a lot of the same meshes
- **Raycasting**: the process of casting a ray from a position towards a direction
- **AABB**: Axis Aligned Bounding Box
- **Collision Detection**: the process of detecting collision between 2 AABBs
- **Collision Response**: the process of responding to collision between 2 AABBs
- **Reference Angle**: a rotational angle converted between 0&deg; and 90&deg;
- **Transformation**: the combination of position/rotation/size
- **FXAA**: Fast Approximate Anti Aliasing
