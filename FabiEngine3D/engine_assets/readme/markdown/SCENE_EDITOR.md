# Scene Editor
![scene](FabiEngine3D/engine_assets/readme/scene_editor.png)
### Environment
- Sky: you can select **only 1** sky, created in the environment editor.
- Terrain: you can select **only 1** terrain, created in the environment editor.
- Water: you can select **only 1** water, created in the environment editor.
### Models
- You can place **multiple** models in the scene.
- If a terrain is selected, the model will be placed **on top** of the terrain.
- If no terrain is selected, the model will be placed at **XYZ(0,0,0)**.
- Every placed model can be **edited** (position, rotation, size, animation, deleting, freezing into local space).
- Placed models are not meant for individual interactions through scripting (only by group).
### Billboards
- You can place **multiple** billboards in the scene.
- If a terrain is selected, the billboard will be placed **on top** of the terrain.
- If no terrain is selected, the billboard will be placed at **XYZ(0,0,0)**.
- Every placed billboard can be **edited** (position, rotation, size, deleting).
- Billboards will **NOT** be affected by scene lighting.
- Every billboard's **AABB** will be scaled based on their rotation.
- Placed billboards are not meant for individual interactions through scripting (only by group).
### Lights
- You can add **ambient lighting** which has a custom color & intensity.
- You can add **directional lighting** which has a custom color, intensity and position.
- Directional lighting also has the option to show a lightsource circle billboard (with custom intensity).
- You can place **multiple point lights** in the scene.
- If a terrain is selected, the point light will be placed **on top** of the terrain.
- If no terrain is selected, the point light will be placed at **XYZ(0,0,0)**.
- Every placed point light can be **edited** (position, max distance, intensity, color, deleting).
- Placed lights are not meant for individual interactions through scripting.
### Audio
- You can place **multiple** 3D audio casters in the scene
- If a terrain is selected, the audio caster will be placed **on top** of the terrain.
- If no terrain is selected, the audio caster will be placed at **XYZ(0,0,0)**.
- Every placed audio caster can be **edited** (position, max volume, max distance, deleting).
- Placed audio casters are not meant for individual interactions through scripting.
### Graphics
- You can add **shadows** to scene based on (casting position, box size, box center, option to follow camera + interval).
- You can enable **motion blur** with a custom strength.
- You can enable dynamic Depth Of Field (**DOF**) based on (min distance, blur distance) or enable a static **distant blur**.
- You can enable **fog** based on (min distance, max distance, intensity, color).
- You can enable **dynamic skyHDR** based on (max extra intensity).
- You can enable a **lens flare** for directional lighting based on (flare map, intensity, multiplier).
- **Flare map**: colored 24bit `PNG` format image file from `game_assets\textures\flare_maps`.
### Other settings
- You can change the editor movement speed, which will be saved for next time.
- You can set the minimum distance by which level of detailed models will change their rendering.