# Spotlight scripting functions

## Setters

- `fe3d:spotlight_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:spotlight_delete` (`STR` spotlight_id) -----> `NONE`
- `fe3d:spotlight_delete_all` () -----> `NONE`
- `fe3d:spotlight_move` (`STR` spotlight_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:spotlight_move_to` (`STR` spotlight_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:spotlight_set_visible` (`STR` spotlight_id, `BOL` value) -----> `NONE`
- `fe3d:spotlight_set_position` (`STR` spotlight_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:spotlight_set_yaw` (`STR` spotlight_id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_pitch` (`STR` spotlight_id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_color` (`STR` spotlight_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:spotlight_set_intensity` (`STR` spotlight_id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_angle_` (`STR` spotlight_id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_distance` (`STR` spotlight_id, `DEC` value) -----> `NONE`

## Getters

- `fe3d:spotlight_find_ids` (`STR` spotlight_id) -----> `LST`
- `fe3d:spotlight_is_existing` (`STR` spotlight_id) -----> `BOL`
- `fe3d:spotlight_is_visible` (`STR` spotlight_id) -----> `BOL`
- `fe3d:spotlight_get_position_x` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_position_y` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_position_z` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_front_x` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_front_y` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_front_z` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_angle` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_distance` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_color_r` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_color_g` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_color_b` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_ids` () -----> `LST`
- `fe3d:spotlight_get_intensity` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_yaw` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_pitch` (`STR` spotlight_id) -----> `DEC`
- `fe3d:spotlight_get_editor_id` (`STR` spotlight_id) -----> `STR`
