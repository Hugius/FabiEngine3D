# Water Scripting Functions

## Setters

- `fe3d:file_write` (`STR` path, `STR` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `DEC` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `INT` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `BOL` value) -----> `NONE`
- `fe3d:file_copy` (`STR` from_path, `STR` to_path) -----> `NONE`
- `fe3d:file_rename` (`STR` old_path, `STR` new_path) -----> `NONE`
- `fe3d:file_delete` (`STR` path) -----> `NONE`

## Getters

- `fe3d:file_read` (`STR` path) -----> `LST`
- `fe3d:file_is_existing` (`STR` path) -----> `BOL`
