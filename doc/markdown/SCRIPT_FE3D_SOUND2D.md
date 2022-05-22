# Sound2D Scripting Functions

## Setters

- `fe3d:sound2d_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:sound2d_delete` (`STR` sound_id) -----> `NONE`
- `fe3d:sound2d_delete_all` () -----> `NONE`
- `fe3d:sound2d_start` (`STR` sound_id, `INT` play_count, `INT` start_milliseconds) -----> `NONE`
- `fe3d:sound2d_pause` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound2d_resume` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound2d_stop` (`STR` sound_id, `INT` index) -----> `NONE`
- `fe3d:sound2d_set_volume` (`STR` sound_id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound2d_set_left_intensity` (`STR` sound_id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound2d_set_right_intensity` (`STR` sound_id, `INT` index, `DEC` value) -----> `NONE`

## Getters

- `fe3d:sound2d_find_ids` (`STR` sound_id) -----> `LIST`
- `fe3d:sound2d_is_device_connected` () -----> `BOL`
- `fe3d:sound2d_is_existing` (`STR` sound_id) -----> `BOL`
- `fe3d:sound2d_is_started` (`STR` sound_id, `INT` index) -----> `BOL`
- `fe3d:sound2d_is_paused` (`STR` sound_id, `INT` index) -----> `BOL`
- `fe3d:sound2d_get_volume` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_left_intensity` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_right_intensity` (`STR` sound_id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_current_milliseconds` (`STR` sound_id, `INT` index) -----> `INT`
- `fe3d:sound2d_get_play_count` (`STR` sound_id, `INT` index) -----> `INT`
- `fe3d:sound2d_get_started_count` (`STR` sound_id) -----> `INT`
- `fe3d:sound2d_get_ids` () -----> `LIST`
- `fe3d:sound2d_get_audio_path` (`STR` sound_id) -----> `STR`
