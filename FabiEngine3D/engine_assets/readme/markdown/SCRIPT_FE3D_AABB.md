# AABB
- `fe3d:aabb_is_existing`() ---> `BOOL`  
  Returns true if AABB is existing.
- `fe3d:aabb_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all AABBs which IDs start with **subID**.
- `fe3d:aabb_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all AABB.
- `fe3d:aabb_place`(`STR` newID, `DEC` x, `DEC` y, `DEC` z, `DEC` width, `DEC` height, `DEC` depth) ---> `NONE`  
  Places a new AABB with **newID** (cannot start with @) with size of **width**, **height**, **depth** at position as **xyz**.
- `fe3d:aabb_delete`(`STR` ID) ---> `NONE`  
  Deletes non-bound AABB with **ID** if existing.
- `fe3d:aabb_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of non-bound AABB with **ID** to **visible**.
- `fe3d:aabb_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if AABB with **ID** is visible.
- `fe3d:aabb_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of non-bound AABB with **ID**.
- `fe3d:aabb_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the non-bound AABB with factor **xyz** of AABB with **ID**.
- `fe3d:aabb_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of AABB with **ID**.
- `fe3d:aabb_set_size`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the size as **xyz** of non-bound AABB with **ID**.
- `fe3d:aabb_scale`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Scales the non-bound AABB with factor **xyz** of AABB with **ID**.
- `fe3d:aabb_get_size`(`STR` ID) ---> `VEC3`  
  Returns the size of AABB with **ID**.
- `fe3d:aabb_set_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the non-bound AABB raycasting responsiveness to **responsive** of AABB with **ID**.
- `fe3d:aabb_set_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the non-bound AABB collision responsiveness to **responsive** of AABB with **ID**.
