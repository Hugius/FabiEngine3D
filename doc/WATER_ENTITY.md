# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Resources

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

- **Size**: the XZ size of the water plane in world space.
  - Constraints `0` to `inf`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Constraints: `0` to `inf`
- **Color**: the RGB color that will be mixed with the water fragments.
  - Constraints: `0` to `255`
- **Reflective**: enable or disable reflections on the water.
  - Constraints: `ON` or `OFF`
- **Refractive**: enable or disable refractions on the water.
  - Constraints: `ON` or `OFF`
- **Specular**: enable or disable specular lighting on the water.
  - Constraints: `ON` or `OFF`
- **Specular Factor**: the shininess of the specular lighting.
  - Constraints: `0` to `256`
- **Specular Intesity**: the intensity of the specular lighting.
  - Constraints: `0` to `inf`
- **Wave Height**: the height of the waves.
  - Constraints: `0` to `inf`
- **Water Speed**: the speed of water rippling/waving movement.
  - Constraints: `-inf` to `inf`
- **Transparency**: the percentage that determines how transparent the water is.
  - Constraints: `0` to `100`
- **Quality**: determines everything that is captured by reflections & refractions.
  - Constraints: `1` (only sky) or `2` (sky + terrain) or `3` (sky + terrain + models) or `4` (sky + terrain + models + billboards)
