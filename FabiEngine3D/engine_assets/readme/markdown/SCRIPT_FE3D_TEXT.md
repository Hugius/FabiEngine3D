# Text
- `fe3d:text_is_existing`() ---> `BOOL`  
  Returns true if text is existing.
- `fe3d:text_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all text which IDs start with **subID**.
- `fe3d:text_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all texts.
- `fe3d:text_place`(`STR` newID, `STR` fontPath, `STR` content, `DEC` x, `DEC` y, `DEC` rotation, `DEC` width, `DEC` height) ---> `NONE`  
  Places a new text (**content**) with **newID** (cannot start with @) with a font from **fontPath** at position as **xy** with **rotation** and size as **width** & **height**.
- `fe3d:text_delete`(`STR` ID) ---> `NONE`  
  Deletes text with **ID** if existing.
- `fe3d:text_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of text with **ID** to **visible**.
- `fe3d:text_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if text with **ID** is visible.
- `fe3d:text_set_position`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the position as **xy** of text with **ID**.
- `fe3d:text_move`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Moves the text with factor **xy** of text with **ID**.
- `fe3d:text_get_position_x`(`STR` ID) ---> `DEC`  
  Returns the X position of text with **ID**.
- `fe3d:text_get_position_y`(`STR` ID) ---> `DEC`  
  Returns the Y position of text with **ID**.
- `fe3d:text_set_rotation`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Sets the **rotation** of text with **ID**.
- `fe3d:text_rotate`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Rotates the text with factor **rotation** of text with **ID**.
- `fe3d:text_get_rotation`(`STR` ID) ---> `DEC`  
  Returns the rotation of text with **ID**.
- `fe3d:text_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of text with **ID**.
- `fe3d:text_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the text with factor **xy** of text with **ID**.
- `fe3d:text_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of text with **ID**.
- `fe3d:text_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of text with **ID**.
- `fe3d:text_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of text with **ID**.
- `fe3d:text_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of text with **ID**.
- `fe3d:text_set_content`(`STR` ID, `STR` content) ---> `NONE`  
  Sets the **content** of text with **ID**.
- `fe3d:text_get_content`(`STR` ID) ---> `DEC`  
  Returns the content of text with **ID**.
- `fe3d:text_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of text with **ID**.
- `fe3d:text_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of text with **ID**.
