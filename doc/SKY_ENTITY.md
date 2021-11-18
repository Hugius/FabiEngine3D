# Sky Entity

## 1. General

- The sky entity is a 3D cube in 3D space.
- This cube, which called a skybox, is rendered around the camera.
- A skybox has a static position and has an infinite size, which creates the illusion of a real sky.

## 2. Resources

- Cube Map

## 3. Properties

- **Rotation Speed**: the speed of rotation around the Y axis.
  - Constraints: `-inf` to `inf`
- **Lightness**: the brightness of the sky fragments.
  - Constraints: `0` to `inf`
- **Color**: the RGB color that will be mixed with the sky fragments.
  - Constraints: `0` to `255`
