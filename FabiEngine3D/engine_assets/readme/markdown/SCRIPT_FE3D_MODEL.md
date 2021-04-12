# Model
- `fe3d:model_is_existing`() ---> `BOOL`  
  Returns true if model is existing.
- `fe3d:model_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all models which IDs start with **subID**.
- `fe3d:model_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the IDs of all models.
- `fe3d:model_place`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Places a new model with **newID** (cannot start with @) based on model with **previewID** at position as **xyz**. If the preview model is instanced, the position will be added to the offsets. There can only be 1 instanced model placed in the scene, which has the ID of the first time it is placed (either by scene editor or through this function).
- `fe3d:model_delete`(`STR` ID) ---> `NONE`  
  Deletes model with **ID** if existing.
- `fe3d:model_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of model with **ID** to **visible**.
- `fe3d:model_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if model with **ID** is visible.
- `fe3d:model_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of model with **ID**.
- `fe3d:model_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of model with **ID**.
- `fe3d:model_set_rotation_origin`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation origin of model with **ID** to **xyz** in local space. The model will be rotated around this origin. An xyz of 0 means the rotation will be centered.
- `fe3d:model_get_rotation_origin`() ---> `VEC3`  
  Returns the rotation origin of model with **ID**.
- `fe3d:model_set_rotation`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation as **xyz** of model with **ID**.
- `fe3d:model_rotate`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Rotates the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_rotation`(`STR` ID) ---> `VEC3`  
  Returns the rotation of model with **ID**.
- `fe3d:model_set_size`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the size as **xyz** of model with **ID**.
- `fe3d:model_scale`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Scales the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_size`(`STR` ID) ---> `VEC3`  
  Returns the size of model with **ID**.
- `fe3d:model_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of model with **ID**.
- `fe3d:model_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of model with **ID**.
- `fe3d:model_set_min_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local minimum **height** of model with **ID**. The height is relative to the model position.
- `fe3d:model_get_min_height`(`STR` ID) ---> `DEC`  
  Returns the minimum local height of model with **ID**.
- `fe3d:model_set_max_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local maximum **height** of model with **ID**. The height is relative to the model position.
- `fe3d:model_get_max_height`(`STR` ID) ---> `DEC`  
  Returns the maximum local height of model with **ID**.
- `fe3d:model_set_lightness`(`STR` ID, `DEC` lightness) ---> `NONE`  
  Sets the **lightness** of model with **ID**.
- `fe3d:model_get_lightness`(`STR` ID) ---> `DEC`  
  Returns the lightness of model with **ID**.
- `fe3d:model_set_aabb_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the model's parent AABB raycasting responsiveness to **responsive** of model with **ID**.
- `fe3d:model_set_aabb_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the model's parent AABB collision responsiveness to **responsive** of model with **ID**.
- `fe3d:model_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of model with **ID**. Keep in mind FabiEngine3D does not support transparency sorting!
- `fe3d:model_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of model with **ID**.
  
# Animation
- `fe3d:model_start_animation`(`STR` modelID, `STR` animationID, `INT` loops) ---> `NONE`  
  Starts the animation with **animationID** on model with **modelID** and repeats it **loops** times (-1 to play forever).
- `fe3d:model_pause_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Pauses the playing animation with **animationID** on model with **modelID**.
- `fe3d:model_resume_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Resumes the paused animation with **animationID** on model with **modelID**. Only possible when animation is currently paused.
- `fe3d:model_fade_animation`(`STR` modelID, `STR` animationID, `INT` frameStep) ---> `NONE`  
  Fades the playing animation with **animationID** on model with **modelID** to an end. Every **frameStep** amount of frames the animation will stop.
- `fe3d:model_stop_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Stops the playing animation with **animationID** on model with **modelID**.
- `fe3d:model_is_animation_started`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** was started on model with **modelID**.
- `fe3d:model_is_animation_playing`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** is currently playing on model with **modelID**.
- `fe3d:model_is_animation_paused`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** is currently paused on model with **modelID**.
- `fe3d:model_set_animation_speed`(`STR` modelID, `STR` animationID, `DEC` speed) ---> `NONE`  
  Sets the animation **speed** of animation with **animationID** on model with **modelID**. Cannot be lower than 0.
- `fe3d:model_get_animation_frame_index`(`STR` modelID, `STR` animationID) ---> `INT`  
  Returns the current animation frame index of animation with **animationID** on model with **modelID**. Remember: an index starts at 0!
