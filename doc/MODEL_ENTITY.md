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

### 3.1 `string`

- **Mesh Path**: the path of the mesh file
  - Constraints: cannot be changed
- **Diffuse Map Path**: the path of the diffuse map file
  - Constraints: none
- **Emission Map Path**: the path of the emission map file
  - Constraints: none
- **Specular Map Path**: the path of the specular map file
  - Constraints: none
- **Reflection Map Path**: the path of the reflection map file
  - Constraints: none
- **Normal Map Path**: the path of the normal map file
  - Constraints: none
- **LOD Entity ID**: the ID of another model entity representing the LOD version of the current model entity
  - Constraints: entity must exist

### 3.2 `decimal3`

- **Position**: the XYZ position of the mesh
  - Constraints: none
- **Rotation**: the XYZ rotation of the mesh
  - Constraints: between `0.0` and `360.0`
- **Rotation Origin**: the XYZ position that the mesh rotates around
  - Constraints: none
- **Size**: the XYZ size multiplier of the mesh
  - Constraints: at least `0.0`
- **Position Target**: the target XYZ position of the mesh
  - Constraints: none
- **Rotation Target**: the target XYZ rotation of the mesh
  - Constraints: between `0.0` and `360.0`
- **Size Target**: the target XYZ size multiplier of the mesh
  - Constraints: at least `0.0`
- **LOD Size**: the XYZ size multiplier of the LOD entity mesh
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` and `1.0`
- **Wireframe Color**: the RGB color multiplier of the wireframe
  - Constraints: between `0.0` and `1.0`

### 3.3 `decimal`

- **Texture Repeat**: the amount of times the textures are repeated
  - Constraints: at least `0.0`
- **Lightness**: the lightness multiplier of the mesh
  - Constraints: at least `0.0`
- **Specular Shininess**: the shininess of the specular lighting
  - Constraints: at least `0.0`
- **Specular Intensity**: the intensity of the specular lighting
  - Constraints: at least `0.0`
- **Reflectivity**: the percentage of how reflective the mesh is
  - Constraints: between `0.0` and `1.0`
- **Min Height**: the minimum world height from which fragments are visible
  - Constraints: none
- **Max Height**: the maximum world height to which fragments are visible
  - Constraints: none
- **Transparency**: the transparency of the fragments
  - Constraints: between `0.0` and `1.0`
- **Color Inversion**: NOT SURE IF WE NEED TO KEEP IT
  - Constraints: at least `0.0`
- **Emission Intensity**: the intensity of the emission map
  - Constraints: between `0.0` and `1.0`
- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Constraints: at least `0.0`
- **Rotation Target Speed**: the speed with which the mesh rotates to the target rotation
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Constraints: at least `0.0`

### 3.4 `boolean`

- **Specular**: specular lighting is rendered on the mesh
  - Constraints: none
- **Reflective**: cube/planar reflections are rendered on the mesh
  - Constraints: none
- **Instanced**: the mesh is rendered using instanced rendering (disables AABBs)
  - Constraints: none
- **Face Culled**: the mesh uses the face culling optimization
  - Constraints: none
- **Bright**: the mesh is bloomed?? WIP
  - Constraints: none
- **Wireframed**: the mesh is rendered as a wireframe
  - Constraints: none
- **Camera Static**: the mesh is not being affected by the camera position
  - Constraints: none
- **Shadowed**: the mesh is captured for shadow rendering
  - Constraints: none
- **Reflected**: the mesh is captured for reflection rendering
  - Constraints: none

### 3.5 `enumeration`

- **Reflection Type**: the type of reflection
  - Constraints: `CUBE` or `PLANAR`
- **Rotation Order**: the order of directions in which the mesh is rotated
  - Constraints: `XYZ` or `XZY` or `YXZ` or `YZX` or `ZXY` or `ZYX`
