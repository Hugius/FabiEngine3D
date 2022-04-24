# Text3D Entity

## 1. General

- The Text3D entity is a composition of quad3D entities.
- Every quad3D entity represents a text character.
- The text is generated using a font map.

## 2. Assets

- Font map

## 3. Properties

- **Font Map Path**: the path of the font map file
  - Type: `string`
  - Constraints: cannot be changed
- **Content**: the content of the characters
  - Type: `string`
  - Constraints: none
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Min Clip Position**: the minimum position from which fragments are visible
  - Type: `decimal3`
  - Constraints: none
- **Max Clip Position**: the maximum position to which fragments are visible
  - Type: `decimal3`
  - Constraints: none
- **Position**: the XY position of the mesh
  - Type: `decimal2`
  - Constraints: none
- **Size**: the XY size of the mesh
  - Type: `decimal2`
  - Constraints: at least `0.0`
- **Rotation**: the rotation of the mesh around the Z axis
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Lightness**: the lightness multiplier of the mesh
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Opacity**: the opacity of the fragments
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Min Texture Alpha**: the minimum texture alpha channel intensity to be visible
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Min Height**: the minimum Y position from which fragments are visible
  - Type: `decimal`
  - Constraints: none
- **Max Height**: the maximum Y position to which fragments are visible
  - Type: `decimal`
  - Constraints: none
- **Shadowed**: the mesh is captured for shadows
  - Type: `boolean`
  - Constraints: none
- **Reflected**: the mesh is captured for reflections
  - Type: `boolean`
  - Constraints: none
- **Facing Camera Horizontally**: the mesh is horizontally facing the camera
  - Type: `boolean`
  - Constraints: none
- **Facing Camera Vertically**: the mesh is vertically facing the camera
  - Type: `boolean`
  - Constraints: none
- **Bright**: the mesh is captured for bloom
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
- **Frozen**: the XYZ position of the mesh is not affected by the camera position
  - Type: `boolean`
  - Constraints: none
