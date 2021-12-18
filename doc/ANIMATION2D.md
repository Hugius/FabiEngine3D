# Animation2D

## 1. General

- Animation2D is used for creating 2D texture animations.
- These animations can be applied to billboard/image entities.

## 2. Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
  - Write Access: editor
  - Read Access: editor + script
- **Row Count**: the amount of rows in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
  - Write Access: editor
  - Read Access: editor + script
- **Row Index**: the row index of the current frame
  - Type: `integer`
  - Constraints: at least `0`
  - Write Access: script
  - Read Access: script
- **Column Count**: the amount of columns in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
  - Write Access: editor + script
  - Read Access: editor + script
- **Column Index**: the column index of the current frame
  - Type: `integer`
  - Constraints: between `64` and `512`
  - Write Access: editor
  - Read Access: editor + script
- **Framestep**: the amount of engine updates between frame cycles
  - Type: `integer`
  - Constraints: between `64` and `512`
  - Write Access: editor + script
  - Read Access: editor + script
- **Paused**: the animation is paused
  - Type: `boolean`
  - Constraints: none
  - Write Access: script
  - Read Access: script
