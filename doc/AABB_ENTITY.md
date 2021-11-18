# AABB Entity

## 1 General

- The AABB entity is a 3D cube in 3D space.
- AABB stands for "Axis Aligned Bounding Box".
- AABB entities are used for [collision](https://en.wikipedia.org/wiki/Collision_detection) and [raycasting](https://en.wikipedia.org/wiki/Ray_casting).
- AABB entities can be bound to a parent entity (model/billboard).
- A bound AABB entity will follow the transformation (position/rotation/size) of its parent entity.
- Bound AABB entities follow their parent's rotation (per 90&deg;) in the direction that has the the greatest [reference angle](https://brilliant.org/wiki/reference-angle/).
- If you want to access an individual AABB entity bound to a model entity, its ID is composed like this: `<model_id> + "@" + <aabb_id>`.
- If you want to access an individual AABB entity bound to a bilboard entity, its ID is composed like this: `<billboard_id> + "@" + <aabb_id>`.

## 2. Assets

- Cube Map

## 3. Properties

- **Rotation Speed**: the speed of rotation around the Y axis.
  - Constraints: `-inf` to `inf`
- **Lightness**: the brightness of the sky fragments.
  - Constraints: `0` to `inf`
- **Color**: the RGB color that will be mixed with the sky fragments.
  - Constraints: `0` to `255`
