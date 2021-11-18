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

- **Max Height**: the maximum height of the terrain, which is calculated based on the height map pixel intensities.
  - Constraints: `0` to `inf`
- **Lightness**: the brightness of the terrain fragments.
  - Constraints: `0` to `inf`
- **Specular**: enable or disable specular lighting on the terrain.
  - Constraints: `ON` or `OFF`
- **Specular Factor**: the shininess of the specular lighting.
  - Constraints: `0` to `256`
- **Specular Intensity**: the intensity of the specular lighting.
  - Constraints: `0` to `inf`
- **Texture Repeat**: the amount of times the base textures are repeated.
  - Constraints: `0` to `inf`
- **Red Repeat**: the amount of times the textures of the red blend map channel are repeated.
  - Constraints: `0` to `inf`
- **Green Repeat**: the amount of times the textures of the green blend map channel are repeated.
  - Constraints: `0` to `inf`
- **Blue Repeat**: the amount of times the textures of the blue blend map channel are repeated.
  - Constraints: `0` to `inf`
