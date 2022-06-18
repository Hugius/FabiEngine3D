# Water Scripting Functions

## Setters

- `fe3d:clock_create` (`STR` clock_id) -----> `NONE`
- `fe3d:clock_delete` (`STR` clock_id) -----> `NONE`
- `fe3d:clock_delete_all` () -----> `NONE`
- `fe3d:clock_start` (`STR` clock_id) -----> `NONE`
- `fe3d:clock_pause` (`STR` clock_id) -----> `NONE`
- `fe3d:clock_resume` (`STR` clock_id) -----> `NONE`
- `fe3d:clock_stop` (`STR` clock_id) -----> `NONE`

## Getters

- `fe3d:clock_find_ids` (`STR` clock_id) -----> `LST`
- `fe3d:clock_is_existing` (`STR` clock_id) -----> `BOL`
- `fe3d:clock_is_started` (`STR` clock_id) -----> `BOL`
- `fe3d:clock_is_paused` (`STR` clock_id) -----> `BOL`
- `fe3d:clock_get_delta_time` (`STR` clock_id) -----> `DEC`
- `fe3d:clock_get_ids` () -----> `LST`
