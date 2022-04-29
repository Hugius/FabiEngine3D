# Performance

## 1. Statistics

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- The amount of triangles is the realtime amount being rendered every frame.
- `mainUpdate` includes all function calls and calculations in your update scripts.
- `physicsUpdate` contains: camera, raycasting, collision.
- `bufferSwap` means the actual buffering on the output screen.

## 3. Dangers

- Rendering planar reflections
- Rendering water reflections
- Rendering water refractions
- Rendering water waves
- Rendering water edges
- Rendering pointlights
- Rendering spotlights
- Rendering complex meshes
- Rendering high quality shadows
- Capturing captors
- Loading high resolution textures
- Loading complex meshes

## 4. Tips

- Make use of LOD models to improve the performance on high-poly meshes.
- Lower the graphics/lighting quality to improve performance if necessary.
- Clear the messages in the logging console if a lot of messages are printed.
- Make sure your GPU is giving the maximum computing power to the engine, so check your graphics card settings.
- Capturing a captor can take some time (especially when loading a world).
- Use the face culling optimization in models as much as possible.
