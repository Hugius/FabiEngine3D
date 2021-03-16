# Light
- `fe3d:light_is_existing`() ---> `BOOL`  
  Returns true if light is existing.
- `fe3d:light_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all lights which IDs start with **subID**.
- `fe3d:light_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all light.
- `fe3d:light_place`(`STR` newID, `DEC` x, `DEC` y, `DEC` z, `DEC` r, `DEC` g, `DEC` b, `DEC` intensity, `DEC` distance) ---> `NONE`  
  Places a new light with **newID** (cannot start with @) at position as **xyz** with color as **rgb**. It also has an **intensity** and maximum **distance**.
- `fe3d:light_delete`(`STR` ID) ---> `NONE`  
  Deletes light with **ID** if existing.
- `fe3d:light_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of light with **ID** to **visible**.
- `fe3d:light_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if light with **ID** is visible.
- `fe3d:light_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of light with **ID**.
- `fe3d:light_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the light with factor **xyz** of light with **ID**.
- `fe3d:light_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of light with **ID**.
- `fe3d:light_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of light with **ID**.
- `fe3d:light_get_color`(`STR` ID) ---> `DEC`  
  Returns the color of light with **ID**.
- `fe3d:light_set_intensity`(`STR` ID, `DEC` intensity) ---> `NONE`  
  Sets the **intensity** of light with **ID**.
- `fe3d:light_get_intensity`(`STR` ID) ---> `DEC`  
  Returns the intensity of light with **ID**.
- `fe3d:light_set_distance`(`STR` ID, `DEC` distance) ---> `NONE`  
  Sets the **distance** of light with **ID**.
- `fe3d:light_get_distance`(`STR` ID) ---> `DEC`  
  Returns the distance of light with **ID**.
