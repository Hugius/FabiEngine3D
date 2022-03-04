# Pointlight Scripting Functions

## Setters

- `fe3d:pointlight_place` (`STR` new_id, `DEC` position_x, `DEC` position_y, `DEC` position_z, `DEC` radius_x, `DEC` radius_y, `DEC` radius_z, `DEC` color_r, `DEC` color_g, `DEC` color_b, `DEC` intensity) -----> `NONE`
- `fe3d:pointlight_delete` (`STR` id) -----> `NONE`
- `fe3d:pointlight_delete_all` () -----> `NONE`
- `fe3d:pointlight_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:pointlight_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:pointlight_set_radius` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:pointlight_set_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:pointlight_set_intensity` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:pointlight_set_shape` (`STR` id, `STR` value) -----> `NONE`

## Getters

- `fe3d:pointlight_is_visible` (`STR` id) -----> `BOL`
- `fe3d:pointlight_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_radius_x` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_radius_y` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_radius_z` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_color_r` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_color_g` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_color_b` (`STR` id) -----> `DEC`
- `fe3d:pointlight_is_existing` (`STR` id) -----> `BOL`
- `fe3d:pointlight_find_ids` (`STR` id) -----> `LIST`
- `fe3d:pointlight_get_ids` () -----> `LIST`
- `fe3d:pointlight_get_intensity` (`STR` id) -----> `DEC`
- `fe3d:pointlight_get_shape` (`STR` id) -----> `STR`
