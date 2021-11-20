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

### 3.1 String

- **Level Of Detail**: the ID of another model entity representing the LOD version of the current model entity.
  - Type: `string`
  - Constraints: must exist
- **Rotation**: the order of directions in which the model is rotated.
  - Type: `string`
  - Constraints: `XYZ` or `XZY` or `YXZ` or `YZX` or `ZXY` or `ZYX`

### 3.2 Vector3

- **Position**: the position of the mesh.
  - Type: `vector3`
  - Constraints: none
- **Rotation**: the rotation of the mesh.
  - Type: `vector3`
  - Constraints: between `0.0` and `360.0`
- **Rotation Origin**: the origin that the model rotates around.
  - Type: `vector3`
  - Constraints: none
- **Size**: size multiplier of the mesh.
  - Type: `vector3`
  - Constraints: at least `0.0`
- **Color**: the RGB color of the mesh.
  - Type: `vector3`
  - Constraints: between `0.0` and `1.0`

### 3.3 Vector2

### 3.4 Decimal

- **Texture Repeat**: the amount of times the textures are repeated.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Lightness**: the brightness of the mesh.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Factor**: the shininess of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Specular Intensity**: the intensity of the specular lighting.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Type**: the type of reflection that is rendered onto the model.
  - Type: `decimal`
  - Constraints: `CUBE` or `PLANAR`
- **Reflectivity**: the percentage of how reflective the model is.
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Min Height**: WIP
  - Type: `decimal`
  - Constraints: between `WIP` and `WIP`
- **Max Height**: WIP
  - Type: `decimal`
  - Constraints: between `WIP` and `WIP`
- **Transparency**: the transparency of the mesh.
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`

### 3.5 Integer

### 3.6 Boolean

- **Specular**: enable or disable specular lighting on the model.
  - Type: `boolean`
  - Constraints: none
- **Reflective**: enable or disable full sky reflection or vertical world reflection.
  - Type: `boolean`
  - Constraints: none
- **Instanced**: enable or disable instanced rendering for this model (disables AABBs).
  - Type: `boolean`
  - Constraints: none
- **Culling**: enable or disable the face culling performance optimization.
  - Type: `boolean`
  - Constraints: none
