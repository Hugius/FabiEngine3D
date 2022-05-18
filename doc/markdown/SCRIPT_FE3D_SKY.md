# Sky Scripting Functions

## Setters

- `fe3d:sky_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:sky_select` (`STR`sky_id) -----> `NONE`
- `fe3d:sky_delete` (`STR`sky_id) -----> `NONE`
- `fe3d:sky_delete_all` () -----> `NONE`
- `fe3d:sky_set_lightness` (`STR`sky_id, `DEC` value) -----> `NONE`
- `fe3d:sky_set_color` (`STR`sky_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:sky_set_wireframe_color` (`STR`sky_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:sky_set_rotation` (`STR`sky_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:sky_rotate` (`STR`sky_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:sky_rotate_to` (`STR`sky_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:sky_set_wireframed` (`STR`sky_id, `DEC` value) -----> `NONE`
- `fe3d:sky_set_left_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_right_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_bottom_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_top_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_back_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_front_cube_map` (`STR`sky_id, `STR` file_path) -----> `NONE`
- `fe3d:sky_set_rotation_order` (`STR`sky_id, `STR` value) -----> `NONE`

## Getters

- `fe3d:sky_find_ids` (`STR`sky_id) -----> `LIST`
- `fe3d:sky_is_wireframed` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_left_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_right_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_bottom_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_top_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_back_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_has_front_cube_map` (`STR`sky_id) -----> `BOL`
- `fe3d:sky_get_selected_id` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_lightness` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_color_r` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_color_g` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_color_b` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_r` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_g` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_wireframe_color_b` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_rotation_x` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_rotation_y` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_rotation_z` (`STR`sky_id) -----> `DEC`
- `fe3d:sky_get_ids` () -----> `LIST`
- `fe3d:sky_get_left_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_right_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_bottom_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_top_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_back_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_front_cube_map_path` (`STR`sky_id) -----> `STR`
- `fe3d:sky_get_rotation_order` (`STR`sky_id) -----> `STR`
