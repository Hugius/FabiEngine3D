# Sky Entity

## 1. General

- The sky entity is a 3D cube in 3D space.
- This cube, which called a skybox, is rendered around the camera.
- A skybox has a static position and has an infinite size, which creates the illusion of a real sky.

## 2. Assets

- Cube Map

## 3. Properties

### 3.1 `string`

- **Right Cube Map Path**: the path of the right part of the cube map file
  - Constraints: none
- **Left Cube Map Path**: the path of the left part of the cube map file
  - Constraints: none
- **Top Cube Map Path**: the path of the top part of the cube map file
  - Constraints: none
- **Bottom Cube Map Path**: the path of the bottom part of the cube map file
  - Constraints: none
- **Back Cube Map Path**: the path of the back part of the cube map file
  - Constraints: none
- **Front Cube Map Path**: the path of the front part of the cube map file
  - Constraints: none

### 3.2 `decimal3`

- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Constraints: between `0.0` and `1.0`

### 3.3 `decimal`

- **Rotation**: the XYZ rotation of the mesh around the Y axis
  - Constraints: between `0.0` and `360.0`
- **Lightness**: the lightness multiplier of the fragments
  - Constraints: at least `0.0`

### 3.4 `boolean`

- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none
