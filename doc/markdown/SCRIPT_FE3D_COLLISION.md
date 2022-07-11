# Collision Scripting Functions

## Setters

- `fe3d:collision_set_camera_box` (`DEC` left, `DEC` right, `DEC` bottom, `DEC` top, `DEC` back, `DEC` front) -----> `NONE`
- `fe3d:collision_set_camera_terrain_response_height` (`DEC` value) -----> `NONE`
- `fe3d:collision_set_camera_terrain_response_speed` (`DEC` value) -----> `NONE`
- `fe3d:collision_calculate_camera_terrain` (`BOL` value) -----> `NONE`
- `fe3d:collision_calculate_camera_aabb` (`BOL` x, `BOL` y, `BOL` z) -----> `NONE`

## Getters

- `fe3d:collision_check_camera_terrain` () -----> `BOL`
- `fe3d:collision_check_camera_model` (`STR` model_id, `STR` aabb_id, `STR` xyz) -----> `BOL`
- `fe3d:collision_check_camera_quad3d` (`STR` quad_id, `STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_text3d` (`STR` text_id, `STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_aabb` (`STR` aabb_id, `STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_models` (`STR` aabb_id, `STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_quad3ds` (`STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_text3ds` (`STR` xyz) -----> `DEC`
- `fe3d:collision_check_camera_aabbs` (`STR` xyz) -----> `DEC`
- `fe3d:collision_get_camera_terrain_response_height` () -----> `DEC`
- `fe3d:collision_get_camera_terrain_response_speed` () -----> `DEC`
