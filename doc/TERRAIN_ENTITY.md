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

### 3.1 String

### 3.2 Vector3

### 3.3 Vector2

### 3.4 Decimal

- **Max Height**: the maximum height of the terrain, which is calculated based on the height map pixel intensities.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Lightness**: the brightness of the terrain fragments.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Factor**: the shininess of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Intensity**: the intensity of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the base textures are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Red Repeat**: the amount of times the textures of the red blend map channel are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Green Repeat**: the amount of times the textures of the green blend map channel are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Blue Repeat**: the amount of times the textures of the blue blend map channel are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`

### 3.5 Integer

### 3.6 Boolean

- **Specular**: enable or disable specular lighting on the terrain.
  - Type: `boolean`
  - Constraints: none

### 3.7 Enumeration
