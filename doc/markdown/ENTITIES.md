# Entities

## 1. General

- In FabiEngine3D, an entity is a thing that can be placed (both 2D and 3D).
- All entities have something to do with rendering.
- Some entities are visible objects.
- All entities have a position, which makes them placeable.
- Every entity must be traceable, which is why they have a unique ID.
- Entities have a lifecycle; they are created/mutated/deleted.

## 2. Properties

- **ID**: the identifier of the entity
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Visible**: the visibility of the entity in the world
  - Type: `boolean`
  - Constraints: none

## 3. Types

- [Sky Entity](SKY_ENTITY.md) (**3D**)
- [Terrain Entity](TERRAIN_ENTITY.md) (**3D**)
- [Water Entity](WATER_ENTITY.md) (**3D**)
- [Model Entity](MODEL_ENTITY.md) (**3D**)
- [Quad3D Entity](QUAD3D_ENTITY.md) (**3D**)
- [Text3D Entity](TEXT3D_ENTITY.md) (**3D**)
- [Quad2D Entity](QUAD2D_ENTITY.md) (**2D**)
- [Text2D Entity](TEXT2D_ENTITY.md) (**2D**)
- [AABB Entity](AABB_ENTITY.md) (**3D**)
- [Pointlight Entity](POINTLIGHT_ENTITY.md) (**3D**)
- [Spotlight Entity](SPOTLIGHT_ENTITY.md) (**3D**)
- [Reflection Entity](REFLECTION_ENTITY.md) (**3D**)
