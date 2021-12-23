# Physics

## 1. Collision

<img src="../image/collision.png" width="50%"/>

## 1.1 AABB Entity vs AABB Entity

- FabiEngine3D supports collision (only detection) between 2 AABB entities.
- Collision response can be scripted.

## 1.2 Camera vs AABB entities

- FabiEngine3D supports collision (detection + response) between the camera and multiple AABB entities.
- The camera has its own custom bounding box.

## 1.3 Camera vs Terrain Entity

- FabiEngine3D supports collision (detection + response) between the camera and the terrain entity.
- The camera has a custom minimum distance to the camera.

## 2. Raycasting

<img src="../image/raycasting.png" width="75%"/>

## 2.1 Cursor Ray

- The cursor ray is a normalized ray from the cursor to 3D space.
- Every engine update the cursor ray is recalculated.
- The ray is the 3D direction of the cursor.

## 2.1 Terrain Entity Pointing

- FabiEngine3D supports 3D cursor picking on the terrain entity.
- Terrain entity pointing can be configured for performance.

## 2.2 AABB Entity Selection

- FabiEngine3D supports AABB entity selection with the cursor.
- Intersection between the cursor ray and AABB entities is calculated.
