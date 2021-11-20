# Billboard Entity

## 1. General

- The billboard entity is a 2D quad in 3D space.
- Instead of a solid quad, the texture of the billboard entity can be transparent text (based on a font).
- Billboard entities are not affected by shadows or lighting.

## 2. Resources

- Font
- Diffuse map
- Emission map

## 3. Properties

### 3.1 `string`

- **Text Content**: the text content of the billboard.
  - Type: `string`
  - Constraints: none
- **Diffuse Map Path**: the text content of the billboard.
  - Type: `string`
  - Constraints: none
- **Emission Map Path**: the text content of the billboard.
  - Type: `string`
  - Constraints: none
- **Font Path**: the text content of the billboard.
  - Type: `string`
  - Constraints: none

### 3.2 `decimal`

- **Size**: the size of the billboard.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Rows**: the amount of rows in the sprite animation texture.
  - Type: `decimal`
  - Constraints: at least `1.0`
- **Columns**: the amount of columns in the sprite animation texture.
  - Type: `decimal`
  - Constraints: at least `1.0`
- **Framestep**: the amount of engine execution frames between the sprite animation frame cycles.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Color**: the RGB color that will be mixed with the billboard fragments.
  - Type: `decimal`
  - Constraints: between `0.0` to `1.0`
- **Lightness**: the brightness of the billboard fragments.
  - Type: `decimal`
  - Constraints: at least `0.0`

### 3.3 `boolean`

- **Shadowed**: enable or disable billboard capturing in shadows.
  - Type: `boolean`
  - Constraints: none
- **Reflected**: enable or disable billboard capturing in reflections.
  - Type: `boolean`
  - Constraints: none
- **Facing X**: enable or disable horizontal billboard facing towards the camera.
  - Type: `boolean`
  - Constraints: none
- **Facing Y**: enable or disable vertical billboard facing towards the camera.
  - Type: `boolean`
  - Constraints: none
