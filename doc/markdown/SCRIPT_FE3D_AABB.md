# AABB Scripting Functions

## Setters

- `fe3d:aabb_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:aabb_delete` (`STR` id) -----> `NONE`
- `fe3d:aabb_delete_all` () -----> `NONE`
- `fe3d:aabb_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:aabb_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_set_size` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_scale` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_move_to` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_scale_to` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_set_color` (`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:aabb_set_raycast_responsive` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:aabb_set_collision_responsive` (`STR` id, `BOL` value) -----> `NONE`

## Getters

- `fe3d:aabb_find_ids` (`STR` id) -----> `LIST`
- `fe3d:aabb_is_existing` (`STR` id) -----> `BOL`
- `fe3d:aabb_is_visible` (`STR` id) -----> `BOL`
- `fe3d:aabb_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_size_x` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_size_y` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_size_z` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_ids` () -----> `LIST`
- `fe3d:aabb_is_collision_responsive` (`STR` id) -----> `BOL`
- `fe3d:aabb_is_raycast_responsive` (`STR` id) -----> `BOL`
- `fe3d:aabb_get_color_r` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_color_g` (`STR` id) -----> `DEC`
- `fe3d:aabb_get_color_b` (`STR` id) -----> `DEC`
