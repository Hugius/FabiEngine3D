# AABB Entity

## 1 General

- The AABB entity is a 3D cube in 3D space.
- AABB stands for "Axis Aligned Bounding Box".
- AABB entities are used for collision and raycasting.
- AABB entities can be bound to a parent entity (model/billboard).
- A bound AABB entity can follow the transformation and visibility of its parent entity.
- Bound AABB entities follow their parent's rotation (per 90&deg;) in the direction that has the the greatest reference angle.
- If you want to access an individual AABB entity bound to a model entity, its ID is composed like this: `<model_id> + "@" + <aabb_id>`.
- If you want to access an individual AABB entity bound to a bilboard entity, its ID is composed like this: `<billboard_id> + "@" + <aabb_id>`.

## 2. Properties

- **Parent Entity ID**: the identifier of the parent entity
  - Type: `string`
  - Constraints: entity must exist
- **Local Position**: the local XYZ position of the mesh
  - Type: `decimal3`
  - Constraints: none
- **Local Size**: the local XYZ size multiplier of the mesh
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Position**: the XYZ position of the mesh
  - Type: `decimal3`
  - Constraints: none
- **Size**: the XYZ size multiplier of the mesh
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Position Target**: the target XYZ position of the mesh
  - Type: `decimal3`
  - Constraints: none
- **Size Target**: the target XYZ size multiplier of the mesh
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Follow Parent Transformation**: the mesh is following the transformation of the parent entity
  - Type: `boolean`
  - Constraints: none
- **Follow Parent Visibility**: the mesh is following the visibility of the parent entity
  - Type: `boolean`
  - Constraints: none
- **Raycast Responsive**: the mesh is responsive to raycasting
  - Type: `boolean`
  - Constraints: none
- **Collision Responsive**: the mesh is responsive to collision detection/resolving
  - Type: `boolean`
  - Constraints: none
- **Parent Type**: the type of the parent entity
  - Type: `enumeration`
  - Constraints: `MODEL` or `BILLBOARD`
- **Collision Direction**: the direction from which the collision happened
  - Type: `enumeration`
  - Constraints: `X` or `Y` or `Z`
