# Sky Editor

## General

- All sky entities will be saved in `~\projects\<your_project>\data\sky.fe3d`.
- You can create/edit/delete sky entities.
- Every created sky entity can be placed in a scene.
- Each sky entity is rendered as a cube map, which consists of 6 different images: left, right, bottom, top, back, front.

## Controls

- Press RMB to toggle the camera
- Move the camera with your mouse
- Press H to toggle debug rendering
- Press F to toggle the wire frame
- Press ESC to go back

## Textures

- You can load the images from `~\projects\<your_project>\assets\textures\cube_maps\`.
- The image format must be a colored `24bit PNG`.
- The image resolutions must be exactly the same.

## Properties

- **Rotation Speed**: the speed of rotation around the Y axis.
  - **Range**: inf to inf
- **Lightness**: the brightness of the sky fragments.
  - **Range**: 0 to inf
- **Color**: the RGB color that will be mixed with the sky fragments.
  - **Range**: 0 to 255
