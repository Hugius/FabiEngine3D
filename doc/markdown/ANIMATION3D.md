# Animation3D

## 1. General

- Animation3D is used for creating 3D mesh animations.
- These animations can be applied to model entities.
- Each animation consists of 1 or more frames.
- The first keyframe is always the default model entity transformation.
- The last keyframe should be the same as the first keyframe.
- If the model entity is multiparted, each part can be animated independently.

## 2. Base Properties

- **ID**: the identifier of the animation
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Part IDs**: the identifiers of the animation parts
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Frames**: the frames of the animation

## 3. Frame Properties

- **Transformation**: the target transformation
  - Type: `decimal3`
  - Constraints: none
- **Rotation origin**: the local origin which the model is rotated around
  - Type: `decimal3`
  - Constraints: none
- **Speed**: the speed of the transformation change
  - Type: `decimal3`
  - Constraints: none
- **Transformation Type**: the type of transformation
  - Type: `enumeration`
  - Constraints: `MOVE` or `ROTATE` or `SCALE`
- **Speed Type**: the type of speed
  - Type: `enumeration`
  - Constraints: `LINEAR` or `EXPONENT` or `INSTANT`

## 4. Started Properties

- **Play Count**: the amount of (remaining) times the animation must play
  - Type: `integer`
  - Constraints: at least `-1`
- **Speed Multiplier**: the speed multiplier of the animation
  - Type: `decimal`
  - Constraints: at least `0`
- **Frame Index**: the index of the current animation frame
  - Type: `integer`
  - Constraints: at least `0`
- **Paused**: the animation is paused
  - Type: `boolean`
  - Constraints: none
- **Autopaused**: the animation is automatically paused after the current frame
  - Type: `boolean`
  - Constraints: none
