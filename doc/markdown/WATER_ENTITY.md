# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Assets

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

- **DUDV Map Path**: the path of the DUDV map file
  - Type: `string`
  - Constraints: none
- **Normal Map Path**: the path of the normal map file
  - Type: `string`
  - Constraints: none
- **Displacement Map Path**: the path of the displacement map file
  - Type: `string`
  - Constraints: none
- **Color**: the RGB color multiplier
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Speed**: the speed of  the rippling/waving movement
  - Type: `decimal2`
  - Constraints: none
- **Height**: the Y position of the mesh
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Size**: the XZ size of the mesh
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Wave Height**: the height of the waves
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Intesity**: the intensity of the specular lighting
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Transparency**: the transparency of the fragments
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Reflective**: planar reflections are rendered on the mesh
  - Type: `boolean`
  - Constraints: none
- **Refractive**: planar refractions are rendered on the mesh
  - Type: `boolean`
  - Constraints: none
- **Specular**: specular lighting is rendered on the mesh
  - Type: `boolean`
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Type: `boolean`
  - Constraints: none
- **Quality**: determines what is captured by reflections/refractions
  - Type: `enumeration`
  - Constraints: `SKY` or `SKY_TERRAIN` or `SKY_TERRAIN_MODELS` or `SKY_TERRAIN_MODELS_BILLBOARDS`
