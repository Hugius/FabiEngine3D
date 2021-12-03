# Image Entity

## 1. General

- The image entity is a 2D quad in 2D space.
- The mesh renders on top of all 3D rendering.
- Sprite animations can be applied to the diffuse map.

## 2. Assets

- Diffuse Map

## 3. Properties

### 3.1 `string`

- **Diffuse Map Path**: the path of the diffuse map file
  - Constraints: none

### 3.2 `decimal3`

- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Constraints: between `0.0` and `1.0`

### 3.3 `decimal2`

- **Position**: the XY position of the mesh
  - Constraints: none
- **Size**: the XY size multiplier of the mesh
  - Constraints: at least `0.0`
- **Position Target**: the target XY position of the mesh
  - Constraints: none
- **Size Target**: the target XY size multiplier of the mesh
  - Constraints: at least `0.0`
- **Min Position**: the XY position of the mesh
  - Constraints: none
- **Max Position**: the XY position of the mesh
  - Constraints: none

### 3.4 `decimal`

- **Rotation**: the XYZ rotation of the mesh around the Y axis
  - Constraints: between `0.0` and `360.0`
- **Rotation Target**: the target XYZ rotation of the mesh
  - Constraints: between `0.0` and `360.0`
- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Constraints: at least `0.0`
- **Rotation Target Speed**: the speed with which the mesh rotates to the target rotation
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Constraints: at least `0.0`
- **Transparency**: the transparency of the fragments
  - Constraints: between `0.0` and `1.0`

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

- **Centered**: the mesh is centered around XY(0,0)
  - Constraints: none
- **Mirrored Horizontally**: the diffuse map is mirrored horizontally
  - Constraints: none
- **Mirrored Vertically**: the diffuse map is mirrored vertically
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none
- **Animation Started**: the sprite animation is started (can still be paused)
  - Constraints: none
- **Animation Paused**: the sprite animation is paused
  - Constraints: none
