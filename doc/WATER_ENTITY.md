# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Assets

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

### 3.1 `string`

- **DUDV Map Path**: the path of the DUDV map file
  - Constraints: none
- **Displacement Map Path**: the path of the displacement map file
  - Constraints: none
- **Normal Map Path**: the path of the normal map file
  - Constraints: none

### 3.2 `decimal3`

- **Color**: the RGB color multiplier
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Constraints: between `0.0` and `1.0`

### 3.3 `decimal2`

- **Speed**: the speed of  the rippling/waving movement
  - Constraints: none

### 3.4 `decimal`

- **Height**: the Y position of the mesh in world space
  - Constraints: at least `0.0`
- **Size**: the XZ size of the mesh in world space
  - Constraints: at least `0.0`
- **Wave Height**: the height of the waves
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting
  - Constraints: at least `0.0`
- **Specular Intesity**: the intensity of the specular lighting
  - Constraints: at least `0.0`
- **Transparency**: the transparency of the fragments
  - Constraints: between `0.0` and `1.0`

### 3.5 `boolean`

- **Reflective**: planar reflections are rendered on the mesh
  - Constraints: none
- **Refractive**: planar refractions are rendered on the mesh
  - Constraints: none
- **Specular**: specular lighting is rendered on the mesh
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none

### 3.6 `enumeration`

- **Quality**: determines everything that is captured by reflections & refractions
  - Constraints: `SKY` or `SKY_TERRAIN` or `SKY_TERRAIN_MODELS` or `SKY_TERRAIN_MODELS_BILLBOARDS`
