# Animation2D

## 1. General

- Animation2D is used for creating 2D texture animations.
- These animations can be applied to Quad2D/Quad3D entities.
- Animated textures consist of multiple small animation frames, divided in rows and columns.

## 2. Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Row Count**: the amount of rows in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
- **Column Count**: the amount of columns in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
- **Row Index**: the row index of the current animated texture frame
  - Type: `integer`
  - Constraints: at least `0`
- **Column Index**: the column index of the current animated texture frame
  - Type: `integer`
  - Constraints: at least `0`
- **Play Count**: the amount of (remaining) times the animation must play
  - Type: `integer`
  - Constraints: `-1` or at least `0`
- **Framestep**: the amount of engine updates between frame cycles
  - Type: `integer`
  - Constraints: at least `0`
- **Paused**: the animation is paused
  - Type: `boolean`
  - Constraints: none
- **Autopaused**: the animation is automatically paused after the current frame
  - Type: `boolean`
  - Constraints: none
