# Graphics
- `fe3d:graphics_enable_fog`() ---> `NONE`  
  Enables the fog effect.
- `fe3d:graphics_disable_fog`() ---> `NONE`  
  Disables the fog effect.
- `fe3d:graphics_set_min_fog_distance`(`DEC` distance) ---> `NONE`  
  Sets the minimum fog **distance**.
- `fe3d:graphics_get_min_fog_distance`() ---> `DEC`  
  Returns the minimum fog distance.
- `fe3d:graphics_set_max_fog_distance`(`DEC` distance) ---> `NONE`  
  Sets the maximum fog **distance**.
- `fe3d:graphics_get_max_fog_distance`() ---> `DEC`  
  Returns the maximum fog distance.
- `fe3d:graphics_set_fog_thickness`(`DEC` thickness) ---> `NONE`  
  Sets the fog **thickness** (clamped between 0.0 and 1.0; 0% and 100% respectively).
- `fe3d:graphics_get_fog_thickness`() ---> `DEC`  
  Returns the fog thickness.
- `fe3d:graphics_set_fog_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the fog color as **rgb**.
- `fe3d:graphics_get_fog_color`() ---> `VEC3`  
  Returns the fog color as **rgb**.
- `fe3d:graphics_enable_dof`() ---> `NONE`  
  Enables the DOF effect.
- `fe3d:graphics_disable_dof`() ---> `NONE`  
  Disables the DOF effect.
- `fe3d:graphics_set_dof_dynamic`(`BOOL` dynamic) ---> `NONE`  
  Sets the DOF effect to **dynamic**.
- `fe3d:graphics_is_dof_dynamic`() ---> `BOOL`  
  Returns true if the DOF effect is dynamic.
- `fe3d:graphics_set_max_dof_distance`(`DEC` distance) ---> `NONE`  
  Sets the maximum DOF **distance** to objects.
- `fe3d:graphics_get_max_dof_distance`() ---> `DEC`  
  Returns the maximum DOF distance to objects.
- `fe3d:graphics_set_dof_blur_distance`(`DEC` distance) ---> `NONE`  
  Sets the minmum blurring DOF **distance** to objects.
- `fe3d:graphics_get_dof_blur_distance`() ---> `DEC`  
  Returns the minmum blurring DOF distance to objects.
- `fe3d:graphics_enable_shadows`() ---> `NONE`  
  Enables shadow rendering.
- `fe3d:graphics_disable_shadows`() ---> `NONE`  
  Disables shadow rendering.
- `fe3d:graphics_set_shadow_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the shadow caster position as **xyz**.
- `fe3d:graphics_get_shadow_position`() ---> `VEC3`  
  Returns the shadow caster position.
- `fe3d:graphics_enable_sky_hdr`() ---> `NONE`  
  Enables the dynamic sky HDR effect.
- `fe3d:graphics_disable_sky_hdr`() ---> `NONE`  
  Disables the dynamic sky HDR effect.
- `fe3d:graphics_set_sky_hdr_brightness`(`DEC` brightness) ---> `NONE`  
  Sets the **brightness** of the sky HDR effect.
- `fe3d:graphics_get_max_dof_distance`() ---> `DEC`  
  Returns the brightness of the sky HDR effect.
- `fe3d:graphics_enable_motion_blur`() ---> `NONE`  
  Enables the motion blur effect.
- `fe3d:graphics_disable_motion_blur`() ---> `NONE`  
  Disables the motion blur effect.
- `fe3d:graphics_set_motion_blur_strength`(`DEC` strength) ---> `NONE`  
  Sets the **strength** of the motion blur effect. Cannot be lower than 0.
- `fe3d:graphics_get_motion_blur_strength`() ---> `DEC`  
  Returns the strength of the motion blur effect.
- `fe3d:graphics_enable_lens_flare`() ---> `NONE`  
  Enables the lens flare effect.
- `fe3d:graphics_disable_lens_flare`() ---> `NONE`  
  Disables the lens flare effect.
- `fe3d:graphics_set_lens_flare_map`(`STR` filePath) ---> `NONE`  
  Sets the flare map in **filePath** of the lens flare effect. The base file path is `game_assets\textures\flare_maps`.
- `fe3d:graphics_get_lens_flare_map_path`() ---> `DEC`  
  Returns the file path of the flare map.
- `fe3d:graphics_set_lens_flare_intensity`(`DEC` intensity) ---> `NONE`  
  Sets the lens flare **intensity**.
- `fe3d:graphics_get_lens_flare_intensity`() ---> `DEC`  
  Returns the lens flare intensity.
- `fe3d:graphics_set_lens_flare_multiplier`(`DEC` multiplier) ---> `NONE`  
  Sets the lens flare **multiplier**. Cannot be lower than 0.
- `fe3d:graphics_get_lens_flare_multiplier`() ---> `DEC`  
  Returns the lens flare multiplier.
