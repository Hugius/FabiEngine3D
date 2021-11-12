# Water Editor

![water](../images/water_editor.png)

## General

- All water environments will be saved in `projects\<your_project>\data\water.fe3d`.
- You can **create/edit/delete** water environments.
- Every created water environment can be placed in a **scene** later on.
- The water environment is simply a **flat plane** in 3D space.
- You have the option to show a created terrain while creating a water environment, mainly for having a reference.
- You can rotate the **camera** around the water by using your mouse **scroll wheel**.

## Texturing

- To enable the rippling effect, you need a **DUDV map**.
- To enable the waving effect, you need a **displacement map**.
- To enable specular lighting, you need a **normal map**.
- **DUDV map**: colored 24bit `PNG` format image from `game_assets\textures\dudv_maps\`.
- **Displacement map**: grayscaled 24bit `PNG` format image from `game_assets\textures\displacement_maps\`.
- **Normal map**: colored 24bit `PNG` format image from `game_assets\textures\normal_maps\`.

## Properties

- **Position**: the XYZ position of the water plane in scene space. **Range** -inf to inf.
- **Size**: the XZ size of the water plane in scene space. **Range** 0 to inf.
- **UV repeat**: the amount of times the diffuse map texture is repeated. **Range**: 0 to inf.
- **Reflective**: enable or disable sky/terrain reflectivity on the water. **Range**: ON or OFF.
- **Refractive**: enable or disable terrain/model/billboard refractivity on the water. **Range**: ON or OFF.
- **Waving**: enable or disable waving effect on the water. **Range**: ON or OFF.
- **Rippling**: enable or disable rippling effect on the water. **Range**: ON or OFF.
- **Specular**: enable or disable specular lighting on the water. **Range**: ON or OFF.
- **Water speed**: the speed with which the water rippling/waving moves. **Range**: -inf to inf.
- **Transparency**: the percentage of how transparent the water plane is. This applies mostly for edges. **Range**: 0 to 100.
- **Color**: the RGB color that will be mixed with the water fragments. **Range**: 0 to 255.
- **Spec factor**: the shininess of the specular lighting. **Range**: 0 to 256.
- **Spec intesity**: the intensity of the specular lighting. **Range**: 0 to inf.
- **Wave height**: the height of the waves. **Range**: 0 to inf.
- **Quality**: determines which entities are captured by reflections & refractions.  
  **Range**: 1 (only sky) or 2 (sky + terrain) or 3 (sky + terrain + models) or 4 (sky + terrain + models + billboards).
