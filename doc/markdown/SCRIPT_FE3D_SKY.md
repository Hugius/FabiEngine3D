# Sky Scripting Functions

## Setters

- `fe3d:sky_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:sky_select` (`STR` id) -----> `NONE`
- `fe3d:sky_delete` (`STR` id) -----> `NONE`
- `fe3d:sky_delete_all` () -----> `NONE`
- `fe3d:sky_set_lightness` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:sky_set_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:sky_set_wireframe_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:sky_set_rotation` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:sky_set_wireframed` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:sky_set_left_cube_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_right_cube_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_bottom_cube_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_top_cube_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_back_cube_map` (`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_front_cube_map` (`STR` id, `STR` file_path) -----> `NONE`

## Getters

- `fe3d:sky_find_ids` (`STR` id) -----> `LIST`
- `fe3d:sky_is_wireframed` (`STR` id) -----> `BOL`
- `fe3d:sky_has_left_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_has_right_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_has_bottom_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_has_top_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_has_back_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_has_front_cube_map` (`STR` id) -----> `BOL`
- `fe3d:sky_get_selected_id` (`STR` id) -----> `STR`
- `fe3d:sky_get_lightness` (`STR` id) -----> `DEC`
- `fe3d:sky_get_color_r` (`STR` id) -----> `DEC`
- `fe3d:sky_get_color_g` (`STR` id) -----> `DEC`
- `fe3d:sky_get_color_b` (`STR` id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_r` (`STR` id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_g` (`STR` id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_b` (`STR` id) -----> `DEC`
- `fe3d:sky_get_rotation` (`STR` id) -----> `DEC`
- `fe3d:sky_get_ids` () -----> `LIST`
- `fe3d:sky_get_left_cube_map_path` (`STR` id) -----> `STR`
- `fe3d:sky_get_right_cube_map_path` (`STR` id) -----> `STR`
- `fe3d:sky_get_bottom_cube_map_path` (`STR` id) -----> `STR`
- `fe3d:sky_get_top_cube_map_path` (`STR` id) -----> `STR`
- `fe3d:sky_get_back_cube_map_path` (`STR` id) -----> `STR`
- `fe3d:sky_get_front_cube_map_path` (`STR` id) -----> `STR`
