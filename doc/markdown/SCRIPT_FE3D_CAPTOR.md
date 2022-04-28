# captor Scripting Functions

## Setters

- `fe3d:captor_place` (`STR` new_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:captor_delete` (`STR` id) -----> `NONE`
- `fe3d:captor_delete_all` () -----> `NONE`
- `fe3d:captor_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:captor_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:captor_capture` (`STR` id) -----> `NONE`
- `fe3d:captor_set_visible` (`STR` id, `BOL` value) -----> `NONE`
- `fe3d:captor_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:captor_set_exception_id` (`STR` id, `STR` value) -----> `NONE`

## Getters

- `fe3d:captor_find_ids` (`STR` id) -----> `LIST`
- `fe3d:captor_is_existing` (`STR` id) -----> `BOL`
- `fe3d:captor_is_visible` (`STR` id) -----> `BOL`
- `fe3d:captor_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:captor_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:captor_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:captor_get_exception_id` (`STR` id) -----> `STR`
- `fe3d:captor_get_ids` () -----> `LIST`
