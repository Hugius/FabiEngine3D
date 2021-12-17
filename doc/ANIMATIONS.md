# Animations

## 1. General

- There are 2 types of animations: animation2D & animation3D.
- Animation2D = texture animation for billboards/images
- Animation3D = mesh animation for models

## 2. Animation2D Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
- **Row Count**: the amount of rows in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
- **Column Count**: the amount of columns in the animated texture
  - Type: `integer`
  - Constraints: at least `0`
- **Framestep**: the amount of engine updates between frame cycles
  - Type: `integer`
  - Constraints: between `64` and `512`
- **Column Index**: the amount of allocated audio channels for 3D sounds
  - Type: `integer`
  - Constraints: between `64` and `512`

## 3. Animation3D Properties

- **ID**: the identifier of the sound
  - Type: `string`
  - Constraints: must be unique, cannot be changed
