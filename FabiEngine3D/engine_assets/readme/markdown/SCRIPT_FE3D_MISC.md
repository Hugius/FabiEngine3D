# Miscellaneous
- `fe3d:game_pause`() ---> `NONE`  
  Pauses all internal game/engine updates if playing (except for the scripting of course).
- `fe3d:game_unpause`() ---> `NONE`  
  Unpauses all internal game/engine updates if paused.
- `fe3d:game_stop`() ---> `NONE`  
  Stops the game.
- `fe3d:print`(`VEC3/STR/DEC/INT/BOOL` message) ---> `NONE`  
  Prints a value to the console (both internal & external). Accepts various message types.
- `fe3d:scene_load`(`STR` ID) ---> `NONE`  
  Loads an editor scene with **ID** into the game. Any previously loaded scene will be cleared.
- `fe3d:scene_get_current_id`() ---> `STR`  
  Returns ID of currently loaded scene.
- `fe3d:scene_clear`() ---> `NONE`  
  Deletes all sky, terrain, water, models, billboards, audio, lights from the currently loaded scene.
- `fe3d:scene_is_custom_existing`(`STR` ID) ---> `BOOL`  
  Returns true if custom scene with **ID** is existing.
- `fe3d:scene_create_custom`(`STR` ID) ---> `NONE`  
  Creates a new custom scene as **ID**.
- `fe3d:scene_add_custom_sky`() ---> `NONE`  
  Queues sky environment to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_terrain`() ---> `NONE`  
  Queues terrain environment to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_water`() ---> `NONE`  
  Queues water environment to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_model`(`STR` modelID) ---> `NONE`  
  Queues **modelID** to be saved in the custom scene, including animation if started (does not have to exist yet).
- `fe3d:scene_add_custom_billboard`(`STR` billboardID) ---> `NONE`  
  Queues **billboardID** to be saved in the custom scene, including animation if started (does not have to exist yet).
- `fe3d:scene_add_custom_aabb`(`STR` aabbID) ---> `NONE`  
  Queues non-bound **aabbID** to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_sound`(`STR` soundID) ---> `NONE`  
  Queues 3D **soundID** to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_light`(`STR` lightID) ---> `NONE`  
  Queues **lightID** to be saved in the custom scene (does not have to exist yet).
- `fe3d:scene_add_custom_lighting`() ---> `NONE`  
  Queues ambient lighting + directional lighting to be saved in the custom scene.
- `fe3d:scene_add_custom_graphics`() ---> `NONE`  
  Queues graphical settings (shadows, motion blur, DOF, fog, lens flare, skyHDR) to be saved in the custom scene.
- `fe3d:scene_save_custom`() ---> `NONE`  
  Saves current custom scene to a file as ID in `projects\<your_project>\scenes\custom\`.
- `fe3d:scene_load_custom`(`STR` ID) ---> `NONE`  
  Loads a customly saved scene with **ID** into the game. Any previously loaded scene will be cleared.
- `fe3d:scene_delete_custom`(`STR` ID) ---> `NONE`  
  Deletes customly saved scene with **ID**.
- `fe3d:cursor_center`() ---> `NONE`  
  Moves the cursor position to the middle of the screen.
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
- `fe3d:wireframe_enable_rendering`() ---> `NONE`  
  Enable wireframe rendering.
- `fe3d:wireframe_disable_rendering`() ---> `NONE`  
  Disable wireframe rendering.
- `fe3d:aabbs_enable_rendering`() ---> `NONE`  
  Enable frame rendering of AABBs.
- `fe3d:aabbs_disable_rendering`() ---> `NONE`  
  Disable frame rendering of AABBs.
- `fe3d:directory_is_existing`(`STR` directoryPath) ---> `BOOL`  
  Returns true if **directoryPath** in `projects\<your_project>\saves\` is existing.
- `fe3d:directory_create`(`STR` directoryPath) ---> `NONE`  
  Creates a new **directoryPath** in `projects\<your_project>\saves\`.
- `fe3d:directory_delete`(`STR` directoryPath) ---> `NONE`  
  Deletes an existing **directoryPath** in `projects\<your_project>\saves\`.
- `fe3d:file_is_existing`(`STR` filePath) ---> `BOOL`  
  Returns true if **filePath** in `projects\<your_project>\saves\` is existing.
- `fe3d:file_read`(`STR` filePath) ---> `LIST`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and returns all lines as a list of strings.
- `fe3d:file_write`(`STR` filePath, `VEC3/STR/DEC/INT/BOOL` content) ---> `NONE`  
  Opens/creates a **filePath** in `projects\<your_project>\saves\` and writes **content** to it.
- `fe3d:file_add_new_line`(`STR` filePath) ---> `NONE`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and writes a new line to it.
- `fe3d:file_clear`(`STR` filePath) ---> `NONE`  
  Opens an existing **filePath** in `projects\<your_project>\saves\` and removes all content.
- `fe3d:file_delete`(`STR` filePath) ---> `NONE`  
  Deletes an existing **filePath** in `projects\<your_project>\saves\`.
