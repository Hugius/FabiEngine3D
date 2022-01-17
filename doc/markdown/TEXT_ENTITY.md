# Text Entity

## 1. General

- The text entity is a composition of Quad2D entities.
- Every Quad2D entity represents a text character.
- A font map is used to form a line of text.

## 2. Assets

- Font map

## 3. Properties

- **Font Map Path**: the path of the font map file
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
- **Size**: the XY size of the mesh
  - Type: `decimal2`
  - Constraints: at least `0.0`
- **Rotation**: the rotation of the mesh around the Z axis
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Transparency**: the transparency of the fragments
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Horizontally Mirrored**: the diffuse map is horizontally mirrored
  - Type: `boolean`
  - Constraints: none
- **Vertically Mirrored**: the diffuse map is vertically mirrored
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
