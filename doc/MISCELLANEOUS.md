# Miscellaneous

## 1. Coordinate system

- The X axis is horizontal (left & right).
- The Y axis is vertical (down & up).
- The Z axis is depth (back & front).
- The 3D coordinate system works on decimals with XYZ(0,0,0) as center coordinate. They can go in any direction (positive & negative).
- The 2D coordinate system works on decimals with XY(0,0) as center coordinate. The range is between -1.0 and 1.0 from left to right & bottom to top.
- The maximum render distance is fixed at 2500.0 (the reference box in the model editor has a size of 1.0).

## 2. Rotation system

- Beware of the [gimbal lock](https://en.wikipedia.org/wiki/Gimbal_lock) when rotating objects in all 3 (XYZ) directions!
- FabiEngine3D does not support a camera roll, because of the infamous gimbal lock.
- All rotational degrees are converted between 0&deg; and 360&deg; (example: 500&deg; = 140&deg;, -500&deg; = 220&deg;).
- X rotations go around the X axis.
- Y rotations go around the Y axis.
- Z rotations go around the Z axis.

## 3. AABB system



## 4. Performance

- You can use the performance statistics in the bottom viewport to analyze your application's performance.
- In the statistics, the amount of entities is the total existing entity amount.
- In the statistics, the amount of triangles is the realtime triangle amount being rendered every frame.
- `coreUpdate` includes all function calls and calculations in your update scripts.
- `physicsUpdate` contains: camera calculations, raycasting, collision.
- `bufferSwap` means the actual buffering on the output screen.
- Make use of LOD models to improve your performance on high-poly models.
- Lower the graphics quality in the project settings to improve your graphics performance.
- The water reflection/refraction effects have a huge impact on performance, because a lot of entities have to be rendered twice.
- The in-engine logging console can have impact on performance during in-engine application runtime, because of scripting error checks. The higher the amount of console messages, the bigger the performance impact. To resolve this, simply clear the console messages.

## 5. Tips & tricks

- You can create your own custom subfolders within the subfolders of `~\projects\<your_project>\assets\`.
- Internal engine updates happen after the scripting updates.
- The top viewport has a button called `UNCACHE` which removes the chosen asset from the cache (if it was cached).
- The top viewport has a button called `DOCS` that redirects you instantly to the FabiEngine3D documentation.
- You can clear the logging console in the bottom viewport by pressing `C` while hovering over the logging console.

## 6. Known issues

- There is a very rare bug when using the first person camera; if the cursor does not center anymore and the camera keeps spinning very fast, click on the window border once. This bug does not occur in fullscreen mode.
- If FabiEngine3D crashes with the error `SDL_MIX could not be initialized: WASAPI can't find requested audio endpoint: Element not found.`, then you do not have an active audio device enabled or you have sound driver problems.

## 7. Miscellaneous

- Image entities and text entities are rendered in the order you placed them (last placed entity on top).
- Centering the cursor might take 1 frame (or more) in time, because it might not be centered instantly by Microsoft Windows.
- The engine updates all logic at a fixed speed (144 ticks per second), even if the rendering FPS is higher/lower.
- Emission maps are used for bloom if the specified bloom type is `PARTS`.
- Bloomed fragments are not affected by shadows or lighting.
