# Model Editor
![model](FabiEngine3D/engine_assets/readme/model_editor.png)
- You can **create/edit/delete** models that can be placed in scene or placed with scripting.
- A model must **at least** consist of a mesh.
- Textures can be added to the model as well as a custom color.
- Properties include: size, culling, alpha removal, instanced rendering, color, UV-repeat, level of detail.
- Lighting: specular reflection (+ factor & intensity), lightness, shadowed, sky reflection, scene reflection.
- You can also add 1 or more **AABBs** to the model. Every individual box has a position and size.
- All AABBs are bound to the model's transformation (translation, rotation, scaling).
- A mesh should be modeled so that the center is at the **lowest** vertex.
- If you enable the "alpha removal" property, all transparent pixels in the diffuse map(s) will not be rendered. This is useful for transparent backgrounds for example.
- If you enable the "instancing" property, the model will be rendered VERY efficiently if in large numbers. This option will also disable AABB's for this model.
- The "level of detail" property is the name of another model representing a lower quality version of the current model.
### Normal mesh
- **Mesh**: `OBJ` format mesh file from `game_assets\meshes`.
- **Diffuse map**: colored 24bit/32bit `PNG` format image file from `game_assets\textures\diffuse_maps\`.
- **Light map**: colored 24bit `PNG` format image file from `game_assets\textures\light_maps\`.
- **Reflection map**: colored 24bit `PNG` format image file from `game_assets\textures\reflection_maps\`.
- **Normal map**: colored 24bit `PNG` format image file from `game_assets\textures\normal_maps\`.
### Multitextured/multiparted mesh
- A mesh can consist of **multiple parts** (including textures for every part).
- In the **.obj** file, you need to specify when a certain part of vertices starts.
- You can start a new mesh part by writing `FE3D_PART <name>` in the OBJ file.
- You can bind a **diffuse** map to the part by writing `FE3D_DIFFUSE_MAP <path><filename>` on the next line.
- You can bind a **light** map to the part by writing `FE3D_LIGHT_MAP <path><filename>` on the next line.
- You can bind a **reflection** map to the part by writing `FE3D_REFLECTION_MAP <path><filename>` on the next line.
- You can bind a **normal** map to the part by writing `FE3D_NORMAL_MAP <path><filename>` on the next line.