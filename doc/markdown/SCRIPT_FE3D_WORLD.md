# World Scripting Functions

## Setters

- `fe3d:world_clear_editor` () -----> `NONE`
- `fe3d:world_load_editor` (`STR` world_id) -----> `NONE`
- `fe3d:world_add_custom_sky` (`STR` sky_id) -----> `NONE`
- `fe3d:world_add_custom_terrain` (`STR` terrain_id) -----> `NONE`
- `fe3d:world_add_custom_water` (`STR` water_id) -----> `NONE`
- `fe3d:world_add_custom_model` (`STR` model_id) -----> `NONE`
- `fe3d:world_add_custom_quad3d` (`STR` quad_id) -----> `NONE`
- `fe3d:world_add_custom_text3d` (`STR` text_id) -----> `NONE`
- `fe3d:world_add_custom_aabb` (`STR` aabb_id) -----> `NONE`
- `fe3d:world_add_custom_pointlight` (`STR` pointlight_id) -----> `NONE`
- `fe3d:world_add_custom_spotlight` (`STR` spotlight_id) -----> `NONE`
- `fe3d:world_add_custom_captor` (`STR` captor_id) -----> `NONE`
- `fe3d:world_add_custom_sound3d` (`STR` sound_id) -----> `NONE`
- `fe3d:world_add_custom_graphics` () -----> `NONE`
- `fe3d:world_reset_custom` () -----> `NONE`
- `fe3d:world_clear_custom` () -----> `NONE`
- `fe3d:world_save_custom` (`STR` world_id) -----> `NONE`
- `fe3d:world_load_custom` (`STR` world_id) -----> `NONE`
- `fe3d:world_delete_custom` (`STR` world_id) -----> `NONE`

## Getters

- `fe3d:world_is_custom_sky_added` (`STR` sky_id) -----> `BOL`
- `fe3d:world_is_custom_terrain_added` (`STR` terrain_id) -----> `BOL`
- `fe3d:world_is_custom_water_added` (`STR` water_id) -----> `BOL`
- `fe3d:world_is_custom_model_added` (`STR` model_id) -----> `BOL`
- `fe3d:world_is_custom_quad3d_added` (`STR` quad_id) -----> `BOL`
- `fe3d:world_is_custom_text3d_added` (`STR` text_id) -----> `BOL`
- `fe3d:world_is_custom_aabb_added` (`STR` aabb_id) -----> `BOL`
- `fe3d:world_is_custom_pointlight_added` (`STR` pointlight_id) -----> `BOL`
- `fe3d:world_is_custom_spotlight_added` (`STR` spotlight_id) -----> `BOL`
- `fe3d:world_is_custom_captor_added` (`STR` captor_id) -----> `BOL`
- `fe3d:world_is_custom_sound3d_added` (`STR` sound_id) -----> `BOL`
- `fe3d:world_is_editor_existing` (`STR` world_id) -----> `BOL`
- `fe3d:world_is_custom_existing` (`STR` world_id) -----> `BOL`
- `fe3d:world_get_current_editor_id` () -----> `STR`
- `fe3d:world_get_current_custom_id` () -----> `STR`
