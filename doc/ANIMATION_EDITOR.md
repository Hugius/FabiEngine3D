# Animation Editor

## 1. General

- All animations will be saved in `~\projects\<your_project>\data\animation.fe3d`.
- You can create/edit/delete animations for models.
- Every created animation can be applied to models through scripting.
- You can select a preview model for the animation playback.

## 2. Controls

- Move camera with your mouse
- Press `RMB` to toggle camera
- Scroll `MMB` to zoom camera
- Press `H` to toggle debug rendering
- Press `R` to toggle reference box
- Press `F` to toggle wireframe
- Press `ESC` to go back
- Press `SPACE` to move upwards
- Press `SHIFT` to move downwards

## 3. Keyframes

- Each animation consists of 1 or more keyframes.
- You can create/edit/delete keyframes.
- The first keyframe is always the default model transformation.
- The last keyframe should be the same as the first keyframe.
- If the model is multiparted, each part can be animated independently.

## 4. Properties

### 4.1 `decimal3`

- **Transformation**: the target transformation
  - Constraints: none
- **Speed**: the speed of the transformation change
  - Constraints: none
- **Rotation origin**: the local origin which the model is rotated around
  - Constraints: none

### 4.2 `enumeration`

- **Type**: the type of transformation.
  - Constraints: `MOVE` or `ROTATE` or `SCALE`
- **Type**: the type of speed
  - Constraints: `LINEAR` or `EXPONENT` or `INSTANT`
