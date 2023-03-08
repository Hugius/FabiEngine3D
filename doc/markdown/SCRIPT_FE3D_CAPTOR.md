# captor scripting functions

## Setters

- `fe3d:captor_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:captor_delete` (`STR` captor_id) -----> `NONE`
- `fe3d:captor_delete_all` () -----> `NONE`
- `fe3d:captor_move` (`STR` captor_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:captor_move_to` (`STR` captor_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:captor_capture` (`STR` captor_id) -----> `NONE`
- `fe3d:captor_set_position` (`STR` captor_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:captor_set_exception_id` (`STR` captor_id, `STR` value) -----> `NONE`
- `fe3d:captor_set_reflection_quality` (`STR` captor_id, `INT` value) -----> `NONE`
- `fe3d:captor_set_refraction_quality` (`STR` captor_id, `INT` value) -----> `NONE`

## Getters

- `fe3d:captor_find_ids` (`STR` captor_id) -----> `LST`
- `fe3d:captor_is_existing` (`STR` captor_id) -----> `BOL`
- `fe3d:captor_get_position_x` (`STR` captor_id) -----> `DEC`
- `fe3d:captor_get_position_y` (`STR` captor_id) -----> `DEC`
- `fe3d:captor_get_position_z` (`STR` captor_id) -----> `DEC`
- `fe3d:captor_get_exception_id` (`STR` captor_id) -----> `STR`
- `fe3d:captor_get_reflection_quality` (`STR` captor_id) -----> `INT`
- `fe3d:captor_get_refraction_quality` (`STR` captor_id) -----> `INT`
- `fe3d:captor_get_ids` () -----> `LST`
- `fe3d:captor_get_editor_id` (`STR` captor_id) -----> `STR`
