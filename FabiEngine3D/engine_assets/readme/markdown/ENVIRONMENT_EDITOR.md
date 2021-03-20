# Sky
![sky](../images/sky_editor.png)
### General
- All sky environments will be saved in `projects\<your_project>\data\sky.fe3d`.
- You can **create/edit/delete** sky environments.
- Every created sky environment can be placed in a **scene** later on.
- The sky environment is rendered as a **skybox**, which has 6 different images: left, right, bottom, top, back, front.
- You can activate a **first-person camera** with **RMB** and move it with your **mouse**.
### Texturing
- You can load these 6 images from `game_assets\textures\cube_maps\`.
- The image format **must** be a colored 24bit `PNG`.
- The image resolutions **must** be exactly the same.
### Properties
- **Lightness**: the brightness of the sky fragments. **Range**: 0 to inf.
- **Color**: the RGB color that will be mixed with the sky fragments. **Range**: 0 to 255.
- **Rotation speed**: the speed of rotation around the Y axis. **Range**: -inf to inf.

# Terrain
![terrain](../images/terrain_editor.png)
### General
- All terrain environment will be saved in `projects\<your_project>\data\terrain.fe3d`.
- You can **create/edit/delete** terrain environments.
- Every created terrain environment can be placed in a **scene** later on.
- You can rotate the **camera** around the terrain by using your mouse **scroll wheel**.
### Texturing
- The terrain environment is generated through a **height map** texture.
- The terrain can have a base **diffuse map** texture.
- Multitexturing can be done through a **blend map**.
- Every color **channel** (R,G,B) of the blend map **represents** a different **diffuse map**.
- The rendering of **every diffuse map** can be improved with a **normal map**.
- In total you can use **10 different textures** for terrain rendering (1x heightmap, 1x blendmap, 4x diffusemap, 4x normalmap).
- **Height map**: grayscaled 24bit `BMP` format image file from `game_assets\textures\height_maps\`.
- **Blend map**: colored 24bit `PNG` format image file from `game_assets\textures\blend_maps\`.
- **Diffuse maps**: colored 24bit `PNG` format image file from `game_assets\textures\diffuse_maps\`.
- **Normal maps**: colored 24bit `PNG` format image file from `game_assets\textures\normal_maps\`.
### Properties
- **Max height**: the maximum height of the terrain, which is calculated based on the height map pixel intensities. **Range**: 0 to inf.
- **UV repeat**: the amount of times the main diffuse map texture is repeated. **Range**: 0 to inf.
- **Red UV**: the amount of times the diffuse map texture of the RED blend map channel is repeated. **Range**: 0 to inf.
- **Green UV**: the amount of times the diffuse map texture of the GREEN blend map channel is repeated. **Range**: 0 to inf.
- **Blue UV**: the amount of times the diffuse map texture of the BLUE blend map channel is repeated. **Range**: 0 to inf.
- **Specular**: enable or disable specular lighting on the terrain. **Range**: ON or OFF.
- **Spec factor**: the shininess of the specular lighting. **Range**: 0 to 256.
- **Spec intensity**: the intensity of the specular lighting. **Range**: 0 to inf.
- **Lightness**: the brightness of the terrain fragments. **Range**: 0 to inf.

# Water
![water](../images/water_editor.png)
### General
- All water environments will be saved in `projects\<your_project>\data\water.fe3d`.
- You can **create/edit/delete** water environments.
- Every created water environment can be placed in a **scene** later on.
- The water environment is simply a **flat plane** in 3D space.
- You have the option to show a created terrain while creating a water environment, mainly for having a reference.
- You can rotate the **camera** around the water by using your mouse **scroll wheel**.
### Texturing
- To enable the rippling effect, you need a **DUDV map**.
- To enable the waving effect, you need a **displacement map**.
- To enable specular lighting, you need a **normal map**.
- **DUDV map**: colored 24bit `PNG` format image from `game_assets\textures\dudv_maps\`.
- **Displacement map**: grayscaled 24bit `PNG` format image from `game_assets\textures\displacement_maps\`.
- **Normal map**: colored 24bit `PNG` format image from `game_assets\textures\normal_maps\`.
### Properties
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
