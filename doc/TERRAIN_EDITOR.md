# Terrain Editor

## 1. General

- All terrains will be saved in `~\projects\<your_project>\data\terrain.fe3d`.
- You can create/edit/delete terrains.
- Every created terrain can be placed in a world.
- Each terrain is generated with a height map.

## 2. Controls

- Move camera with your mouse
- Press `RMB` to toggle camera
- Scroll `MMB` to zoom camera
- Press `H` to toggle debug rendering
- Press `R` to toggle reference box
- Press `F` to toggle wireframe
- Press `ESC` to go back

## 3. Resources

- **Height map**: grayscaled `24bit BMP` format image file from `~\projects\<your_project>\assets\textures\height_maps\`.
- **Blend map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\blend_maps\`.
- **Diffuse map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\diffuse_maps\`.
- **Normal map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\normal_maps\`.

## 4. Blend Mapping

Using a blend map you can render multiple textures onto a terrain mesh. Every color channel (R,G,B) of the blend map represents a different diffuse/normal map. This means that in total you can use up to 10 different textures for terrain rendering:

- 1x height map
- 1x blend map
- 1x base diffuse map
- 1x base normal map
- 3x blend diffuse map
- 3x blend normal map

## 5. Properties

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
