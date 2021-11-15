# Entities

## 1. General

- In FabiEngine3D, an entity is a thing that can be placed in the scene (both 2D and 3D).
- Most entities are renderable/visible.
- All entities have a position, which makes them placeable in the scene.
- Every entity must be traceable, which is why they have an ID.
- Entities have a lifecycle; they are created/mutated/deleted.

## 2. Properties

- **ID**: the identifier of the entity.
  - Type: `string`
  - Constraints: must be unique, cannot change
- **Visible**: the visibility of the entity in the scene.
  - Type: `boolean`
  - Constraints: none

## 3. Types

- Sky entity (**3D**)
- Terrain entity (**3D**)
- Water entity (**3D**)
- Model entity (**3D**)
- Billboard entity (**3D**)
- AABB entity (**3D**)
- Pointlight entity (**3D**)
- Spotlight entity (**3D**)
- Reflection entity (**3D**)
- Image entity (**2D**)
- Text entity (**2D**)
