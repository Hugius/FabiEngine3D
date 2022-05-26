# Spotlight

## 1. General

- The spotlight is a 3D light in 3D space.
- Emitted light is cast in a direction from a position.
- Only a maximum of 64 spotlights can exist.
- The ID of a spotlight cannot be empty or contain spaces/capitals/specials.

## 2. Properties

- **ID**: the identifier of the spotlight
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Position**: the XYZ position of the light
  - Type: `decimal3`
  - Constraints: none
- **Front**: the normalized vector of the light direction
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Intensity**: the intensity of the light emission
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Yaw**: the horizontal rotation of the light direction
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Pitch**: the vertical rotation of the light direction
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Angle**: the angle of the light direction
  - Type: `decimal`
  - Constraints: between `0.0` and `45.0`
- **Distance**: the maximum distance of the light emission
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Visible**: the visibility of the spotlight in the world
  - Type: `boolean`
  - Constraints: none
