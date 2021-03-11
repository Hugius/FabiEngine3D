#### Raycasting
- `fe3d:raycast_enable_terrain_positioning`(`DEC` distance, `DEC` precision) ---> `NONE`  
  Enables raycasting on terrain. Only works when a terrain is selected. **distance** is the maximum distance from the camera towards a point on the terrain. **precision** is how   precise the raycast should be. These values have impact on the performance!
- `fe3d:raycast_disable_terrain_positioning`() ---> `NONE`  
  Disables raycasting on terrain.
- `fe3d:raycast_get_vector`() ---> `VEC3`  
  Returns the raycast vector (from 2D cursor position to 3D ray).
- `fe3d:raycast_get_position_on_terrain`() ---> `VEC3`  
  Returns the 3D raycasted position of the cursor that intersects with the terrain. Returns -1.0 if not intersecting with terrain.
- `fe3d:raycast_is_position_on_terrain_valid`() ---> `BOOL`  
  Returns true if 3D cursor position is valid.
- `fe3d:raycast_into_model`(`STR` model, `STR` aabbpart, `BOOL` occludable) ---> `STR`  
  Returns the ID of the model that is selected. All models which ID starts with **ID** will be checked (leave empty for all models). Only the **aabbpart** will be checked (leave empty for all parts). **occludable** means if the raycast can be blocked by other AABBs.
- `fe3d:raycast_into_models`() ---> `STR`  
  Returns the ID of any model that is selected.
- `fe3d:raycast_into_billboard`(`STR` billboard,  `BOOL` occludable) ---> `STR`  
  Returns the ID of the billboard that is selected. All billboards which ID starts with **ID** will be checked (leave empty for all billboards). **occludable** means if the raycast can be blocked by other AABBs.
- `fe3d:raycast_into_billboards`() ---> `STR`  
  Returns the ID of any billboard that is selected.
- `fe3d:raycast_into_model_distance`(`STR` model, `STR` aabbpart, `BOOL` occludable) ---> `DEC`  
  Returns the distance to the model that is selected. All models which ID starts with **model** will be checked (leave empty for all models). Only the **aabbpart** will be checked (leave empty for all parts). **occludable** means if the raycast can be blocked by other AABBs. Returns -1.0 if the model is not selected.
- `fe3d:raycast_into_models_distance`() ---> `DEC`  
  Returns the distance to any model that is selected. Returns -1.0 if no model is selected.
- `fe3d:raycast_into_billboard_distance`(`STR` billboard,  `BOOL` occludable) ---> `DEC`  
  Returns the distance to the billboard that is selected. All billboards which ID starts with **billboards** will be checked (leave empty for all billboards). **occludable** means if the raycast can be blocked by other AABBs. Returns -1.0 if the billboard is not selected.
- `fe3d:raycast_into_billboards_distance`() ---> `DEC`  
  Returns the distance to any billboard that is selected. Returns -1.0 if the billboard is not selected.
