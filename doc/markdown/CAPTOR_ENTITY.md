# Captor Entity

## 1. General

- The captor entity is a 3D "camera" in 3D space.
- Everything around the entity is captured into an internal cube map.
- The cube map is used for cube reflections.

## 2. Properties

- **Exception ID**: the ID of a model entity that cannot be captured in the reflection
  - Type: `string`
  - Constraints: none
- **Position**: the XYZ position of the captor
  - Type: `decimal3`
  - Constraints: none
