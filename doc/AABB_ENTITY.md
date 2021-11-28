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

### 2.1 `string`

- **Parent Entity ID**: the identifier of the parent entity
  - Constraints: entity must exist

### 2.2 `decimal3`

- **Local Position**: the local XYZ position of the mesh
  - Constraints: none
- **Local Size**: the local XYZ size multiplier of the mesh
  - Constraints: at least `0.0`
- **Position**: the XYZ position of the mesh
  - Constraints: none
- **Size**: the XYZ size multiplier of the mesh
  - Constraints: at least `0.0`
- **Position Target**: the target XYZ position of the mesh
  - Constraints: none
- **Size Target**: the target XYZ size multiplier of the mesh
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` to `1.0`

### 2.3 `decimal`

- **Position Target Speed**: the speed with which the mesh moves to the target position
  - Constraints: at least `0.0`
- **Size Target Speed**: the speed with which the mesh scales to the target size
  - Constraints: at least `0.0`

### 2.4 `boolean`

- **Follow Parent Transformation**: the mesh is following the transformation of the parent entity
  - Constraints: none
- **Follow Parent Visibility**: the mesh is following the visibility of the parent entity
  - Constraints: none
- **Raycast Responsive**: the mesh is responsive to raycasting
  - Constraints: none
- **Collision Responsive**: the mesh is responsive to collision detection/resolving
  - Constraints: none

### 2.5 `enumeration`

- **Parent Type**: the type of the parent entity
  - Constraints: `MODEL` or `BILLBOARD`
- **Collision Direction**: the direction from which the collision happened
  - Constraints: `X` or `Y` or `Z`
