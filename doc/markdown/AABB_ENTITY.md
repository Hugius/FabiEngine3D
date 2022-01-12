# AABB Entity

## 1 General

- The AABB entity is a 3D cube in 3D space.
- AABB stands for "Axis Aligned Bounding Box".
- An AABB entity can only rotate with angles of 90&deg;
- AABB entities are used for collision and raycasting.
- AABB entities can be bound to a parent entity (model/billboard).
- Bound AABB entities follow the transformation and visibility of their parent entity.
- Bound AABB entities cannot directly be accessed or deleted.

## 2. Properties

- **Position**: the XYZ position of the mesh
  - Type: `decimal3`
  - Constraints: none
- **Size**: the XYZ size of the mesh
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Raycast Responsive**: the mesh is responsive to raycasting
  - Type: `boolean`
  - Constraints: none
- **Collision Responsive**: the mesh is responsive to collision detection/resolving
  - Type: `boolean`
  - Constraints: none
