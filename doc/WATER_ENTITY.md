# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Resources

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

### 3.1 `string`

- **DUDV Map Path**: the path of the DUDV map file.
  - Constraints: none
- **Displacement Map Path**: the path of the displacement map file.
  - Constraints: none
- **Normal Map Path**: the path of the normal map file.
  - Constraints: none

### 3.2 `vector3`

- **Color**: the RGB color that will be mixed with the water fragments.
  - Constraints: between `0.0` and `1.0`

### 3.3 `vector2`

- **Water Speed**: the speed of water rippling/waving movement.
  - Constraints: none

### 3.4 `decimal`

- **Height**: the Y position of the water plane in world space.
  - Constraints: at least `0.0`
- **Size**: the XZ size of the water plane in world space.
  - Constraints: at least `0.0`
- **Wave Height**: the height of the waves.
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting.
  - Constraints: at least `0.0`
- **Specular Intesity**: the intensity of the specular lighting.
  - Constraints: at least `0.0`
- **Transparency**: the percentage that determines how transparent the water is.
  - Constraints: between `0.0` and `1.0`

### 3.5 `boolean`

- **Reflective**: the water is reflective.
  - Constraints: none
- **Refractive**: the water is refractive.
  - Constraints: none
- **Specular**: specular lighting is rendered on the water.
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe.
  - Constraints: none

### 3.6 `enumeration`

- **Quality**: determines everything that is captured by reflections & refractions.
  - Constraints: `SKY` or `SKY_TERRAIN` or `SKY_TERRAIN_MODELS` or `SKY_TERRAIN_MODELS_BILLBOARDS`
