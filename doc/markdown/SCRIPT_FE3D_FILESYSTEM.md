# Water Scripting Functions

## Setters

- `fe3d:directory_create` (`STR` path) -----> `NONE`
- `fe3d:directory_delete` (`STR` path) -----> `NONE`
- `fe3d:file_create` (`STR` path) -----> `NONE`
- `fe3d:file_delete` (`STR` path) -----> `NONE`
- `fe3d:file_write` (`STR` path, `STR` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `DEC` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `INT` value) -----> `NONE`
- `fe3d:file_write` (`STR` path, `BOL` value) -----> `NONE`
- `fe3d:file_clear` (`STR` path) -----> `NONE`

## Getters

- `fe3d:file_read` (`STR` path) -----> `LST`
- `fe3d:directory_is_existing` (`STR` path) -----> `BOL`
- `fe3d:file_is_existing` (`STR` path) -----> `BOL`
