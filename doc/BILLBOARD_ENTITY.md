# Billboard Entity

## 1. General

- The billboard entity is a 2D quad in 3D space.
- Instead of a solid quad, the texture of the billboard entity can be transparent text (based on a font).
- Billboard entities are not affected by shadows or lighting.

## 2. Resources

- Font
- Diffuse map
- Emission map

## 3. Properties

### 3.1 `string`

- **Text Content**: the text content of the billboard entity
  - Constraints: none
- **Diffuse Map Path**: the path of the diffuse map file
  - Constraints: none
- **Emission Map Path**: the path of the emission map file
  - Constraints: none
- **Font Path**: the path of the font file
  - Constraints: none

### 3.2 `vector3`

- **Position**: the XYZ position of the mesh
  - Constraints: none
- **Rotation**: the XYZ rotation of the mesh
  - Constraints: between `0.0` and `360.0`
- **Position Target**: the target XYZ position of the mesh
  - Constraints: none
- **Rotation Target**:  the target XYZ rotation of the mesh
  - Constraints: between `0.0` and `360.0`
- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` to `1.0`

### 3.3 `vector2`

- **Size**: the XY size of the mesh
  - Constraints: at least `0.0`
- **Size Target**: the target XY size of the mesh
  - Constraints: at least `0.0`

### 3.4 `decimal`

- **Emission Intenstiy**: the intensity of the emission map
  - Constraints: at least `0.0`
- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Constraints: at least `0.0`
- **Rotation Target Speed**: the speed with which the mesh rotates to the target rotation
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated
  - Constraints: at least `0.0`
- **Lightness**: the lightness multiplier of the mesh
  - Constraints: at least `0.0`
- **Transparency**: the transparency of the fragments
  - Constraints: between `0.0` and `1.0`
- **Min Height**: the minimum world height from which fragments are visible
  - Constraints: none
- **Max Height**: the maximum world height to which fragments are visible
  - Constraints: none
- **Color Inversion**: REFGIJOREJGREIGJERGJERIGJ
  - Constraints: at least `0.0`

### 3.5 `integer`

- **Animation Loops**: the amount of times the sprite animation repeats
  - Constraints: at least `0.0`
- **Animation Rows**: the amount of rows in the sprite animation texture
  - Constraints: at least `1.0`
- **Animation Columns**: the amount of columns in the sprite animation texture
  - Constraints: at least `1.0`
- **Animation Row Index**: the current row of the sprite animation texture
  - Constraints: at least `0.0`
- **Animation Column Index**: the current column of the sprite animation texture
  - Constraints: at least `0.0`
- **Animation Framestep**: the amount of engine execution frames between the sprite animation frame cycles
  - Constraints: at least `0.0`

### 3.6 `boolean`

- **Shadowed**: the mesh is captured for shadow rendering
  - Constraints: none
- **Reflected**: the mesh is captured for reflection rendering
  - Constraints: none
- **Facing X**: the mesh is horizontally facing the camera
  - Constraints: none
- **Facing Y**: the mesh is vertically facing the camera
  - Constraints: none
- **Bright**: enable or disable vertical billboard facing towards the camera
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none
- **Textual**: the diffuse map is textual
  - Constraints: none
