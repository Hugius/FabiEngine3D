# Sky Editor

## General

- All skies will be saved in `~\projects\<your_project>\data\sky.fe3d`.
- You can create/edit/delete skies.
- Every created sky can be placed in a scene.
- Each sky is rendered as a cube map, which consists of 6 different textures: left, right, bottom, top, back, front.

## Controls

- Press RMB to toggle camera
- Move camera with your mouse
- Press H to toggle debug rendering
- Press F to toggle wireframe
- Press ESC to go back

## Resources

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
