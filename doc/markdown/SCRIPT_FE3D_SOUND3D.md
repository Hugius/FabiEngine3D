# Sound3D Scripting Functions

## Setters

- `fe3d:sound3d_place` (`STR` new_id, `STR` editor_id, `DEC` position_x, `DEC` position_y, `DEC` position_z) -----> `NONE`
- `fe3d:sound3d_delete` (`STR` sound_id) -----> `NONE`
- `fe3d:sound3d_delete_all` () -----> `NONE`
- `fe3d:sound3d_start` (`STR` sound_id, `INT` play_count, `DEC` start_time) -----> `NONE`
- `fe3d:sound3d_pause` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound3d_resume` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound3d_stop` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound3d_move` (`STR` sound_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`
- `fe3d:sound3d_move_to` (`STR` sound_id, `DEC` target_x, `DEC` target_y, `DEC` target_z, `DEC` speed) -----> `NONE`
- `fe3d:sound3d_set_max_volume` (`STR` sound_id, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_max_distance` (`STR` sound_id, `DEC` value) -----> `NONE`
- `fe3d:sound3d_set_position` (`STR` sound_id, `DEC` x, `DEC` y, `DEC` z) -----> `NONE`

## Getters

- `fe3d:sound3d_find_ids` (`STR` sound_id) -----> `LST`
- `fe3d:sound3d_is_device_connected` () -----> `BOL`
- `fe3d:sound3d_is_existing` (`STR` sound_id) -----> `BOL`
- `fe3d:sound3d_is_started` (`STR` sound_id, `INT` index) -----> `BOL`
- `fe3d:sound3d_is_paused` (`STR` sound_id, `INT` index) -----> `BOL`
- `fe3d:sound3d_get_volume` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_left_intensity` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_right_intensity` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_current_time` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound3d_get_play_count` (`STR` sound_id, `INT` index) -----> `INT`
- `fe3d:sound3d_get_started_count` (`STR` sound_id) -----> `INT`
- `fe3d:sound3d_get_ids` () -----> `LST`
- `fe3d:sound3d_get_audio_path` (`STR` sound_id) -----> `STR`
- `fe3d:sound3d_get_position_x` (`STR` sound_id) -----> `DEC`
- `fe3d:sound3d_get_position_y` (`STR` sound_id) -----> `DEC`
- `fe3d:sound3d_get_position_z` (`STR` sound_id) -----> `DEC`
- `fe3d:sound3d_get_max_volume` (`STR` sound_id) -----> `DEC`
- `fe3d:sound3d_get_max_distance` (`STR` sound_id) -----> `DEC`
