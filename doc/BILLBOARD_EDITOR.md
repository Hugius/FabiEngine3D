# Billboard Editor

## 1. General

- All billboards will be saved in `~\projects\<your_project>\data\billboard.fe3d`.
- You can create/edit/delete billboards.
- Every created billboard can be placed in a world.
- Billboards are not affected by shadows or lighting.
- Each billboard has 1 AABB.
- The AABB is bound to the billboard's transformation, so the AABB will transform with the billboard.

## 2. Controls

- Move camera with your mouse
- Press `RMB` to toggle camera
- Scroll `MMB` to zoom camera
- Press `H` to toggle debug rendering
- Press `R` to toggle reference box
- Press `F` to toggle wireframe
- Press `ESC` to go back
- Press `SPACE` to move upwards
- Press `SHIFT` to move downwards

## 3. Resources

- **Font**: `TTF` format font file from `~\projects\<your_project>\assets\fonts`.
- **Diffuse Map**: colored `24bit/32bit PNG` format image file from `~\projects\<your_project>\assets\textures\diffuse_maps`
- **Emission Map**: colored `24bit/32bit PNG` format image file from `~\projects\<your_project>\assets\textures\emission_maps`

## 4. Properties

- **Size**: the size of the billboard.
  - Constraints: `0` to `inf`
- **Text Content**: the text content of the billboard.
  - Constraints: `none`
- **Texture Repeat**: the amount of times the textures are repeated.
  - Constraints: `0` to `inf`
- **Rows**: the amount of rows in the sprite animation texture.
  - Constraints: `1` to `inf`
- **Columns**: the amount of columns in the sprite animation texture.
  - Constraints: `1` to `inf`
- **Framestep**: the amount of engine execution frames between the sprite animation frame cycles.
  - Constraints: `0` to `inf`
- **Color**: the RGB color that will be mixed with the billboard fragments.
  - Constraints: `0` to `255`
- **Lightness**: the brightness of the billboard fragments.
  - Constraints: `0` to `inf`
- **Shadowed**: enable or disable billboard capturing in shadows.
  - Constraints: `ON` or `OFF`
- **Reflected**: enable or disable billboard capturing in reflections.
  - Constraints: `ON` or `OFF`
- **Facing X**: enable or disable horizontal billboard facing towards the camera.
  - Constraints: `ON` or `OFF`
- **Facing Y**: enable or disable vertical billboard facing towards the camera.
  - Constraints: `ON` or `OFF`
