# Sky
![sky](FabiEngine3D/engine_assets/readme/sky_editor.png)
- You can **create/edit/delete** sky environments that can be placed in a scene.
- The sky environment is rendered as a **skybox**, which has 6 different textures.
- You can load these 6 images from `game_assets\textures\cube_maps\`.
- The image format must be a colored 24bit `PNG`.
- The image resolutions must be the same.
- Properties include: lightness, color, rotation speed.

# Terrain
![terrain](FabiEngine3D/engine_assets/readme/terrain_editor.png)
- You can **create/edit/delete** terrain environments that can be placed in a scene.
- The terrain environment is generated with a **height map** texture.
- A terrain can have a **diffuse map** texture, but can also be textured using a **blend mapping**.
- In total a terrain can be textured with up to 4 different textures!
- All of these rendered textures can be improved with **normal mapping**.
- Properties include: max height, UV-repeat, lighting.
- **Height map**: grayscale 24bit `BMP` format image file from `game_assets\textures\height_maps\`.
- **Blend map**: colored 24bit `PNG` file format image from `game_assets\textures\blend_maps\`.
- **Diffuse maps**: colored 24bit `PNG` format image file from `game_assets\textures\diffuse_maps\`.
- **Normal maps**: colored 24bit `PNG` format image file from `game_assets\textures\normal_maps\`.

# Water
![water](FabiEngine3D/engine_assets/readme/water_editor.png)
- You can **create/edit/delete** water environments that can be placed in a scene.
- The water environment is simply a **flat plane** in 3D space.
- Properties include: position, size, wave height, specular factor & intensity, wave/ripple speed, UV-repeat, color, edge transparency.
- You also have the option to show a created terrain while creating a water environment, mainly for having a reference.
- Custom color (RGB).
- Sky & terrain reflection (on/off, only shown when above water surface).
- Water refraction (on/off, **Warning**: huge performance impact!).
- Rippling effect (on/off, **DUDV map** needed: colored 24bit `PNG` format image from `game_assets\textures\dudv_maps\`).
- Waves (on/off, **displacement map** needed: grayscale 24bit `PNG` format image from `game_assets\textures\displacement_maps\`).
- Specular reflection (on/off, **normal map** needed: colored 24bit `PNG` format image from `game_assets\textures\normal_maps\`).