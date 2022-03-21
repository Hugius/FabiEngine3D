# Raycast Scripting Functions

## Setters

- `fe3d:raycast_set_terrain_intersection_enabled` (`BOL` value) -----> `NONE`
- `fe3d:raycast_set_terrain_intersection_distance` (`DEC` value) -----> `NONE`
- `fe3d:raycast_set_terrain_intersection_precision` (`DEC` value) -----> `NONE`
- `fe3d:raycast_set_aabb_intersection_enabled` (`BOL` value) -----> `NONE`

## Getters

- `fe3d:raycast_is_terrain_intersection_enabled` () -----> `BOL`
- `fe3d:raycast_is_aabb_intersection_enabled` () -----> `BOL`
- `fe3d:raycast_is_point_on_terrain_valid` () -----> `BOL`
- `fe3d:raycast_get_cursor_ray_position_x` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_position_y` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_position_z` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_x` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_y` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_z` () -----> `DEC`
- `fe3d:raycast_get_terrain_intersection_distance` () -----> `DEC`
- `fe3d:raycast_get_terrain_intersection_precision` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_x` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_y` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_z` () -----> `DEC`
- `fe3d:raycast_get_closest_model` (`STR` part_id) -----> `STR`
- `fe3d:raycast_get_closest_quad3d` () -----> `STR`
- `fe3d:raycast_get_closest_text3d` () -----> `STR`
- `fe3d:raycast_get_distance_to_model` (`STR` model_id, `STR` part_id) -----> `STR`
- `fe3d:raycast_get_distance_to_quad3d` (`STR` id) -----> `STR`
- `fe3d:raycast_get_distance_to_text3d` (`STR` id) -----> `STR`
