# Physics

## 1. Collision

<img src="../image/collision.png" width="50%"/>

## 1.1 AABB vs AABB

- FabiEngine3D supports collision (only detection) between 2 AABBs.
- Collision response can be scripted.

## 1.2 Camera vs AABB

- FabiEngine3D supports collision (detection + response) between the camera and multiple AABBs.
- The camera has its own custom bounding box.

## 1.3 Camera vs Terrain

- FabiEngine3D supports collision (detection + response) between the camera and the terrain.
- The camera has a custom minimum distance to the camera.

## 2. Raycasting

<img src="../image/raycasting.png" width="75%"/>

## 2.1 Cursor Ray

- The cursor ray is a normalized ray from the cursor to 3D space.
- The position of the ray is simply the camera position.
- The direction of the ray is simply to where the cursor is pointing at.
- Every engine update the cursor ray is calculated.

## 2.1 Terrain Intersection

- FabiEngine3D supports cursor intersection with the terrain.
- Used in the mouse picking system of the world editor.
- Can be used for determining the distance from the camera to the terrain.
- Terrain pointing can be configured for performance.

## 2.2 AABB Intersection

- FabiEngine3D supports cursor intersection with AABBs.
- Used in the AABB selection system of the world editor.
- Can be used to check if the camera is looking at a certain AABB.
- Can be used for determining the distance from the camera to a certain AABB.
- If terrain intersection is enabled, the terrain can block AABB intersection.
