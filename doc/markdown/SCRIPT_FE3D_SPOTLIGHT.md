# Spotlight Scripting Functions

## Setters

- `fe3d:spotlight_place` (`STR` new_id, `DEC` position_x, `DEC` position_y, `DEC` position_z, `DEC` color_r, `DEC` color_g, `DEC` color_b, `DEC` yaw, `DEC` pitch, `DEC` intensity, `DEC` angle, `DEC` distance) -----> `NONE`
- `fe3d:spotlight_delete` (`STR` id) -----> `NONE`
- `fe3d:spotlight_delete_all` () -----> `NONE`
- `fe3d:spotlight_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:spotlight_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:spotlight_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:spotlight_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:spotlight_set_yaw` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_pitch` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:spotlight_set_intensity` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_angle_` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:spotlight_set_distance` (`STR` id, `DEC` value) -----> `NONE`

## Getters

- `fe3d:spotlight_find_ids` (`STR` id) -----> `LIST`
- `fe3d:spotlight_is_existing` (`STR` id) -----> `BOL`
- `fe3d:spotlight_is_visible` (`STR` id) -----> `BOL`
- `fe3d:spotlight_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_front_x` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_front_y` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_front_z` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_angle` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_distance` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_color_r` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_color_g` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_color_b` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_ids` () -----> `LIST`
- `fe3d:spotlight_get_intensity` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_yaw` (`STR` id) -----> `DEC`
- `fe3d:spotlight_get_pitch` (`STR` id) -----> `DEC`
