# Sky

## 1.1 General

- The sky entity is simply a 3D cube, called a [skybox](https://en.wikipedia.org/wiki/Skybox_(video_games)), that is rendered around the camera.
- A skybox is static and has an infinite size, which creates the illusion of a real sky.

## 1.2 Assets

- Cube Map

## 1.3 Properties

- **Rotation Speed**: the speed of rotation around the Y axis.
  - Constraints: `-inf` to `inf`
- **Lightness**: the brightness of the sky fragments.
  - Constraints: `0` to `inf`
- **Color**: the RGB color that will be mixed with the sky fragments.
  - Constraints: `0` to `255`