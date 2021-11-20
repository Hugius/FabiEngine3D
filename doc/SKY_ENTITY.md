# Sky Entity

## 1. General

- The sky entity is a 3D cube in 3D space.
- This cube, which called a skybox, is rendered around the camera.
- A skybox has a static position and has an infinite size, which creates the illusion of a real sky.

## 2. Resources

- Cube Map

## 3. Properties

### 3.1 String

### 3.2 Vector3

- **Color**: the RGB color that will be mixed with the sky fragments.
  - Type: `vector3`
  - Constraints: between `0.0` and `1.0`

### 3.3 Vector2

### 3.4 Decimal

- **Rotation**: the rotation of the mesh around the Y axis.
  - Type: `decimal`
  - Constraints: between `0.0` and `360.0`
- **Lightness**: the brightness of the sky fragments.
  - Type: `decimal`
  - Constraints: at least `0.0`

### 3.5 Integer

### 3.6 Boolean

### 3.7 Enumeration
