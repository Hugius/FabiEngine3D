# World editor

## 1. General

- All worlds will be saved in `~\projects\<your_project>\worlds\editor\`.
- Every thing that you place is based on the version in their own editor.
- Only the changes in the placed things made in the world editor are saved.
- Placed things can be selected if it has 1 or more bound AABBs.
- Each world has its own ID counters for every placable thing (which starts from 0).
- Every thing that you place will increase the ID counter by 1, so that all placed things are unique.
- The structure of the IDs look like this: `"name_123"`.

## 2. Controls

- Move camera with your mouse
- Press `LMB` to place
- Press `RMB` to toggle camera
- Press `MMB` to cancel placement
- Press `G` to toggle editor grid
- Press `F` to toggle wireframe rendering
- Press `B` to toggle AABB rendering
- Press `SPACE` to move upwards
- Press `SHIFT` to move downwards
- Use `WASD` to move around
- Press `ESC` to go back

## 3. Sky

- You can select/delete up to 1 sky from the sky editor.

## 4. Terrain

- You can select/delete up to 1 terrain from the terrain editor.

## 5. Water

- You can select/delete up to 1 water from the water editor.
- The water height can be moved upwards and downwards.

## 6. Models

- You can place/edit/delete models in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation3D to a placed model.

## 7. Quad3Ds

- You can place/edit/delete quad3Ds in the world.
- If a terrain is selected, you can place the quad3D on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.
- You can attach an (endless) animation2D to a placed quad3D.

## 8. Text3Ds

- You can place/edit/delete text3Ds in the world.
- If a terrain is selected, you can place the text3D on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.
- You can attach an (endless) animation2D to a placed text3D.

## 9. AABBs

- You can place/edit/delete AABBs in the world.
- If a terrain is selected, you can place the AABB on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the AABB.

## 10. Pointlights

- You can place/edit/delete pointlights in the world.
- If a terrain is selected, you can place the pointlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the pointlight.

## 11. Spotlights

- You can place/edit/delete spotlights in the world.
- If a terrain is selected, you can place the spotlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the spotlight.

## 12. Captors

- You can place/edit/delete captors in the world.
- If a terrain is selected, you can place the captor on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the captor.

## 13. Sound3Ds

- You can place/edit/delete sound3Ds in the world.
- If a terrain is selected, you can place the sound on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound3D.

## 14. Settings

### 14.1 Graphics

- You can configure ambient lighting in the world.
- You can configure directional lighting in the world.
- You can configure shadows in the world.
- You can configure reflections in the world.
- You can configure refractions in the world.
- You can configure DOF in the world.
- You can configure fog in the world.
- You can configure lens flare in the world.
- You can configure sky exposure in the world.
- You can configure bloom in the world.

### 14.2 Properties

- **Editor Speed**: the speed with which the camera moves and the XYZ fields change
  - Type: `decimal`
  - Constraints: at least `0.0`
