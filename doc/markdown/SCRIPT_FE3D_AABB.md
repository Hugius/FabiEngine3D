# AABB scripting functions

## Setters

- `fe3d:aabb_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:aabb_delete` (`STR` aabb_id) -----> `NONE`
- `fe3d:aabb_delete_all` () -----> `NONE`
- `fe3d:aabb_move` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_scale` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_move_to` (`STR` aabb_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:aabb_scale_to` (`STR` aabb_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:aabb_set_visible` (`STR` aabb_id, `BOL` value) -----> `NONE`
- `fe3d:aabb_set_position` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_set_size` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_set_color` (`STR` aabb_id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:aabb_set_raycast_responsive` (`STR` aabb_id, `BOL` value) -----> `NONE`
- `fe3d:aabb_set_collision_responsive` (`STR` aabb_id, `BOL` value) -----> `NONE`
- `fe3d:aabb_set_min_clip_position` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:aabb_set_max_clip_position` (`STR` aabb_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`

## Getters

- `fe3d:aabb_find_ids` (`STR` aabb_id) -----> `LST`
- `fe3d:aabb_is_existing` (`STR` aabb_id) -----> `BOL`
- `fe3d:aabb_is_visible` (`STR` aabb_id) -----> `BOL`
- `fe3d:aabb_is_collision_responsive` (`STR` aabb_id) -----> `BOL`
- `fe3d:aabb_is_raycast_responsive` (`STR` aabb_id) -----> `BOL`
- `fe3d:aabb_get_position_x` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_position_y` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_position_z` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_size_x` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_size_y` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_size_z` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_ids` () -----> `LST`
- `fe3d:aabb_get_color_r` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_color_g` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_color_b` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_min_clip_position_x` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_min_clip_position_y` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_min_clip_position_z` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_max_clip_position_x` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_max_clip_position_y` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_max_clip_position_z` (`STR` aabb_id) -----> `DEC`
- `fe3d:aabb_get_editor_id` (`STR` aabb_id) -----> `STR`
