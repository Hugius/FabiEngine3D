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

- **Size**: the size of the billboard.
  - **Constraints**: `0` to `inf`
- **Text Content**: the text content of the billboard.
  - **Constraints**: `none`
- **Texture Repeat**: the amount of times the textures are repeated.
  - **Constraints**: `0` to `inf`
- **Rows**: the amount of rows in the sprite animation texture.
  - **Constraints**: `1` to `inf`
- **Columns**: the amount of columns in the sprite animation texture.
  - **Constraints**: `1` to `inf`
- **Framestep**: the amount of engine execution frames between the sprite animation frame cycles.
  - **Constraints**: `0` to `inf`
- **Color**: the RGB color that will be mixed with the billboard fragments.
  - **Constraints**: `0` to `255`
- **Lightness**: the brightness of the billboard fragments.
  - **Constraints**: `0` to `inf`
- **Shadowed**: enable or disable billboard capturing in shadows.
  - **Constraints**: `ON` or `OFF`
- **Reflected**: enable or disable billboard capturing in reflections.
  - **Constraints**: `ON` or `OFF`
- **Facing X**: enable or disable horizontal billboard facing towards the camera.
  - **Constraints**: `ON` or `OFF`
- **Facing Y**: enable or disable vertical billboard facing towards the camera.
  - **Constraints**: `ON` or `OFF`
