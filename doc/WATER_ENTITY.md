# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Resources

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

### 3.1 String

### 3.2 Vector3

- **Color**: the RGB color that will be mixed with the water fragments.
  - Type: `vector3`
  - Constraints: between `0.0` and `1.0`

### 3.3 Vector2

### 3.4 Decimal

- **Size**: the XZ size of the water plane in world space.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Factor**: the shininess of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Intesity**: the intensity of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Wave Height**: the height of the waves.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Water Speed**: the speed of water rippling/waving movement.
  - Type: `decimal`
  - Constraints: none
- **Transparency**: the percentage that determines how transparent the water is.
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`

### 3.5 Integer

### 3.6 Boolean

- **Reflective**: enable or disable reflections on the water.
  - Type: `boolean`
  - Constraints: none
- **Refractive**: enable or disable refractions on the water.
  - Type: `boolean`
  - Constraints: none
- **Specular**: enable or disable specular lighting on the water.
  - Type: `boolean`
  - Constraints: none

### 3.7 Enumeration

- **Quality**: determines everything that is captured by reflections & refractions.
  - Type: `enumeration`
  - Constraints: `SKY` or `SKY_TERRAIN` or `SKY_TERRAIN_MODELS` or `SKY_TERRAIN_MODELS_BILLBOARDS`