# Uncategorized scripting functions

## Setters

- `fe3d:application_stop` () -----> `NONE`
- `fe3d:print` (`STR` value) -----> `NONE`
- `fe3d:print` (`DEC` value) -----> `NONE`
- `fe3d:print` (`INT` value) -----> `NONE`
- `fe3d:print` (`BOL` value) -----> `NONE`
- `fe3d:cursor_set_visible` (`BOL` value) -----> `NONE`
- `fe3d:cursor_set_position` (`DEC` x, `DEC` y) -----> `NONE`
- `fe3d:cursor_set_type` (`STR` type) -----> `NONE`
- `fe3d:vsync_set_enabled` (`BOL` value) -----> `NONE`

## Getters

- `fe3d:vsync_is_enabled` () -----> `BOL`
- `fe3d:time_is_passed` (`INT` update_count) -----> `BOL`
- `fe3d:cursor_is_visible` () -----> `BOL`
- `fe3d:cursor_get_position_x` () -----> `DEC`
- `fe3d:cursor_get_position_y` () -----> `DEC`
- `fe3d:cursor_get_type` () -----> `STR`
- `fe3d:window_get_width` () -----> `INT`
- `fe3d:window_get_height` () -----> `INT`
- `fe3d:window_get_aspect_ratio` () -----> `DEC`
