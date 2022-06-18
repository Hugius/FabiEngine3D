# Text2D Scripting Functions

## Setters

- `fe3d:text2d_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` size_x, `DEC` size_y) -----> `NONE`
- `fe3d:text2d_delete` (`STR` text_id) -----> `NONE`
- `fe3d:text2d_delete_all` () -----> `NONE`
- `fe3d:text2d_move` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_rotate` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text2d_scale` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_move_to` (`STR` text_id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:text2d_rotate_to` (`STR` text_id, `DEC` target, `DEC` speed) -----> `NONE`
- `fe3d:text2d_scale_to` (`STR` text_id, `DEC` target_x, `DEC` target_y, `DEC` speed) -----> `NONE`
- `fe3d:text2d_set_visible` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_position` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_set_rotation` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text2d_set_size` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_set_color` (`STR` text_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text2d_set_wireframe_color` (`STR` text_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:text2d_set_opacity` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text2d_set_lightness` (`STR` text_id, `DEC` value) -----> `NONE`
- `fe3d:text2d_set_wireframed` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_horizontally_flipped` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_vertically_flipped` (`STR` text_id, `BOL` value) -----> `NONE`
- `fe3d:text2d_set_content` (`STR` text_id, `STR` value) -----> `NONE`
- `fe3d:text2d_set_min_clip_position` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:text2d_set_max_clip_position` (`STR` text_id, `DEC` x, `DEC` y) -----> `NONE`

## Getters

- `fe3d:text2d_find_ids` (`STR` text_id) -----> `LST`
- `fe3d:text2d_is_visible` (`STR` text_id) -----> `BOL`
- `fe3d:text2d_is_horizontally_flipped` (`STR` text_id) -----> `BOL`
- `fe3d:text2d_is_vertically_flipped` (`STR` text_id) -----> `BOL`
- `fe3d:text2d_is_wireframed` (`STR` text_id) -----> `BOL`
- `fe3d:text2d_is_existing` (`STR` text_id) -----> `BOL`
- `fe3d:text2d_get_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_position_y` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_rotation` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_size_x` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_size_y` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_color_r` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_color_g` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_color_b` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_r` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_g` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_wireframe_color_b` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_opacity` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_lightness` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_ids` () -----> `LST`
- `fe3d:text2d_get_content` (`STR` text_id) -----> `STR`
- `fe3d:text2d_get_font_map_path` (`STR` text_id) -----> `STR`
- `fe3d:text2d_get_min_clip_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_min_clip_position_y` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_max_clip_position_x` (`STR` text_id) -----> `DEC`
- `fe3d:text2d_get_max_clip_position_y` (`STR` text_id) -----> `DEC`
