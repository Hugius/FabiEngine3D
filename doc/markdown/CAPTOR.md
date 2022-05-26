# Captor

## 1. General

- The captor is a 3D "camera" in 3D space.
- Everything around the is captured into an internal cube map.
- The cube map is used for cube reflections/refractions.
- The ID of a captor cannot be empty or contain spaces/capitals/specials.

## 2. Properties

- **ID**: the identifier of the captor
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Exception ID**: the ID of a model that cannot be captured in the reflection/refraction
  - Type: `string`
  - Constraints: none
- **Position**: the XYZ position of the captor
  - Type: `decimal3`
  - Constraints: none
- **Reflection Quality**: the quality of the reflection
  - Type: `integer`
  - Constraints: between `128` and `1024`
- **Reflection Quality**: the quality of the refraction
  - Type: `integer`
  - Constraints: between `128` and `1024`
