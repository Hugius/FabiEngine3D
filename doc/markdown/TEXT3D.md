# Text3D

## 1. General

- The text3D is a composition of quad3Ds.
- Every quad3D represents a text character.
- The text itself is generated using a font map.

## 2. Assets

- Font map

## 3. Properties

- **ID**: the unique identifier of the text3D
  - Type: `string`
  - Constraints: cannot be empty or contain spaces/capitals/specials
- **Font Map Path**: the path of the font map file
  - Type: `string`
  - Constraints: cannot be changed
- **Content**: the content of the characters
  - Type: `string`
  - Constraints: none
- **Color**: the RGB color multiplier of the mesh
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Min Clip Position**: the minimum position from which the mesh is visible
  - Type: `decimal3`
  - Constraints: none
- **Max Clip Position**: the maximum position to which the mesh is visible
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
- **Opacity**: the opacity of the mesh
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Min Alpha**: the minimum texture alpha channel intensity to be visible
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Min Clip Position**: the minimum position from which the mesh is visible
  - Type: `decimal3`
  - Constraints: none
- **Max Clip Position**: the maximum position to which the mesh is visible
  - Type: `decimal3`
  - Constraints: none
- **Visible**: the visibility of the text3D in the world
  - Type: `boolean`
  - Constraints: none
- **Shadowed**: the mesh is captured for shadows
  - Type: `boolean`
  - Constraints: none
- **Reflected**: the mesh is captured for reflections
  - Type: `boolean`
  - Constraints: none
- **Refracted**: the mesh is captured for refractions
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
- **Horizontally Flipped**: the characters are horizontally flipped
  - Type: `boolean`
  - Constraints: none
- **Vertically Flipped**: the characters are vertically flipped
  - Type: `boolean`
  - Constraints: none
