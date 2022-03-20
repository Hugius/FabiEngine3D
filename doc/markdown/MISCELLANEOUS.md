# Miscellaneous

## 1. Tips & tricks

- You can create your own custom subfolders within the subfolders of `~\projects\<your_project>\assets\`.
- Internal engine updates happen after the scripting updates.
- The top viewport has a button called `UNCACHE` which deletes the chosen asset from the cache (if it was cached).
- The top viewport has a button called `DOCS` that redirects you instantly to the FabiEngine3D documentation.
- You can clear the logging console in the bottom viewport by pressing `C` while hovering over the logging console.

## 2. Known issues

- There is a very rare bug when using the first person camera; if the cursor does not center anymore and the camera keeps spinning very fast, click on the window border once. This bug does not occur in fullscreen mode.

## 3. Miscellaneous

- All quad2D/text2D entities are rendered on top of each other.
- Centering the cursor might take 1 frame (or more) in time, because it might not be centered instantly by Microsoft Windows.
- The engine updates all logic at a fixed speed (144 updates per second), even if the FPS is higher/lower.
- The maximum amount of messages in the engine logging console is 1000.
- Transparency in 2D space is based on the order of placed entities.
- Transparency in 3D space is very complex and can sometimes be incorrect.
- Graphical effects that are set to low quality can flicker.
- All rotational values are in degrees, not radians.
