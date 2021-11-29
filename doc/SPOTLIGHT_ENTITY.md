# Spotlight Entity

## 1. General

- The spotlight entity is a 3D light in 3D space.
- Emitted light is casted in a direction from a position.

## 2. Properties

### 2.1 `decimal3`

- **Position**: the XYZ position of the light
  - Constraints: none
- **Position Target**: the target XYZ position of the light
  - Constraints: none
- **Front Vector**: the normalized vector of the light direction
  - Constraints: at least `0.0`
- **Color**: the RGB color multiplier of the fragments
  - Constraints: between `0.0` to `1.0`

### 2.2 `decimal`

- **Position Target Speed**: the speed with which the light moves to the target position
  - Constraints: at least `0.0`
- **Intensity**: the intensity of the light emission
  - Constraints: at least `0.0`
- **Yaw**: the horizontal rotation of the light direction
  - Constraints: between `0.0` and `360.0`
- **Pitch**: the vertical rotation of the light direction
  - Constraints: between `0.0` and `360.0`
- **Angle**: the angle of the light direction
  - Constraints: between `0.0` and `45.0`
- **Distance**: the maximum distance of the light emission
  - Constraints: at least `0.0`
