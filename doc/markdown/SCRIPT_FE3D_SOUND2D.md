# Sound2D Scripting Functions

## Setters

- `fe3d:sound2d_place` (`STR` new_id, `STR` editor_id) -----> `NONE`
- `fe3d:sound2d_delete` (`STR` id) -----> `NONE`
- `fe3d:sound2d_delete_all` () -----> `NONE`
- `fe3d:sound2d_start` (`STR` id, `INT` play_count) -----> `NONE`
- `fe3d:sound2d_pause` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound2d_resume` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound2d_stop` (`STR` id, `INT` index) -----> `NONE`
- `fe3d:sound2d_set_volume` (`STR` id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound2d_set_speed` (`STR` id, `INT` index, `DEC` value) -----> `NONE`
- `fe3d:sound2d_set_pitch` (`STR` id, `INT` index, `DEC` value) -----> `NONE`

## Getters

- `fe3d:sound2d_get_volume` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_speed` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_pitch` (`STR` id, `INT` index) -----> `DEC`
- `fe3d:sound2d_get_started_count` (`STR` id) -----> `INT`
- `fe3d:sound2d_is_channel_available` () -----> `BOL`
- `fe3d:sound2d_is_device_connected` () -----> `BOL`
- `fe3d:sound2d_is_existing` (`STR` id) -----> `BOL`
- `fe3d:sound2d_find_ids` (`STR` id) -----> `LIST`
- `fe3d:sound2d_get_ids` () -----> `LIST`
- `fe3d:sound2d_is_started` (`STR` id, `INT` index) -----> `BOL`
- `fe3d:sound2d_is_paused` (`STR` id, `INT` index) -----> `BOL`
- `fe3d:sound2d_get_audio_path` (`STR` id) -----> `STR`
