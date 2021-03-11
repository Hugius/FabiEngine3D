#### Graphics
- `fe3d:graphics_set_ambient_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets ambient lighting color as **rgb**.
- `fe3d:graphics_get_ambient_light_color`() ---> `VEC3`  
  Returns ambient lighting color.
- `fe3d:graphics_set_ambient_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets ambient lighting **intensity**.
- `fe3d:graphics_get_ambient_light_intensity`() ---> `DEC`  
  Returns ambient lighting intensity.
- `fe3d:graphics_set_directional_light_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets directional lighting position as **xyz**.
- `fe3d:graphics_get_directional_light_position`() ---> `VEC3`  
  Returns directional lighting position*.
- `fe3d:graphics_set_directional_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets directional lighting color as **rgb**.
- `fe3d:graphics_get_directional_light_color`() ---> `VEC3`  
  Returns directional lighting color.
- `fe3d:graphics_set_directional_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets directional lighting **intensity**.
- `fe3d:graphics_get_directional_light_intensity`() ---> `DEC`  
  Returns directional lighting intensity.
- `fe3d:graphics_enable_spot_light`() ---> `NONE`  
  Enables spot lighting from camera.
- `fe3d:graphics_disable_spot_light`() ---> `NONE`  
  Disables spot lighting from camera.
- `fe3d:graphics_set_spot_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets spot lighting color as **rgb**.
- `fe3d:graphics_get_spot_light_color`() ---> `VEC3`  
  Returns spot lighting color.
- `fe3d:graphics_set_spot_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets spot lighting **intensity**.
- `fe3d:graphics_get_spot_light_intensity`() ---> `DEC`  
  Returns spot lighting intensity.
- `fe3d:graphics_set_spot_light_angle`(`DEC` angle) ---> `NONE`  
  Sets spot lighting **angle**.
- `fe3d:graphics_get_spot_light_angle`() ---> `DEC`  
  Returns spot lighting angle.
- `fe3d:graphics_set_spot_light_distance`(`DEC` distance) ---> `NONE`  
  Sets spot lighting **distance**.
- `fe3d:graphics_get_spot_light_distance`() ---> `DEC`  
  Returns spot lighting angle.
- `fe3d:graphics_set_fog_min_distance`(`DEC` distance) ---> `NONE`  
  Sets minimum fog **distance**.
- `fe3d:graphics_get_fog_min_distance`() ---> `DEC`  
  Returns minimum fog distance.
- `fe3d:graphics_set_fog_max_distance`(`DEC` distance) ---> `NONE`  
  Sets maximum fog **distance**.
- `fe3d:graphics_get_fog_max_distance`() ---> `DEC`  
  Returns maximum fog distance.
- `fe3d:graphics_set_fog_thickness`(`DEC` thickness) ---> `NONE`  
  Sets fog **thickness** percentage (0.0 - 1.0).
- `fe3d:graphics_get_fog_thickness`() ---> `DEC`  
  Returns fog thickness percentage (0.0 - 1.0).
- `fe3d:graphics_set_fog_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets fog color as **rgb**.
- `fe3d:graphics_get_fog_color`() ---> `VEC3`  
  Returns fog color as **rgb**.
- `fe3d:graphics_set_shadow_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets shadow caster position as **xyz**.
- `fe3d:graphics_get_shadow_position`() ---> `VEC3`  
  Returns shadow caster position.
- `fe3d:graphics_enable_light_mapping`() ---> `NONE`  
  Enables light mapping effect.
- `fe3d:graphics_disable_light_mapping`() ---> `NONE`  
  Disables light mapping effect.
- `fe3d:graphics_enable_point_lighting`() ---> `NONE`  
  Enables point lighting.
- `fe3d:graphics_disable_point_lighting`() ---> `NONE`  
  Disables point lighting.