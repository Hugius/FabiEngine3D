# Water Entity

## 1.1 General

- The water entity is 2D quad in 3D space.

## 1.2 Resources

- DUDV Map
- Displacement Map
- Normal Map

## 1.3 Properties

- **Size**: the XZ size of the water plane in world space.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Color**: the RGB color that will be mixed with the water fragments.
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Reflective**: enable or disable reflections on the water.
  - Type: `decimal`
  - Constraints: none
- **Refractive**: enable or disable refractions on the water.
  - Type: `decimal`
  - Constraints: none
- **Specular**: enable or disable specular lighting on the water.
  - Type: `decimal`
  - Constraints: none
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
- **Quality**: determines everything that is captured by reflections & refractions.
  - Type: `decimal`
  - Constraints: `1` (only sky) or `2` (sky + terrain) or `3` (sky + terrain + models) or `4` (sky + terrain + models + billboards)
