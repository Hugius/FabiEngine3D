# Text Entity

## 1. General

- The text entity is a 2D quad in 2D space.
- The mesh renders on top of all 3D rendering.
- A font is used to generate a diffuse map based on the text content.

## 2. Assets

- Font

## 3. Properties

- **Font Path**: the path of the font file
  - Type: `string`
  - Constraints: none
- **Text Content**: the text content of the diffuse map
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
- **Centered**: the mesh is centered around XY(0,0)
  - Type: `boolean`
  - Constraints: none
- **Dynamic**: the mesh is divided in multiple text entities for every single character in the text content
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
