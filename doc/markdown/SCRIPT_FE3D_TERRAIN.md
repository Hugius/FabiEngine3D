# Terrain Scripting Functions

## Setters

- `fe3d:terrain_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:terrain_select` (`STR` id) -----> `NONE`
- `fe3d:terrain_set_lightness` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:terrain_set_max_height` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:terrain_set_diffuse_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_normal_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_blend_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_red_diffuse_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_green_diffuse_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_blue_diffuse_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_red_normal_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_green_normal_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_blue_normal_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:terrain_set_wireframe_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:terrain_set_specular_shininess` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:terrain_set_specular_intensity` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:terrain_set_texture_repeat` (`STR` id, `INT` value) -----> `NONE`
- `fe3d:terrain_set_red_repeat` (`STR` id, `INT` value) -----> `NONE`
- `fe3d:terrain_set_green_repeat` (`STR` id, `INT` value) -----> `NONE`
- `fe3d:terrain_set_blue_repeat` (`STR` id, `INT` value) -----> `NONE`
- `fe3d:terrain_set_specular` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:terrain_set_wireframed` (`STR` id, `BOL` value) -----> `NONE`

## Getters

- `fe3d:terrain_get_selected_id` (`STR` id) -----> `STR`
- `fe3d:terrain_get_pixel_height` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_height_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_diffuse_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_normal_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_blend_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_red_diffuse_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_green_diffuse_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_blue_diffuse_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_red_normal_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_green_normal_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_get_blue_normal_map_path` (`STR` id) -----> `STR`
- `fe3d:terrain_has_diffuse_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_normal_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_blend_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_red_diffuse_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_green_diffuse_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_blue_diffuse_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_red_normal_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_green_normal_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_has_blue_normal_map` (`STR` id) -----> `BOL`
- `fe3d:terrain_get_max_height` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_size` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_lightness` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_specular_shininess` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_specular_intensity` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_wireframe_color_r` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_wireframe_color_g` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_wireframe_color_b` (`STR` id) -----> `DEC`
- `fe3d:terrain_get_texture_repeat` (`STR` id) -----> `INT`
- `fe3d:terrain_get_red_repeat` (`STR` id) -----> `INT`
- `fe3d:terrain_get_green_repeat` (`STR` id) -----> `INT`
- `fe3d:terrain_get_blue_repeat` (`STR` id) -----> `INT`
- `fe3d:terrain_is_specular` (`STR` id) -----> `BOL`
- `fe3d:terrain_is_wireframed` (`STR` id) -----> `BOL`
