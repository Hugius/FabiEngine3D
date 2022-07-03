# Performance

## 1. Statistics

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- The amount of triangles is the realtime amount being rendered every frame.
- `mainUpdate`: input handling + the execution of your update scripts
- `physicsUpdate`: camera + raycasting + collision
- `environmentUpdate`: sky + terrain + water
- `modelUpdate`: model
- `quadUpdate`: quad3D + quad2D
- `textUpdate`: text3D + text2D
- `aabbUpdate`: AABB
- `lightUpdate`: pointlight + spotlight
- `captorUpdate`: captor
- `renderUpdate`: window + sky exposure + shadows + motion blur + lens flare
- `animationUpdate`: animation3D + animation2D
- `soundUpdate`: sound3D + sound2D
- `networkUpdate`: server + client

## 3. Dangers

- Rendering planar reflections
- Rendering planar refractions
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

- Make use of level of detailed models to improve the performance on high-poly meshes.
- Lower the graphics/lighting quality to improve performance if necessary.
- Clear the messages in the logging console if a lot of messages are printed.
- Make sure your GPU is giving the maximum computing power to the engine, so check your graphics card settings.
- Capturing a captor can take some time (especially when loading a world).
- Use the face culling optimization in models as much as possible.
