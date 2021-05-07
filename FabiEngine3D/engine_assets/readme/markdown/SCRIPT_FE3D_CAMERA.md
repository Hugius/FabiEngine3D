# Camera
- `fe3d:camera_move`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the XYZ camera position with speed **xyz**.
- `fe3d:camera_set_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the XYZ camera position to **xyz**.
- `fe3d:camera_get_position`() ---> `VEC3`  
  Returns the XYZ camera position.
- `fe3d:camera_set_lookat_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the XYZ camera lookat position to **xyz**.
- `fe3d:camera_get_lookat_position`() ---> `VEC3`  
  Return the XYZ camera lookat position.
- `fe3d:camera_follow_x`(`DEC` speed) ---> `NONE`  
  Moves the camera in the X direction relative to where the camera is looking at.
- `fe3d:camera_follow_z`(`DEC` speed) ---> `NONE`  
  Moves the camera in the Z direction relative to where the camera is looking at.
- `fe3d:camera_follow_zy`(`DEC` speed) ---> `NONE`  
  Moves the camera in the Z and Y direction relative to where the camera is looking at.
- `fe3d:camera_set_yaw`(`DEC` degrees) ---> `NONE`  
  Sets the camera yaw in **degrees**.
- `fe3d:camera_get_yaw`() ---> `DEC`  
  Returns the camera yaw in degrees.
- `fe3d:camera_set_pitch`(`DEC` degrees) ---> `NONE`  
  Sets the camera pitch in **degrees**. The angle will be clamped between -90.0 and 90.0.
- `fe3d:camera_get_pitch`() ---> `DEC`  
  Returns the camera pitch in degrees.
- `fe3d:camera_set_fov`(`DEC` degrees) ---> `NONE`  
  Sets the camera fov in **degrees**.
- `fe3d:camera_get_fov`() ---> `DEC`  
  Returns the camera FOV in degrees.
- `fe3d:camera_enable_lookat_view`() ---> `NONE`  
  Enable lookat camera view. The camera will ALWAYS be looking at the lookat position.
- `fe3d:camera_disable_lookat_view`() ---> `NONE`  
  Disable lookat camera view.
- `fe3d:camera_is_lookat_view_enabled`() ---> `BOOL`  
  Returns true if lookat camera view is enabled.
- `fe3d:camera_enable_first_person_view`() ---> `NONE`  
  Enable first person camera view. Cursor movement will determine where the camera will be looking at.
- `fe3d:camera_disable_first_person_view`() ---> `NONE`  
  Disable first person camera view.
- `fe3d:camera_is_first_person_view_enabled`() ---> `BOOL`  
  Returns true if first person camera view is enabled.
- `fe3d:camera_set_cursor_speed`(`DEC` speed) ---> `NONE`  
  Sets the **speed** at which the cursor moves.
- `fe3d:camera_set_max_pitch`(`DEC` degrees) ---> `NONE`  
  Sets the maximum camera pitch in **degrees**.
