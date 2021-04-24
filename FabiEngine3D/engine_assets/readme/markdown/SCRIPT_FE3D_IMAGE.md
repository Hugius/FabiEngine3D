# Image
- `fe3d:image_is_existing`() ---> `BOOL`  
  Returns true if image is existing.
- `fe3d:image_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all images which IDs start with **subID**.
- `fe3d:image_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all images.
- `fe3d:image_place`(`STR` newID, `STR` texturePath, `DEC` x, `DEC` y, `DEC` rotation, `DEC` width, `DEC` height) ---> `NONE`  
  Places a new image with **newID** (cannot start with @) with a texture from **texturePath** at position as **xy** with **rotation** and size as **width** & **height**.
- `fe3d:image_delete`(`STR` ID) ---> `NONE`  
  Deletes image with **ID** if existing.
- `fe3d:image_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of image with **ID** to **visible**.
- `fe3d:image_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if image with **ID** is visible.
- `fe3d:image_set_position`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the position as **xy** of image with **ID**.
- `fe3d:image_move`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Moves the image with factor **xy** of image with **ID**.
- `fe3d:image_get_position_x`(`STR` ID) ---> `DEC`  
  Returns the X position of image with **ID**.
- `fe3d:image_get_position_y`(`STR` ID) ---> `DEC`  
  Returns the Y position of image with **ID**.
- `fe3d:image_set_rotation`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Sets the **rotation** of image with **ID**.
- `fe3d:image_rotate`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Rotates the image with factor **rotation** of image with **ID**.
- `fe3d:image_get_rotation`(`STR` ID) ---> `DEC`  
  Returns the rotation of image with **ID**.
- `fe3d:image_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of image with **ID**.
- `fe3d:image_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the image with factor **xy** of image with **ID**.
- `fe3d:image_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of image with **ID**.
- `fe3d:image_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of image with **ID**.
- `fe3d:image_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of image with **ID**.
- `fe3d:image_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of image with **ID**.
- `fe3d:image_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of image with **ID**.
- `fe3d:image_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of image with **ID**.
- `fe3d:image_start_animation`(`STR` ID, `INT` rows, `INT` columns, `INT` framestep, `INT` loops) ---> `NONE`  
  Starts a sprite animation on image with **ID** with an amount **rows** and **columns** in the sprite at speed **framestep** (cannot be lower than 0) and repeats it **loops** times (-1 to play forever, cannot be lower).
- `fe3d:image_pause_animation`(`STR` ID) ---> `NONE`  
  Pauses the playing sprite animation on image with **ID**.
- `fe3d:image_resume_animation`(`STR` ID) ---> `NONE`  
  Resumes the paused sprite animation on image with **ID**.
- `fe3d:image_stop_animation`(`STR` ID) ---> `NONE`  
  Stops the playing sprite animation on image with **ID**.
- `fe3d:image_is_animation_started`(`STR` ID) ---> `BOOL`  
  Returns true if animation on image with **ID** is started.
- `fe3d:image_is_animation_playing`(`STR` ID) ---> `BOOL`  
  Returns true if animation on image with **ID** is playing.
- `fe3d:image_is_animation_paused`(`STR` ID) ---> `BOOL`  
  Returns true if animation on image with **ID** is paused.
- `fe3d:image_set_mirrored_horizontally`(`STR` ID, `BOOL` enabled) ---> `NONE`  
  Sets the horizontal mirroring of image with **ID** to **enabled**.
- `fe3d:image_set_mirrored_vertically`(`STR` ID, `BOOL` enabled) ---> `NONE`  
  Sets the vertical mirroring of image with **ID** to **enabled**.
- `fe3d:image_is_mirrored_horizontally`(`STR` ID) ---> `BOOL`  
  Returns true if image with **ID** is mirrored horizontally.
- `fe3d:image_is_mirrored_vertically`(`STR` ID) ---> `BOOL`  
  Returns true if image with **ID** is mirrored vertically.
