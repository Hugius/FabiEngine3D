# World Editor

## 1. General

- All worlds will be saved in `~\projects\<your_project>\worlds\editor\`.
- Every entity that you place is based on the version in their own editor.
- Only the changes in the entities made in the world editor are saved.
- Placed entities can be selected if it has 1 or more bound AABBs.

## 2. Controls

- Move camera with your mouse
- Press `LMB` to place entity
- Press `RMB` to toggle camera
- Press `MMB` to cancel entity placement
- Press `H` to toggle debug rendering
- Press `F` to toggle wireframe
- Press `B` to toggle AABBs
- Use `WASD` to move around
- Press `SPACE` to move upwards
- Press `SHIFT` to move downwards
- Press `ESC` to go back

## 3. Sky

- You can select/delete up to 1 sky from the sky editor.

## 4. Terrain

- You can select/delete up to 1 terrain from the terrain editor.

## 5. Water

- You can select/delete up to 1 water from the water editor.
- The water can be moved upwards and downwards

## 6. Models

- You can place/edit/delete models in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation to a placed model.
- You can "freeze" a placed model into local space, which means its position is not affected by camera movement.

## 7. Billboards

- You can place/edit/delete billboards in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.

## 8. Sounds

- You can place/edit/delete sounds in the world.
- The sounds you place are in 3D space.
- If a terrain is selected, you can place the sound on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.

## 9. Pointlights

- You can place/edit/delete pointlights in the world.
- If a terrain is selected, you can place the pointlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the pointlight.

## 10. Spotlights

- You can place/edit/delete spotlights in the world.
- If a terrain is selected, you can place the spotlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the spotlight.

## 11. Reflections

- You can place/edit/delete reflections in the world.
- Reflections capture their surroundings into a cube map.
- The resulting cube maps are used for cube reflections.
- If a terrain is selected, you can place the reflection on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the reflection.

## 12. Settings

- **Editor Speed**: the speed for camera movement and value changing.
  - Constraints: `0` to `inf`
- **LOD Distance**: the minimum distance by which LOD models will appear/disappear.
  - Constraints: `0` to `inf`
- **Planar Height**: the Y coordinate from where planar reflections are captured.
  - Constraints: `-inf` to `inf`
- **Audio**: the amount of allocated audio channels
  - Type: `integer`
  - Constraints: between `64` and `512`
- **Billboard Size**: ??????????????
  - Constraints: `-inf` to `inf`