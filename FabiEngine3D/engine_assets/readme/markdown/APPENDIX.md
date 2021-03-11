# Appendix
### Term definitions
- **Model**: a complex 3D object in 3D space, constisting of a mesh.
- **Billboard**: a 2D quad in 3D space.
- **Collision**: intersection between 2 things (for example: between the camera and a model).
- **AABB**: Axis Aligned Bounding Box, a 3D box used for collision.
- **Raycasting**: the process of "shooting" a ray from the camera position towards where the camera is looking.
- **LOD model**: Level Of Detail model, a less-detailed version of a model.
- **Ambient lighting**: the overall lightness of a scene.
- **Directional lighting**: diffuse lighting based on a directional light source (for example: the sun).
- **Point lighting**: individual light casters that show light around them (for example: a torch).
- **Spot lighting**: a spot light casted from the camera position towards where the camera is looking (for example: a flashlight).
- **DOF**: Depth Of Field, a post-processing effect that blurs all non-focused pixels.
- **Motion blur**: pixels will be blurred in the first person camera direction of motion.
- **Lens flare**: a post-processing flare overlay will be shown when the camera is looking at the directional lighting position (for example: the sun).
- **Sky HDR**: an effect that effects the brightness of the sky based on the camera pitch angle.
### General information
- It is best practice to make sure the **center** of your **mesh file** is **XYZ(0,0,0)** and the mesh itself is **above** the center.
- The **3D coordinate system** works on decimals with **XYZ(0.0, 0.0, 0.0)** as **center** coordinate. They can go in **any** direction (positive & negative).
- The **2D coordinate system** works on decimals with **XY(0.0, 0.0)** as **center** coordinate. The range is between **-1.0 and 1.0** from left to right & bottom to top.
### Rotations
- Beware of the [Gimbal lock](https://en.wikipedia.org/wiki/Gimbal_lock) when rotating objects in all 3 (XYZ) directions!
- Rotations of **models** & **billboards** are **Y-based**. This means that X & Z rotations are **relative** to the Y rotation, which is very useful in a lot of gameplay situations.
- All rotational **degrees** cannot be higher than 360 or lower than -360 (for example 500 will be 140).
- X rotations go **towards** the direction of the X axis.
- Z rotations go **towards** the direction of the Z axis.
- Y rotations go **around** the direction of the Y axis.
- FabiEngine3D does **not** support a camera roll, because of the infamous Gimbal Lock.
- FabiEngine3D **does** come with first person camera support, but **not** third person.
### AABB system
- Bound **model AABBs** are adjusted to the transformation (position, rotation, size) of the model **automatically**. They will only rotate in **1 direction** (the direction with the greatest angle of rotation).
- Bound **billboard AABBs** are adjusted to the transformation (position, rotation, size) of the billboard **automatically**. They will rotate only in **1 direction** (the direction with the greatest angle of rotation).
- **"Rotated"** AABBs will be translated and/or scaled in **90 degrees** directions (0, 90, 180, 270, etc).
- You **can** individually access (bound) AABBs that are placed through **scripting**.
- You **cannot** individually access bound AABBs from a **scene**.
- If you want to access an AABB bound to a model, the ID is composed like this: **modelID + "@" + aabbName**.
### Tips & tricks
- You can create your own custom **subfolders** within the main folder of `user\assets`.
- Internal engine updates happen **after** the scripting updates.
- The top viewport has a button called "**uncache**" which forces the engine to load an asset again, even if it was cached.
- You can **clear** the console output by pressing **C** when hovering the **console window**.
### Known issues
- There is a VERY rare **bug** when using the first person camera system; if the cursor does not center anymore and the camera keeps spinning very fast, click on the **window border** once. This bug does not occur in fullscreen mode.
### Performance
![performance](../images/performance.png)
- You can use the performance statistics to analyze your **game's performance**.
- The amounts of entities are the **total** amounts.
- The amount of triangles is the **realtime** amount being rendered every frame.
- `coreUpdate` includes all function calls and calculations in your update scripts.
- `bufferSwap` means the actual buffering on the output screen.
- Use LOD models to improve your performance.
- Lower the graphics quality in the project settings to improve your performance.
