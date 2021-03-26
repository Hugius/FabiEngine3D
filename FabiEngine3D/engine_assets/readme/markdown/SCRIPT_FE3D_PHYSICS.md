# Physics
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

#### Collision
- `fe3d:collision_enable_camera_terrain_response`(`DEC` height,  `DEC` speed) ---> `NONE`  
  Enables camera collision with the terrain surface (if existing). **height** is the minimum height the camera should be above the terrain. **speed** is the speed at which the camera corrects its height based on the terrain surface.
- `fe3d:collision_disable_camera_terrain_response`() ---> `NONE`  
  Disables camera collision with the terrain surface (if existing).
- `fe3d:collision_is_camera_under_terrain`() ---> `BOOL`  
  Returns true if the camera is under the terrain surface (if existing).
- `fe3d:collision_set_camera_box`(`DEC` bottom, `DEC` top, `DEC` left, `DEC` right, `DEC` front, `DEC` back) ---> `NONE`  
  Defines the dimensions of the bounding box around the camera. All parameters are offsets from the camera position. NOTE: this box is NOT an AABB entity.
- `fe3d:collision_enable_camera_aabb_response`(`BOOL` x, `BOOL` y, `BOOL` z) ---> `NONE`  
  Enables collision detection & response between the camera and AABBs. You can specify which directions (**x** and/or **y** and/or **z**) of collision need to be checked.
- `fe3d:collision_disable_camera_aabb_response`() ---> `NONE`  
  Disables collision detection & response between the camera and AABBs.
- `fe3d:collision_check_camera_model`(`STR` model, `STR` aabbpart, `STR` direction) ---> `STR`  
  Returns the ID of the model that has collided with the camera. All models which ID starts with **model** will be checked (leave empty for all models). Only the **aabbpart** part will be checked (leave empty for all parts). You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_models`(`STR` direction) ---> `STR`  
  Return the ID of any model that has collided with the camera. You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_aabb`(`STR` aabbpart, `STR` direction) ---> `STR`  
  Returns the ID of the AABB that has collided with the camera. All AABBs which ID starts with **aabbpart** will be checked (leave empty for all AABBs). You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_aabbs`(`STR` direction) ---> `STR`  
  Return the ID of any AABB that has collided with the camera. You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_model_models`(`STR` model1, `STR` aabbpart1, `STR` model2, `STR` aabbpart2) ---> `STR`  
  Returns the ID of the model that has collided with the **aabbpart1** of **model1**. All models which ID starts with **model2** will be checked (leave empty for all models). Only the **aabbpart2** will be checked (leave empty for all parts).
- `fe3d:collision_check_model_billboards`(`STR` model, `STR` aabbpart, `STR` billboard) ---> `STR`  
  Returns the ID of the billboard that has collided with the **aabbpart** of **model**. All billboards which ID starts with **billboard** will be checked (leave empty for all billboards).
- `fe3d:collision_check_model_aabbs`(`STR` model, `STR` aabbpart, `STR` aabb) ---> `STR`  
  Returns the ID of the AABB that has collided with the **aabbpart** of **model**. All AABBs which ID starts with **aabb** will be checked (leave empty for all AABBs).
