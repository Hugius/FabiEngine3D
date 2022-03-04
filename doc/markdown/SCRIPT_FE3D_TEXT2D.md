# Text2D Scripting Functions

## Setters

- `fe3d:text2d_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:text2d_delete` (`STR` id) -----> `NONE`
- `fe3d:text2d_delete_all` () -----> `NONE`
- `fe3d:text2d_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_position` (`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_set_rotation` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:text2d_set_size` (`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_move` (`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_rotate` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:text2d_scale` (`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:text2d_rotate_to` (`STR` id, `DEC` target, `DEC` speed) -----> `NONE`
- `fe3d:text2d_scale_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:text2d_set_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text2d_set_wireframe_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text2d_set_opacity` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:text2d_set_wireframed` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_horizontally_flipped` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_vertically_flipped` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_content` (`STR` id, `STR` value) -----> `NONE`

## Getters

- `fe3d:text2d_is_visible` (`STR` id) -----> `BOL`
- `fe3d:text2d_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_rotation` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_size_x` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_size_y` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_color_r` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_color_g` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_color_b` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_r` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_g` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_b` (`STR` id) -----> `DEC`
- `fe3d:text2d_get_opacity` (`STR` id) -----> `DEC`
- `fe3d:text2d_is_horizontally_flipped` (`STR` id) -----> `BOL`
- `fe3d:text2d_is_vertically_flipped` (`STR` id) -----> `BOL`
- `fe3d:text2d_is_wireframed` (`STR` id) -----> `BOL`
- `fe3d:text2d_is_existing` (`STR` id) -----> `BOL`
- `fe3d:text2d_find_ids` (`STR` id) -----> `LIST`
- `fe3d:text2d_get_ids` () -----> `LIST`
- `fe3d:text2d_get_content` (`STR` id) -----> `STR`
- `fe3d:text2d_get_font_map_path` (`STR` id) -----> `STR`
