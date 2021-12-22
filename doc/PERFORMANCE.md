# Performance

## 1. Statistics

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- In the statistics, the amount of entities is the total existing entity amount.
- In the statistics, the amount of triangles is the realtime triangle amount being rendered every frame.
- `coreUpdate` includes all function calls and calculations in your update scripts.
- `physicsUpdate` contains: camera, raycasting, collision.
- `bufferSwap` means the actual buffering on the output screen.

## 2. Performance Killers

- **Planar reflections**: everything has to be rendered twice
- **Water reflections**: everything has to be rendered twice
- **Water refractions**: everything has to be rendered twice
- **Water waves**: the water entity plane mesh has much more vertices
- **Pointlight entities**: heavy lighting calculations
- **Spotlight entities**: heavy lighting calculations

## 3. Tips

- Make use of LOD model entities to improve the performance on high-poly meshes.
- Lower the graphics/lighting quality to improve performance if necessary.
- Clear the messages in the engine logging console if a lot of messages are printed.
- Make a text entity dynamic if you want to change its content a lot.
- Make sure your GPU is giving the maximum computing power to the engine, so check your graphics card settings.
- If you want fast scene loading times, use as little reflection entities as possible.
- Use the face culling optimization in model entities as much as possible.
- Make a model entity instanced if you want to render a high amounts.
