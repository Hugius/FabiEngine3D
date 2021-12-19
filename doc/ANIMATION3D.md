# Animation3D

## 1. General

- Each animation consists of 1 or more keyframes.
- You can create/edit/delete keyframes.
- The first keyframe is always the default model transformation.
- The last keyframe should be the same as the first keyframe.
- If the model is multiparted, each part can be animated independently.

## 2. Animation Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
  - Write Access: editor
  - Read Access: editor + script
- **Speed Multiplier**: the speed of the animation
  - Type: `decimal`
  - Constraints: at least `0`
  - Write Access: script
  - Read Access: script
- **Times To Play**: the amount of times the animation is playing
  - Type: `integer`
  - Constraints: `-1` or at least `0`
  - Write Access: script
  - Read Access: script
- **Paused**: the animation is paused
  - Type: `boolean`
  - Constraints: none
  - Write Access: script
  - Read Access: script
- **Auto Paused**: the animation is automatically paused
  - Type: `boolean`
  - Constraints: none
  - Write Access: script
  - Read Access: script

## 3. Frame Properties

- **Transformation**: the target transformation
  - Type: `boolean`
  - Constraints: none
- **Rotation origin**: the local origin which the model is rotated around
  - Type: `boolean`
  - Constraints: none
- **Speed Multiplier**: the speed of the transformation change
  - Type: `boolean`
  - Constraints: none
- **Type**: the type of transformation.
  - Type: `boolean`
  - Constraints: `MOVE` or `ROTATE` or `SCALE`
- **Type**: the type of speed
  - Type: `boolean`
  - Constraints: `LINEAR` or `EXPONENT` or `INSTANT`