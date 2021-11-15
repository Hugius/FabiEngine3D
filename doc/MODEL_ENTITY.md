# Model Entity

## 1. General

- The model entity is a (complex) 3D object in 3D space.
- The entity cannot exist without having a mesh.
- A model entity uses a variety of textures for a more detailed mesh.

## 2. Resources

- Mesh
- Diffuse map
- Emission map
- Specular map
- Reflection map
- Normal map

## 3. Properties

- **Size**: size multiplier of the mesh.
  - **Constraints**: `0` to `inf`
- **Texture Repeat**: the amount of times the textures are repeated.
  - **Constraints**: `0` to `inf`
- **Color**: the RGB color that will be mixed with the model fragments.
  - **Constraints**: `0` to `255`
- **Lightness**: the brightness of the model fragments.
  - **Constraints**: `0` to `inf`
- **Specular**: enable or disable specular lighting on the model.
  - **Constraints**: `ON` or `OFF`
- **Specular Factor**: the shininess of the specular lighting.
  - **Constraints**: `0` to `256`
- **Specular Intensity**: the intensity of the specular lighting.
  - **Constraints**: `0` to `inf`
- **Reflective**: enable or disable full sky reflection or vertical world reflection.
  - **Constraints**: `ON` or `OFF`
- **Type**: the type of reflection that is rendered onto the model.
  - **Constraints**: `CUBE` or `PLANAR`
- **Reflectivity**: the percentage of how reflective the model is.
  - **Constraints**: `0` to `100`
- **Level Of Detail**: the ID of another model representing the LOD version of the current model. If you want to remove the LOD, fill in "@".
  - **Constraints**: `none`
- **Instanced**: enable or disable instanced rendering for this model (disables AABBs).
  - **Constraints**: `ON` or `OFF`
- **Culling**: enable or disable the face culling performance optimization.
  - **Constraints**: `ON` or `OFF`
- **Rotation**: the order of directions in which the model is rotated.
  - **Constraints**: `XYZ` or `XZY` or `YXZ` or `YZX` or `ZXY` or `ZYX`
