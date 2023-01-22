# Raycast Scripting Functions

## Setters

- `fe3d:raycast_calculate_cursor_ray` () -----> `NONE`
- `fe3d:raycast_calculate_terrain_intersection` (`DEC` max_distance, `DEC` precision) -----> `NONE`
- `fe3d:raycast_calculate_aabbs_intersection` () -----> `NONE`

## Getters

- `fe3d:raycast_is_point_on_terrain_valid` () -----> `BOL`
- `fe3d:raycast_get_cursor_ray_position_x` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_position_y` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_position_z` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_x` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_y` () -----> `DEC`
- `fe3d:raycast_get_cursor_ray_direction_z` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_x` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_y` () -----> `DEC`
- `fe3d:raycast_get_point_on_terrain_z` () -----> `DEC`
- `fe3d:raycast_get_closest_model` (`STR` part_id) -----> `STR`
- `fe3d:raycast_get_closest_quad3d` () -----> `STR`
- `fe3d:raycast_get_closest_text3d` () -----> `STR`
- `fe3d:raycast_get_models` (`STR` part_id) -----> `STR`
- `fe3d:raycast_get_quad3ds` () -----> `STR`
- `fe3d:raycast_get_text3ds` () -----> `STR`
- `fe3d:raycast_get_distance_to_model` (`STR` model_id, `STR` part_id) -----> `DEC`
- `fe3d:raycast_get_distance_to_quad3d` (`STR` quad_id) -----> `DEC`
- `fe3d:raycast_get_distance_to_text3d` (`STR` text_id) -----> `DEC`
