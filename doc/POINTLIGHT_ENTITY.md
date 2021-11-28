# Pointlight Entity

## 1. General

- The pointlight entity is 3D light in 3D space.
- Emitted light is casted from in all directions from a position.

## 2. Properties

### 2.1 `decimal3`

- **Position**: the XYZ position of the light
  - Constraints: none
- **Position Target**: the target XYZ position of the light
  - Constraints: none
- **Radius**: the XYZ radius of the light emission
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` to `1.0`

### 2.2 `decimal`

- **Position Target Speed**: the speed with which the light moves to the target position
  - Constraints: at least `0.0`
- **Intensity**: the intensity of the light emission
  - Constraints: at least `0.0`

### 2.3 `enumeration`

- **Shape**: the shape of the light
  - Constraints: `CIRCLE` or `SQUARE`
