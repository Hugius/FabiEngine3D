# Terrain Entity

## 1. General

- The terrain entity is a 3D object in 3D space.
- The mesh of a terrain entity is generated with a height map.

## 2. Resources

- Height map
- Blend map
- Diffuse map
- Normal map

## 3. Properties

### 3.1 `string`

- **Height Map Path**: the path of the height map file
  - Constraints: none
- **Blend Map Path**: the path of the blend map file
  - Constraints: none
- **Diffuse Map Path**: the path of the diffuse map file
  - Constraints: none
- **Normal Map Path**: the path of the normal map file
  - Constraints: none

### 3.2 `decimal3`

- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Constraints: between `0.0` and `1.0`

### 3.3 `decimal`

- **Max Height**: the maximum height of the mesh
  - Constraints: at least `0.0`
- **Lightness**: the lightness multiplier of the fragments
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting
  - Constraints: at least `0.0`
- **Specular Intensity**: the intensity of the specular lighting
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the base textures are repeated
  - Constraints: at least `0.0`
- **Red Repeat**: the amount of times the textures of the red blend map channel are repeated
  - Constraints: at least `0.0`
- **Green Repeat**: the amount of times the textures of the green blend map channel are repeated
  - Constraints: at least `0.0`
- **Blue Repeat**: the amount of times the textures of the blue blend map channel are repeated
  - Constraints: at least `0.0`

### 3.4 `boolean`

- **Specular**: specular lighting is rendered on the mesh
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none
