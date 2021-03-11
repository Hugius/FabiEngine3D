#### Collision
- `fe3d:collision_enable_camera_terrain_response`(`DEC` height,  `DEC` speed) ---> `NONE`  
  Enables camera collision with the terrain surface (if existing). **height** is the minimum height the camera should be above the terrain. **speed** is the speed at which the camera corrects its height based on the terrain surface.
- `fe3d:collision_disable_camera_terrain_response`() ---> `NONE`  
  Disables camera collision with the terrain surface (if existing).
- `fe3d:collision_is_camera_under_terrain`() ---> `BOOL`  
  Returns true if the camera is under the terrain surface (if existing).
- `fe3d:collision_set_camera_box`(`DEC` bottom, `DEC` top, `DEC` left, `DEC` right, `DEC` front, `DEC` back) ---> `NONE`  
  Defines the dimensions of the bounding box around the camera. All parameters are offsets from the camera position.
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