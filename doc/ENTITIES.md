# Entities

## 1. General

- In FabiEngine3D, an entity is a thing that can be placed in the world (both 2D and 3D).
- All entities have something to do with rendering.
- Some entities are visible objects.
- All entities have a position, which makes them placeable in the world.
- Every entity must be traceable, which is why they have an ID.
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
- [Billboard Entity](BILLBOARD_ENTITY.md) (**3D**)
- [AABB Entity](AABB_ENTITY.md) (**3D**)
- [Pointlight Entity](POINTLIGHT_ENTITY.md) (**3D**)
- [Spotlight Entity](SPOTLIGHT_ENTITY.md) (**3D**)
- [Reflection Entity](REFLECTION_ENTITY.md) (**3D**)
- [Image Entity](IMAGE_ENTITY.md) (**2D**)
- [Text Entity](TEXT_ENTITY.md) (**2D**)
