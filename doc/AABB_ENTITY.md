# AABB Entity

## 1 General

- The AABB entity is a 3D cube in 3D space.
- AABB stands for "Axis Aligned Bounding Box".
- AABB entities are used for collision and raycasting.
- AABB entities can be bound to a parent entity (model/billboard).
- A bound AABB entity follow the transformation and visibility of its parent entity.
- Bound AABB entities follow their parent's rotation (per 90&deg;) in the direction that has the the greatest reference angle.
- Bound AABB entities cannot be accessed or deleted.

## 2. Properties

- **Parent Entity ID**: the identifier of the parent entity
  - Type: `string`
  - Constraints: entity must exist
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
- **Raycast Responsive**: the mesh is responsive to raycasting
  - Type: `boolean`
  - Constraints: none
- **Collision Responsive**: the mesh is responsive to collision detection/resolving
  - Type: `boolean`
  - Constraints: none
- **Parent Type**: the type of the parent entity
  - Type: `enumeration`
  - Constraints: `MODEL` or `BILLBOARD`
