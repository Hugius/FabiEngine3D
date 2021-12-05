# Image Entity

## 1. General

- The image entity is a 2D quad in 2D space.
- The mesh renders on top of all 3D rendering.
- Sprite animations can be applied to the diffuse map.

## 2. Assets

- Diffuse Map

## 3. Properties

- **Diffuse Map Path**: the path of the diffuse map file
  - Type: `string`
  - Constraints: none
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Position**: the XY position of the mesh
  - Type: `decimal2`
  - Constraints: none
- **Size**: the XY size multiplier of the mesh
  - Type: `decimal2`
  - Constraints: at least `0.0`
- **Position Target**: the target XY position of the mesh
  - Type: `decimal2`
  - Constraints: none
- **Size Target**: the target XY size multiplier of the mesh
  - Type: `decimal2`
  - Constraints: at least `0.0`
- **Min Position**: the XY position of the mesh
  - Type: `decimal2`
  - Constraints: none
- **Max Position**: the XY position of the mesh
  - Type: `decimal2`
  - Constraints: none
- **Rotation**: the XYZ rotation of the mesh around the Y axis
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Rotation Target**: the target XYZ rotation of the mesh
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Rotation Target Speed**: the speed with which the mesh rotates to the target rotation
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Transparency**: the transparency of the fragments
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Animation Loops**: the amount of times the sprite animation repeats
  - Type: `integer`
  - Constraints: at least `0.0`
- **Animation Rows**: the amount of rows in the sprite animation texture
  - Type: `integer`
  - Constraints: at least `1.0`
- **Animation Columns**: the amount of columns in the sprite animation texture
  - Type: `integer`
  - Constraints: at least `1.0`
- **Animation Row Index**: the current row of the sprite animation texture
  - Type: `integer`
  - Constraints: at least `0.0`
- **Animation Column Index**: the current column of the sprite animation texture
  - Type: `integer`
  - Constraints: at least `0.0`
- **Animation Framestep**: the amount of engine updates between the sprite animation frame cycles
  - Type: `integer`
  - Constraints: at least `0.0`
- **Centered**: the mesh is centered around XY(0,0)
  - Type: `boolean`
  - Constraints: none
- **Mirrored Horizontally**: the diffuse map is mirrored horizontally
  - Type: `boolean`
  - Constraints: none
- **Mirrored Vertically**: the diffuse map is mirrored vertically
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
- **Animation Started**: the sprite animation is started (can still be paused)
  - Type: `boolean`
  - Constraints: none
- **Animation Paused**: the sprite animation is paused
  - Type: `boolean`
  - Constraints: none
