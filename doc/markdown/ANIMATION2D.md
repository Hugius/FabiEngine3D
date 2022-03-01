# Animation2D

## 1. General

- Animation2D is used for creating 2D texture animations.
- These animations can be applied to quad2D/quad3D entities.
- Animated textures should consist of multiple smaller animation frames, divided by rows and columns.

## 2. Base Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Row Count**: the amount of rows in the animated texture
  - Type: `integer`
  - Constraints: at least `1`
- **Column Count**: the amount of columns in the animated texture
  - Type: `integer`
  - Constraints: at least `1`
- **Interval**: the amount of engine updates between animation frame cycles
  - Type: `integer`
  - Constraints: at least `0`

## 3. Started Properties

- **Play Count**: the amount of (remaining) times the animation must play
  - Type: `integer`
  - Constraints: at least `0` or `-1`
- **Row Index**: the row index of the current animated texture frame
  - Type: `integer`
  - Constraints: at least `0`
- **Column Index**: the column index of the current animated texture frame
  - Type: `integer`
  - Constraints: at least `0`
- **Interval Multiplier**: the multiplier of the animation interval to increase the animation speed
  - Type: `integer`
  - Constraints: at least `1`
- **Interval Divider**: the divider of the animation interval to decrease the animation speed
  - Type: `integer`
  - Constraints: at least `1`
- **Paused**: the animation is paused
  - Type: `boolean`
  - Constraints: none
- **Autopaused**: the animation is automatically paused after the current frame
  - Type: `boolean`
  - Constraints: none
