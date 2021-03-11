#### Miscellaneous
- `fe3d:game_pause`() ---> `NONE`  
  Pauses all internal game/engine updates if playing (except for the scripting of course).
- `fe3d:game_unpause`() ---> `NONE`  
  Unpauses all internal game/engine updates if paused.
- `fe3d:game_stop`() ---> `NONE`  
  Stops the game.
- `fe3d:print`(`VEC3/STR/DEC/INT/BOOL` message) ---> `NONE`  
  Prints a value to the console (both internal & external). Accepts various message types.
- `fe3d:scene_load`(`STR` ID) ---> `NONE`  
  Loads the scene with **ID** into the game. Any previously loaded scene will be cleared.
- `fe3d:scene_clear`() ---> `NONE`  
  Deletes (or resets) all stuff in the currently loaded scene (such as models, billboard, graphics, etc).
- `fe3d:scene_get_current_id`() ---> `STR`  
  Returns ID of currently loaded scene.
- `fe3d:cursor_show`() ---> `NONE`  
  Makes mouse cursor visible.
- `fe3d:cursor_hide`() ---> `NONE`  
  Makes mouse cursor invisible.
- `fe3d:cursor_get_position_x`() ---> `DEC`  
  Returns the X position of the cursor (between -1.0 and 1.0).
- `fe3d:cursor_get_position_y`() ---> `DEC`  
  Returns the Y position of the cursor (between -1.0 and 1.0).
- `fe3d:window_get_width`() ---> `INT`  
  Returns window width in pixels.
- `fe3d:window_get_height`() ---> `INT`  
  Returns window height in pixels.
- `fe3d:timer_start`() ---> `NONE`  
  Starts a timer to measure passing time. Works like a stopwatch.
- `fe3d:timer_stop`() ---> `DEC`  
  Returns measured time in milliseconds.
- `fe3d:file_read`(`STR` filePath) ---> `LIST`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and returns all lines as a list of strings.
- `fe3d:file_write`(`STR` filePath, `VEC3/STR/DEC/INT/BOOL` content) ---> `NONE`  
  Opens/creates a **filePath** in `projects\<your_project>\saves\` and writes **content** to it.
- `fe3d:file_add_new_line`(`STR` filePath) ---> `NONE`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and writes a new line to it.
- `fe3d:file_clear`(`STR` filePath) ---> `NONE`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and removes all content.
- `fe3d:file_is_existing`(`STR` filePath) ---> `BOOL`  
  Returns true if **filePath** in `projects\<your_project>\saves\` is existing.