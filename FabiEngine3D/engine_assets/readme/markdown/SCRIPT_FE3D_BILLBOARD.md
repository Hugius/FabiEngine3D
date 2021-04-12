# Billboard
- `fe3d:billboard_is_existing`() ---> `BOOL`  
  Returns true if billboard is existing.
- `fe3d:billboard_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all billboards which IDs start with **subID**.
- `fe3d:billboard_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all billboards.
- `fe3d:billboard_place`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Places a new billboard with **newID** (cannot start with @) based on billboard with **previewID** at position as **xyz**.
- `fe3d:billboard_delete`(`STR` ID) ---> `NONE`  
  Deletes billboard with **ID** if existing.
- `fe3d:billboard_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of billboard with **ID** to **visible**.
- `fe3d:billboard_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is visible.
- `fe3d:billboard_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of billboard with **ID**.
- `fe3d:billboard_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the billboard with factor **xyz** of billboard with **ID**.
- `fe3d:billboard_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of billboard with **ID**.
- `fe3d:billboard_set_rotation`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation as **xyz** of billboard with **ID**.
- `fe3d:billboard_rotate`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Rotates the billboard with factor **xyz** of billboard with **ID**.
- `fe3d:billboard_get_rotation`(`STR` ID) ---> `VEC3`  
  Returns the rotation of billboard with **ID**.
- `fe3d:billboard_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of billboard with **ID**.
- `fe3d:billboard_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the billboard with factor **xy** of billboard with **ID**.
- `fe3d:billboard_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of billboard with **ID**.
- `fe3d:billboard_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of billboard with **ID**.
- `fe3d:billboard_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of billboard with **ID**.
- `fe3d:billboard_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of billboard with **ID**.
- `fe3d:billboard_set_min_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local minimum **height** of billboard with **ID**. The height is relative to the billboard position.
- `fe3d:billboard_get_min_height`(`STR` ID) ---> `DEC`  
  Returns the minimum local height of billboard with **ID**.
- `fe3d:billboard_set_max_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local maximum **height** of billboard with **ID**. The height is relative to the billboard position.
- `fe3d:billboard_get_max_height`(`STR` ID) ---> `DEC`  
  Returns the maximum local height of billboard with **ID**.
- `fe3d:billboard_set_lightness`(`STR` ID, `DEC` lightness) ---> `NONE`  
  Sets the **lightness** of billboard with **ID**.
- `fe3d:billboard_get_lightness`(`STR` ID) ---> `DEC`  
  Returns the lightness of billboard with **ID**.
- `fe3d:billboard_set_aabb_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the billboard's parent AABB raycasting responsiveness to **responsive** of billboard with **ID**.
- `fe3d:billboard_set_aabb_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the billboard's parent AABB collision responsiveness to **responsive** of billboard with **ID**.
- `fe3d:billboard_set_camera_facing_x`(`STR` ID, `BOOL` facing) ---> `NONE`  
  Sets camera **facing** in the X direction for billboard with **ID**.
- `fe3d:billboard_is_facing_camera_x`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is facing the camera in the X direction.
- `fe3d:billboard_set_camera_facing_y`(`STR` ID, `BOOL` facing) ---> `NONE`  
  Sets camera **facing** in the Y direction for billboard with **ID**.
- `fe3d:billboard_is_facing_camera_y`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is facing the camera in the Y direction.
- `fe3d:billboard_start_animation`(`STR` ID, `INT` loops) ---> `NONE`  
  Starts the sprite animation of billboard with **ID** and repeats it **loops** times (-1 to play forever, cannot be lower).
- `fe3d:billboard_pause_animation`(`STR` ID) ---> `NONE`  
  Pauses the playing sprite animation of billboard with **ID**.
- `fe3d:billboard_resume_animation`(`STR` ID) ---> `NONE`  
  Resumes the paused sprite animation of billboard with **ID**.
- `fe3d:billboard_stop_animation`(`STR` ID) ---> `NONE`  
  Stops the playing sprite animation of billboard with **ID**.
- `fe3d:billboard_is_animation_started`(`STR` ID) ---> `BOOL`  
  Returns true if animation of billboard with **ID** was started.
- `fe3d:billboard_is_animation_playing`(`STR` ID) ---> `BOOL`  
  Returns true if animation of billboard with **ID** is currently playing.
- `fe3d:billboard_is_animation_paused`(`STR` ID) ---> `BOOL`  
  Returns true if animation of billboard with **ID** is paused.
- `fe3d:billboard_set_text`(`STR` ID, `STR` text) ---> `NONE`  
  Sets the text content of billboard with **ID**.
- `fe3d:billboard_get_text`(`STR` ID) ---> `STR`  
  Returns the text content of billboard with **ID**.
