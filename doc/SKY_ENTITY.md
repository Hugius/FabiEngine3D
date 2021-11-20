# Sky Entity

## 1. General

- The sky entity is a 3D cube in 3D space.
- This cube, which called a skybox, is rendered around the camera.
- A skybox has a static position and has an infinite size, which creates the illusion of a real sky.

## 2. Resources

- Cube Map

## 3. Properties

- **Rotation Speed**: the speed of rotation around the Y axis.
  - Type: `decimal`
  - Constraints: none
- **Lightness**: the brightness of the sky fragments.
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Color**: the RGB color that will be mixed with the sky fragments.
  - Type: `vector3`
  - Constraints: between `0.0` and `1.0`
