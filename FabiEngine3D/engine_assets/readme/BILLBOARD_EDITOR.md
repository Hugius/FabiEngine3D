# Billboard Editor
![billboard](FabiEngine3D/engine_assets/readme/billboard_editor.png)
- You can **create/edit/delete** billboards that can be placed in a scene or placed with scripting.
- There are 2 types of billboards: text & non-text/textured.
- A text billboard consists of custom (colored) text using a custom loaded **font**.
- A non-text billboard can have a **texture** and/or custom **color**.
- A textured billboard can have a **sprite animation**.
- Properties include: lightness, color, alpha removal, facing camera X/Y.
- When billboard texture is animated, you must specify the amount of rows & columns. You can also set the animation speed.
- Every billboard has its own flat AABB based on their size.
- **Font**: `TTF` format font file from `game_assets\fonts`.
- **Texture**: colored 24bit/32bit `PNG` format image file from `game_assets\textures\billboard_maps`.