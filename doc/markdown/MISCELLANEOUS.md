# Miscellaneous

## 1. Rotation system

<img src="../image/rotation_system.png" width="40%"/>

- X rotations go around the X axis.
- Y rotations go around the Y axis.
- Z rotations go around the Z axis.
- All rotational values are in degrees, not radians.
- Rotational degrees are automatically converted between 0&deg; and 360&deg; (example: 500&deg; = 140&deg;, -500&deg; = 220&deg;).
- **WARNING**: Rotating objects in every direction (XYZ) at the same time can cause the infamous gimbal lock!

## 2. Tips & tricks

- You can create your own custom subfolders within the subfolders of `~\projects\<your_project>\assets\`.
- The top viewport has a button called `UNCACHE` which deletes the chosen asset from the cache (if it was cached).
- The top viewport has a button called `DOCS` that redirects you instantly to the documentation.
- You can cancel any form by pressing `ESC`.
- You can enter a value form by pressing `ENTER`.

## 3. Miscellaneous

- All quad2Ds/text2Ds are rendered on top of each other.
- Centering the cursor might take 1 frame (or more) in time, because it might not be centered instantly by Microsoft Windows.
- The engine processes all logic at a fixed speed (75 updates per second), even if the FPS is higher/lower (minimum of 10 FPS).
- Transparency in 2D space is based on the order of placed quad2Ds/text2Ds.
- Transparency in 3D space is very complex and can sometimes be incorrect.
- Graphical effects that are set to low quality can flicker.
- Internal engine updates happen after the scripting updates.
- The messages of the logging console work like a FIFO (First In First Out) system.
- The maximum amount of messages in the logging console is 100.
- If a message is too long for the logging console, the full message can be found in the external console window.
- There are two types of cursors: ARROW & HAND.
