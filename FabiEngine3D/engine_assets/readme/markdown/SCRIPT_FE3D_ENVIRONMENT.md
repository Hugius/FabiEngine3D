# Environment
#### Sky
- `fe3d:sky_mix_with_current`(`STR` skyID) ---> `NONE`  
  Blends the selected sky texture with the texture of **skyID**.
- `fe3d:sky_set_mix_value`(`DEC` value) ---> `NONE`  
  Sets the mix **value** to blend the 2 sky textures. The value must be between 0.0 and 1.0 (0% and 100% respectively).
- `fe3d:sky_get_mix_value`() ---> `DEC`  
  Returns the mix value of the selected sky.
- `fe3d:sky_set_rotation_speed`(`DEC` speed) ---> `NONE`  
  Sets the rotation **speed** of the selected sky.
- `fe3d:sky_get_rotation_speed`() ---> `DEC`  
  Returns the rotation speed of the selected sky.
- `fe3d:sky_set_lightness`(`DEC` lightness) ---> `NONE`  
  Sets the **lightness** of the selected sky.
- `fe3d:sky_get_lightness`() ---> `DEC`  
  Returns the lightness of the selected sky.
- `fe3d:sky_set_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of the selected sky.
- `fe3d:sky_get_color`() ---> `VEC3`  
  Returns the color of the selected sky.
#### Terrain
- `fe3d:terrain_get_max_height`() ---> `DEC`  
  Returns the maximum height of the selected terrain (based on the heightmap pixels values).
- `fe3d:terrain_get_size`() ---> `DEC`  
  Returns size of the selected terrain.
- `fe3d:terrain_get_pixel_height`(`DEC` x, `DEC` z) ---> `DEC`  
  Returns the height of the pixel in the selected terrain height map based on X and Z. Returns 0.0 if **x** or **z** is invalid.
#### Water
- `fe3d:water_set_speed`(`DEC` x, `DEC` z) ---> `NONE`  
  Sets the rippling/waving speed of the selected water in the **x** direction and **z** direction.
- `fe3d:water_get_speed_x`() ---> `DEC`  
  Returns the rippling/waving speed of the selected water in the X direction.
- `fe3d:water_get_speed_z`() ---> `DEC`  
  Returns the rippling/waving speed of the selected water in the Z direction.
- `fe3d:water_get_height`() ---> `DEC`  
  Returns the height (Y position) of the selected water.
- `fe3d:water_set_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of the selected water.
- `fe3d:water_get_color`() ---> `VEC3`  
  Returns the color of the selected water.
- `fe3d:water_set_transparency`(`DEC` transparency) ---> `NONE`  
  Sets the **transparency** of the selected water.
- `fe3d:water_get_transparency`() ---> `DEC`  
  Returns the transparency of the selected water.
