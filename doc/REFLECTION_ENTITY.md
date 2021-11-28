# Reflection Entity

## 1. General

- The reflection entity is a 3D captor in 3D space.
- Everything around the entity is captured into a cube map.
- The cube map is used for cube reflections.

## 2. Resources

- Cube Map

## 3. Properties

### 3.1 `decimal3`

- **Position**: the XYZ position of the captor
  - Constraints: none
- **Position Target**: the target XYZ position of the captor
  - Constraints: none

### 3.2 `decimal`

- **Position Target Speed**: the speed with which the captor moves to the target position
  - Constraints: at least `0.0`
