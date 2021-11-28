# Miscellaneous

## 1. Performance

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

## 2. Tips & tricks

- You can create your own custom subfolders within the subfolders of `~\projects\<your_project>\assets\`.
- Internal engine updates happen after the scripting updates.
- The top viewport has a button called `UNCACHE` which removes the chosen asset from the cache (if it was cached).
- The top viewport has a button called `DOCS` that redirects you instantly to the FabiEngine3D documentation.
- You can clear the logging console in the bottom viewport by pressing `C` while hovering over the logging console.

## 3. Known issues

- There is a very rare bug when using the first person camera; if the cursor does not center anymore and the camera keeps spinning very fast, click on the window border once. This bug does not occur in fullscreen mode.
- If FabiEngine3D crashes with the error `SDL_MIX could not be initialized: WASAPI can't find requested audio endpoint: Element not found.`, then you do not have an active audio device enabled or you have sound driver problems.

## 4. Miscellaneous

- Image entities and text entities are rendered in the order you placed them (last placed entity on top).
- Centering the cursor might take 1 frame (or more) in time, because it might not be centered instantly by Microsoft Windows.
- The engine updates all logic at a fixed speed (144 ticks per second), even if the rendering FPS is higher/lower.
- Emission maps are used for bloom if the specified bloom type is `PARTS`.
- Bloomed fragments are not affected by shadows or lighting.
