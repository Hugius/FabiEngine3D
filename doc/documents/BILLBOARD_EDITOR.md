# Billboard Editor

## General

- All billboards will be saved in `~\projects\<your_project>\data\billboard.fe3d`.
- You can create/edit/delete billboards.
- Every created billboard can be placed in a scene.
- Each billboard has 1 AABB.
- The AABB is bound to the billboard's transformation, so the AABB will transform with the billboard.

## Controls

- Press RMB to toggle the camera
- Scroll MMB to zoom the camera
- Move the camera with your mouse
- Press H to toggle debug rendering
- Press R to toggle the reference box
- Press F to toggle the wire frame
- Press ESC to go back
- Press SPACE to move upwards
- Press SHIFT to move downwards

## Resources

- **Font**: `TTF` format font file from `~\projects\<your_project>\assets\fonts`.
- **Diffuse Map**: colored `24bit/32bit PNG` format image file from `~\projects\<your_project>\assets\textures\diffuse_maps`
- **Emission Map**: colored `24bit/32bit PNG` format image file from `~\projects\<your_project>\assets\textures\emission_maps`

## Properties

- **Size**: the size of the billboard.
  - **Range**: 0 to inf.
- **Text Content**: the text content of the billboard.
  - **Range**: none.
- **Texture Repeat**: the amount of times the textures are repeated.
  - **Range**: 0 to inf.
- **Rows**: the amount of rows in the sprite animation texture.
  - **Range**: 1 to inf.
- **Columns**: the amount of columns in the sprite animation texture.
  - **Range**: 1 to inf.
- **Framestep**: the amount of engine execution frames between the sprite animation frame cycles.
  - **Range**: 0 to inf.
- **Color**: the RGB color that will be mixed with the billboard fragments.
  - **Range**: 0 to 255.
- **Lightness**: the brightness of the billboard fragments.
  - **Range**: 0 to inf.
- **Shadowed**: enable or disable billboard capturing in shadows.
  - **Range**: ON or OFF.
- **Reflected**: enable or disable billboard capturing in reflections.
  - **Range**: ON or OFF.
- **Facing X**: enable or disable horizontal billboard facing towards the camera.
  - **Range**: ON or OFF.
- **Facing Y**: enable or disable vertical billboard facing towards the camera.
  - **Range**: ON or OFF.
