# Water Scripting Functions

## Setters

- `fe3d:water_place`(`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:water_select`(`STR` id) -----> `NONE`
- `fe3d:water_set_ripple_speed`(`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:water_set_wave_speed`(`STR` id, `DEC` x, `DEC` y) -----> `NONE`
- `fe3d:water_max_depth`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_size`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_dudv_map`(`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:water_set_normal_map`(`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:water_set_displacement_map`(`STR` id, `STR` file_path) -----> `NONE`
- `fe3d:water_set_color`(`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:water_set_wireframe_color`(`STR` id, `DEC` r, `DEC` g, `DEC` b) -----> `NONE`
- `fe3d:water_set_height`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_wave_height`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_texture_repeat`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_specular_shininess`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_specular_intensity`(`STR` id, `DEC` value) -----> `NONE`
- `fe3d:water_set_reflective`(`STR` id, `BOL` value) -----> `NONE`
- `fe3d:water_set_refractive`(`STR` id, `BOL` value) -----> `NONE`
- `fe3d:water_set_specular`(`STR` id, `BOL` value) -----> `NONE`
- `fe3d:water_set_wireframed`(`STR` id, `BOL` value) -----> `NONE`
- `fe3d:water_set_edged`(`STR` id, `BOL` value) -----> `NONE`

## Getters

- `fe3d:water_get_selected_id`(`STR` id) -----> `STR`
- `fe3d:water_get_dudv_map_path`(`STR` id) -----> `STR`
- `fe3d:water_get_displacement_map_path`(`STR` id) -----> `STR`
- `fe3d:water_get_normal_map_path`(`STR` id) -----> `STR`
- `fe3d:water_has_dudv_map`(`STR` id) -----> `BOL`
- `fe3d:water_has_displacement_map`(`STR` id) -----> `BOL`
- `fe3d:water_has_normal_map`(`STR` id) -----> `BOL`
- `fe3d:water_get_max_depth`(`STR` id) -----> `DEC`
- `fe3d:water_get_ripple_speed_x`(`STR` id) -----> `DEC`
- `fe3d:water_get_ripple_speed_y`(`STR` id) -----> `DEC`
- `fe3d:water_get_wave_speed_x`(`STR` id) -----> `DEC`
- `fe3d:water_get_wave_speed_y`(`STR` id) -----> `DEC`
- `fe3d:water_get_height`(`STR` id) -----> `DEC`
- `fe3d:water_get_color_r`(`STR` id) -----> `DEC`
- `fe3d:water_get_color_g`(`STR` id) -----> `DEC`
- `fe3d:water_get_color_b`(`STR` id) -----> `DEC`
- `fe3d:water_get_wireframe_color_r`(`STR` id) -----> `DEC`
- `fe3d:water_get_wireframe_color_g`(`STR` id) -----> `DEC`
- `fe3d:water_get_wireframe_color_b`(`STR` id) -----> `DEC`
- `fe3d:water_get_size`(`STR` id) -----> `DEC`
- `fe3d:water_get_texture_repeat`(`STR` id) -----> `DEC`
- `fe3d:water_get_wave_height`(`STR` id) -----> `DEC`
- `fe3d:water_get_specular_shininess`(`STR` id) -----> `DEC`
- `fe3d:water_get_specular_intensity`(`STR` id) -----> `DEC`
- `fe3d:water_is_reflective`(`STR` id) -----> `BOL`
- `fe3d:water_is_refractive`(`STR` id) -----> `BOL`
- `fe3d:water_is_specular`(`STR` id) -----> `BOL`
- `fe3d:water_is_edged`(`STR` id) -----> `BOL`
- `fe3d:water_is_wireframed`(`STR` id) -----> `BOL`
