# Pointlight Scripting Functions

## Setters

- `fe3d:pointlight_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:pointlight_delete` (`STR`pointlight_id) -----> `NONE`
- `fe3d:pointlight_move` (`STR`pointlight_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_move_to` (`STR`pointlight_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:pointlight_delete_all` () -----> `NONE`
- `fe3d:pointlight_set_visible` (`STR`pointlight_id, `BOL` value) -----> `NONE`
- `fe3d:pointlight_set_position` (`STR`pointlight_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_set_radius` (`STR`pointlight_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_set_color` (`STR`pointlight_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:pointlight_set_intensity` (`STR`pointlight_id, `DEC` value) -----> `NONE`
- `fe3d:pointlight_set_shape` (`STR`pointlight_id, `STR` value) -----> `NONE`

## Getters

- `fe3d:pointlight_find_ids` (`STR`pointlight_id) -----> `LIST`
- `fe3d:pointlight_is_existing` (`STR`pointlight_id) -----> `BOL`
- `fe3d:pointlight_is_visible` (`STR`pointlight_id) -----> `BOL`
- `fe3d:pointlight_get_position_x` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_position_y` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_position_z` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_radius_x` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_radius_y` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_radius_z` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_color_r` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_color_g` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_color_b` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_ids` () -----> `LIST`
- `fe3d:pointlight_get_intensity` (`STR`pointlight_id) -----> `DEC`
- `fe3d:pointlight_get_shape` (`STR`pointlight_id) -----> `STR`
