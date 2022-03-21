# Reflection Scripting Functions

## Setters

- `fe3d:reflection_place` (`STR` new_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:reflection_delete` (`STR` id) -----> `NONE`
- `fe3d:reflection_delete_all` () -----> `NONE`
- `fe3d:reflection_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:reflection_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:reflection_capture` (`STR` id) -----> `NONE`
- `fe3d:reflection_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:reflection_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:reflection_set_exception_entity_id` (`STR` id, `STR` value) -----> `NONE`

## Getters

- `fe3d:reflection_find_ids` (`STR` id) -----> `LIST`
- `fe3d:reflection_is_existing` (`STR` id) -----> `BOL`
- `fe3d:reflection_is_visible` (`STR` id) -----> `BOL`
- `fe3d:reflection_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:reflection_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:reflection_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:reflection_get_exception_entity_id` (`STR` id) -----> `STR`
- `fe3d:reflection_get_ids` () -----> `LIST`
