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

- [Sky Entity](doc/SKY_ENTITY.md) (**3D**)
- [Terrain Entity](doc/TERRAIN_ENTITY.md) (**3D**)
- [Water Entity](doc/WATER_ENTITY.md) (**3D**)
- [Model Entity](doc/MODEL_ENTITY.md) (**3D**)
- [Billboard Entity](doc/BILLBOARD_ENTITY.md) (**3D**)
- [AABB Entity](doc/AABB_ENTITY.md) (**3D**)
- [Pointlight Entity](doc/POINTLIGHT_ENTITY.md) (**3D**)
- [Spotlight Entity](doc/SPOTLIGHT_ENTITY.md) (**3D**)
- [Reflection Entity](doc/REFLECTION_ENTITY.md) (**3D**)
- [Image Entity](doc/IMAGE_ENTITY.md) (**2D**)
- [Text Entity](doc/TEXT_ENTITY.md) (**2D**)
