# Collision scripting functions

## Setters

- `fe3d:collision_set_camera_box` (`DEC` left_size, `DEC` right_size, `DEC` bottom_size, `DEC` top_size, `DEC` back_size, `DEC` front_size) -----> `NONE`
- `fe3d:collision_calculate_camera_terrain` (`BOL` must_respond, `DEC` response_speed) -----> `NONE`
- `fe3d:collision_calculate_camera_aabbs` (`BOL` must_respond_x, `BOL` must_respond_y, `BOL` must_respond_z) -----> `NONE`
- `fe3d:collision_calculate_model_aabbs` (`STR` model_id) -----> `NONE`
- `fe3d:collision_calculate_quad3d_aabbs` (`STR` quad_id) -----> `NONE`
- `fe3d:collision_calculate_text3d_aabbs` (`STR` text_id) -----> `NONE`
- `fe3d:collision_calculate_aabb_aabbs` (`STR` aabb_id) -----> `NONE`

## Getters

- `fe3d:collision_check_camera_terrain` () -----> `BOL`
- `fe3d:collision_check_camera_models` (`STR` aabb_id, `STR` xyz) -----> `LST`
- `fe3d:collision_check_camera_quad3ds` (`STR` xyz) -----> `LST`
- `fe3d:collision_check_camera_text3ds` (`STR` xyz) -----> `LST`
- `fe3d:collision_check_camera_aabbs` (`STR` xyz) -----> `LST`
- `fe3d:collision_check_camera_model` (`STR` model_id, `STR` aabb_id, `STR` xyz) -----> `BOL`
- `fe3d:collision_check_camera_quad3d` (`STR` quad_id, `STR` xyz) -----> `BOL`
- `fe3d:collision_check_camera_text3d` (`STR` text_id, `STR` xyz) -----> `BOL`
- `fe3d:collision_check_camera_aabb` (`STR` aabb_id, `STR` xyz) -----> `BOL`
- `fe3d:collision_check_model_models` (`STR` model_id, `STR` aabb_id) -----> `LST`
- `fe3d:collision_check_quad3d_quad3ds` (`STR` quad_id) -----> `LST`
- `fe3d:collision_check_text3d_text3ds` (`STR` text_id) -----> `LST`
- `fe3d:collision_check_aabb_aabbs` (`STR` aabb_id) -----> `LST`
- `fe3d:collision_check_model_model` (`STR` model_id, `STR` aabb_id, `STR` model_id, `STR` aabb_id) -----> `BOL`
- `fe3d:collision_check_quad3d_quad3d` (`STR` quad_id, `STR` quad_id) -----> `BOL`
- `fe3d:collision_check_text3d_text3d` (`STR` text_id, `STR` text_id) -----> `BOL`
- `fe3d:collision_check_aabb_aabb` (`STR` aabb_id, `STR` aabb_id) -----> `BOL`
