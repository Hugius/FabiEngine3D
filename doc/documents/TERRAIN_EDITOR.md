# Terrain Editor

## General

- All terrain entities will be saved in `~\projects\<your_project>\data\terrain.fe3d`.
- You can create/edit/delete terrain entities.
- Every created terrain entity can be placed in a scene.

## Controls

- Press RMB to toggle the camera
- Press MMB to zoom the camera
- Move the camera with your mouse
- Press H to toggle debug rendering
- Press R to toggle the reference box
- Press F to toggle the wire frame
- Press ESC to go back

## Texturing

- The terrain entity is generated through a **height map** texture.
- The terrain can have a base **diffuse map** texture.
- Multitexturing can be done through a **blend map**.
- Every color **channel** (R,G,B) of the blend map **represents** a different **diffuse map**.
- The rendering of **every diffuse map** can be improved with a **normal map**.
- In total you can use **10 different textures** for terrain rendering (1x heightmap, 1x blendmap, 4x diffusemap, 4x normalmap).
- **Height map**: grayscaled 24bit `BMP` format image file from `~projects\<your_project>\assets\textures\height_maps\`.
- **Blend map**: colored 24bit `PNG` format image file from `~projects\<your_project>\assets\textures\blend_maps\`.
- **Diffuse maps**: colored 24bit `PNG` format image file from `~projects\<your_project>\assets\textures\diffuse_maps\`.
- **Normal maps**: colored 24bit `PNG` format image file from `~projects\<your_project>\assets\textures\normal_maps\`.

## Properties

- **Max height**: the maximum height of the terrain, which is calculated based on the height map pixel intensities. **Range**: 0 to inf.
- **UV repeat**: the amount of times the main diffuse map texture is repeated. **Range**: 0 to inf.
- **Red UV**: the amount of times the diffuse map texture of the RED blend map channel is repeated. **Range**: 0 to inf.
- **Green UV**: the amount of times the diffuse map texture of the GREEN blend map channel is repeated. **Range**: 0 to inf.
- **Blue UV**: the amount of times the diffuse map texture of the BLUE blend map channel is repeated. **Range**: 0 to inf.
- **Specular**: enable or disable specular lighting on the terrain. **Range**: ON or OFF.
- **Spec factor**: the shininess of the specular lighting. **Range**: 0 to 256.
- **Spec intensity**: the intensity of the specular lighting. **Range**: 0 to inf.
- **Lightness**: the brightness of the terrain fragments. **Range**: 0 to inf.
