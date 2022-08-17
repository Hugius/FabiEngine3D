# Physics

## 1. Collision

<img src="../image/collision.png" width="50%"/>

## 1.1 AABB vs AABB

- The engine supports collision (detection only) between 2 AABBs.

## 1.2 Camera vs AABB

- The engine supports collision (detection + response) between the camera and AABBs.
- The camera has its own custom bounding box.

## 1.3 Camera vs Terrain

- The engine supports collision (detection + response) between the camera and the terrain.
- The camera has its own custom bounding box.
- The collision response takes place with a custom speed.

## 2. Raycasting

<img src="../image/raycasting.png" width="75%"/>

## 2.1 Cursor Ray

- The cursor ray is a normalized ray from the cursor into 3D space.
- The position of the ray is simply the camera position.
- The direction of the ray is simply to where the cursor is pointing at.

## 2.1 Terrain Intersection

- The engine supports cursor intersection with the terrain.
- Used in the mouse picking system of the world editor.
- Can be used for determining the distance from the camera to the terrain.

## 2.2 AABB Intersection

- The engine supports cursor intersection with AABBs.
- Used in the AABB selection system of the world editor.
- Can be used to check if the camera is looking at a certain AABB.
- Can be used for determining the distance from the camera to a certain AABB.
- Terrain intersection can block AABB intersections.
