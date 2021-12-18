# Animation3D

## 1. General

- Each animation consists of 1 or more keyframes.
- You can create/edit/delete keyframes.
- The first keyframe is always the default model transformation.
- The last keyframe should be the same as the first keyframe.
- If the model is multiparted, each part can be animated independently.

## 2. Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Transformation**: the target transformation
  - Constraints: none
- **Speed**: the speed of the transformation change
  - Constraints: none
- **Rotation origin**: the local origin which the model is rotated around
  - Constraints: none
- **Type**: the type of transformation.
  - Constraints: `MOVE` or `ROTATE` or `SCALE`
- **Type**: the type of speed
  - Constraints: `LINEAR` or `EXPONENT` or `INSTANT`