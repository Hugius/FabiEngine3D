# Model Editor

## 1. General

- All models will be saved in `~\projects\<your_project>\data\model.fe3d`.
- You can create/edit/delete models.
- Every created model can be placed in a scene.
- A model cannot exist without having a mesh.
- The new model name cannot contain the '@' character, because is it reserved by the engine.

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

- **Mesh**: `OBJ` format mesh file from `~\projects\<your_project>\assets\meshes`.
- **Diffuse map**: colored `24bit/32bit PNG` format image file from `~\projects\<your_project>\assets\textures\diffuse_maps\`.
- **Emission map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\emission_maps\`.
- **Specular map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\specular_maps\`.
- **Reflection map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\reflection_maps\`.
- **Normal map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\normal_maps\`.

## 4. Mesh

- Make sure the center of your mesh is XYZ(0,0,0).
- The mesh should be modeled so that the lowest vertex (Y coordinate) is positioned at the center.
- A mesh can consist of multiple parts (which are collections of vertices).
- In the mesh file, you need to specify when a part of vertices starts.
- You can start a new mesh part by writing `FE3D_PART <name>` in the OBJ file.
- If a mesh is multiparted, you can specify textures/lighting for each mesh part.

## 5. Properties

- **Size**: size multiplier of the mesh.
  - **Range**: 0 to inf
- **Texture Repeat**: the amount of times the textures are repeated.
  - **Range**: 0 to inf
- **Color**: the RGB color that will be mixed with the model fragments.
  - **Range**: 0 to 255
- **Lightness**: the brightness of the model fragments.
  - **Range**: 0 to inf
- **Specular**: enable or disable specular lighting on the model.
  - **Range**: ON or OFF
- **Specular Factor**: the shininess of the specular lighting.
  - **Range**: 0 to 256
- **Specular Intensity**: the intensity of the specular lighting.
  - **Range**: 0 to inf
- **Reflective**: enable or disable full sky reflection or vertical scene reflection.
  - **Range**: ON or OFF
- **Type**: the type of reflection that is rendered onto the model.
  - **Range**: CUBE or PLANAR
- **Reflectivity**: the percentage of how reflective the model is.
  - **Range**: 0 to 100
- **Level Of Detail**: the ID of another model representing the LOD version of the current model. If you want to remove the LOD, fill in "@".
  - **Range**: none
- **Instanced**: enable or disable instanced rendering for this model (disables AABBs).
  - **Range**: ON or OFF
- **Culling**: enable or disable the face culling performance optimization.
  - **Range**: ON or OFF
- **Rotation**: the order of directions in which the model is rotated.
  - **Range**: XYZ, XZY, YXZ, YZX, ZXY, ZYX

## AABB editor

- You can create/edit/delete AABBs.
- Each model can have 1 or more AABBs, used for collision and raycasting.
- You can bind 1 or more AABBs to the model using the AABB editor within the model editor.
- Every individual AABB has its own local position and size that you can alter in the editor.
- All AABBs are bound to the model's transformation, so the AABBs will transform with the model.
