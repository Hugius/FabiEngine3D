# Performance

## 1. Statistics

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- In the statistics, the amount of entities is the total existing entity amount.
- In the statistics, the amount of triangles is the realtime triangle amount being rendered every frame.
- `coreUpdate` includes all function calls and calculations in your update scripts.
- `physicsUpdate` contains: camera, raycasting, collision.
- `bufferSwap` means the actual buffering on the output screen.

## 3. Dangers

- Rendering planar reflections
- Rendering water reflections
- Rendering water refractions
- Rendering water waves
- Rendering water edges
- Rendering pointlight entities
- Rendering spotlight entities
- Rendering complex meshes
- Rendering high quality shadows
- Capturing captor entities
- Loading high resolution textures
- Loading complex meshes

## 4. Tips

- Make use of LOD model entities to improve the performance on high-poly meshes.
- Lower the graphics/lighting quality to improve performance if necessary.
- Clear the messages in the logging console if a lot of messages are printed.
- Make sure your GPU is giving the maximum computing power to the engine, so check your graphics card settings.
- Capturing a captor entity can take some time (especially when loading a world).
- Use the face culling optimization in model entities as much as possible.
