# Pointlight

## 1. General

- The pointlight is a 3D light in 3D space.
- Emitted light is cast in all directions from a position.
- Only a maximum of 64 pointlights can exist.

## 2. Properties

- **ID**: the unique identifier of the pointlight
  - Type: `string`
  - Constraints: cannot be empty or contain spaces/capitals/specials
- **Position**: the XYZ position of the light
  - Type: `decimal3`
  - Constraints: none
- **Radius**: the XYZ radius of the light emission
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the mesh
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Intensity**: the intensity of the light emission
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Visible**: the visibility of the pointlight in the world
  - Type: `boolean`
  - Constraints: none
- **Shape**: the shape of the light
  - Type: `enumeration`
  - Constraints: `CIRCLE` or `SQUARE`
