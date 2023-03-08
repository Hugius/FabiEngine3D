# Performance

## 1. Statistics

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- The amount of triangles is the realtime amount being rendered every frame.
- `mainUpdate`: input handling + execution of your update scripts
- `cameraUpdate`: camera transformation
- `environmentUpdate`: sky + terrain + water
- `modelUpdate`: models
- `quadUpdate`: quad3Ds + quad2Ds
- `textUpdate`: text3Ds + text2Ds
- `aabbUpdate`: AABBs
- `lightUpdate`: pointlights + spotlights
- `captorUpdate`: captors
- `renderUpdate`: window + sky exposure + shadows + motion blur + lens flare
- `animationUpdate`: animation3Ds + animation2Ds
- `soundUpdate`: sound3Ds + sound2Ds
- `networkUpdate`: server + client

## 2. Dangers

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

## 3. Tips

- Make use of level of detailed models to improve the performance on high-poly meshes.
- Lower the graphics quality to improve performance if necessary.
- Make sure your GPU is giving the maximum computing power to the engine, so check your graphics card settings.
- Capturing a captor can take some time (especially when loading a world with multiple captors).
- Use the face culling optimization in models as much as possible.
