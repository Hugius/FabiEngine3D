# Sound3D Scripting Functions

## Setters

- `fe3d:sound3d_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:sound3d_delete` (`STR` id) -----> `NONE`
- `fe3d:sound3d_delete_all` () -----> `NONE`
- `fe3d:sound3d_start` (`STR` id, `INT` play_count) -----> `NONE`
- `fe3d:sound3d_pause` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound3d_resume` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound3d_stop` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound3d_set_max_volume` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_max_distance` (`STR` id, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_speed` (`STR` id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_pitch` (`STR` id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_position` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:sound3d_move` (`STR` id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:sound3d_move_to` (`STR` id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`

## Getters

- `fe3d:sound3d_get_volume` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_speed` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_pitch` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_started_count` (`STR` id) -----> `INT`
- `fe3d:sound3d_is_channel_available` () -----> `BOL`
- `fe3d:sound3d_is_device_connected` () -----> `BOL`
- `fe3d:sound3d_is_existing` (`STR` id) -----> `BOL`
- `fe3d:sound3d_find_ids` (`STR` id) -----> `LIST`
- `fe3d:sound3d_get_ids` () -----> `LIST`
- `fe3d:sound3d_is_started` (`STR` id, `INT` index) -----> `BOL`
- `fe3d:sound3d_is_paused` (`STR` id, `INT` index) -----> `BOL`
- `fe3d:sound3d_get_audio_path` (`STR` id) -----> `STR`
- `fe3d:sound3d_get_position_x` (`STR` id) -----> `DEC`
- `fe3d:sound3d_get_position_y` (`STR` id) -----> `DEC`
- `fe3d:sound3d_get_position_z` (`STR` id) -----> `DEC`
- `fe3d:sound3d_get_max_volume` (`STR` id) -----> `DEC`
- `fe3d:sound3d_get_max_distance` (`STR` id) -----> `DEC`
