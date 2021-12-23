# Pointlight Entity

## 1. General

- The pointlight entity is 3D light in 3D space.
- Emitted light is casted in all directions from a position.
- Only a maximum of 64 pointlight entities can exist.

## 2. Properties

- **Position**: the XYZ position of the light
  - Type: `decimal3`
  - Constraints: none
- **Position Target**: the target XYZ position of the light
  - Type: `decimal3`
  - Constraints: none
- **Radius**: the XYZ radius of the light emission
  - Type: `decimal3`
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Position Target Speed**: the speed with which the light moves to the target position
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Intensity**: the intensity of the light emission
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Shape**: the shape of the light
  - Type: `enumeration`
  - Constraints: `CIRCLE` or `SQUARE`
