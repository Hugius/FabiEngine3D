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
- **Lighting**: ambient lighting, directional lighting, specular lighting, point lighting, spot lighting
- **Post-Processing**: bloom, DOF, motion blur, anti-aliasing, lens flare, gamma correction
- **Miscellaneous**: shadows, cube reflections, cube refractions, planar reflections, planar refractions fog, sky exposure, anisotropic filtering

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
      └── data (do NOT change)
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

## 5. Terminology

- **String**: a concatenation of characters (example: `Hello123!`)
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
- **Raycasting**: the process of casting a ray from a position towards a direction
- **AABB**: Axis Aligned Bounding Box
- **Collision Detection**: the process of detecting collision between 2 AABBs
- **Collision Response**: the process of responding to collision between 2 AABBs
- **Reference Angle**: a rotational angle converted between 0&deg; and 90&deg;
- **Transformation**: the combination of position/rotation/size
- **FXAA**: Fast Approximate Anti Aliasing
