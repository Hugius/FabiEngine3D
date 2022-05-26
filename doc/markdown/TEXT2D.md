# Text2D

## 1. General

- The text2D is a composition of quad2Ds.
- Every quad2D represents a text character.
- A font map is used to form a line of text.
- The ID of a text2D cannot be empty or contain spaces/capitals/specials.

## 2. Assets

- Font map

## 3. Properties

- **ID**: the identifier of the text2D
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Font Map Path**: the path of the font map file
  - Type: `string`
  - Constraints: none
- **Content**: the content of the characters
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
- **Min Clip Position**: the minimum position from which fragments are visible
  - Type: `decimal2`
  - Constraints: none
- **Max Clip Position**: the maximum position to which fragments are visible
  - Type: `decimal2`
  - Constraints: none
- **Rotation**: the rotation of the mesh around the Z axis
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Opacity**: the opacity of the fragments
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Visible**: the visibility of the text2D in the world
  - Type: `boolean`
  - Constraints: none
- **Horizontally Flipped**: the characters are horizontally flipped
  - Type: `boolean`
  - Constraints: none
- **Vertically Flipped**: the characters are vertically flipped
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
