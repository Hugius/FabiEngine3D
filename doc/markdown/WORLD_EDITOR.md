# World Editor

## 1. General

- All worlds will be saved in `~\projects\<your_project>\worlds\editor\`.
- Every thing that you place is based on the version in their own editor.
- Only the changes in the placed things made in the world editor are saved.
- Placed things can be selected if it has 1 or more bound AABBs.
- Each world has its own ID counter, which starts from 0.
- Every thing that you place will increase the ID counter by 1, so that all placed things are unique.

## 2. Controls

- Move camera with your mouse
- Press `LMB` to place
- Press `RMB` to toggle camera
- Press `MMB` to cancel placement
- Press `B` to toggle AABB rendering
- Press `F` to toggle wireframe rendering
- Press `R` to toggle debug rendering
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
- The water height can be moved upwards and downwards

## 6. Models

- You can place/edit/delete models in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation3D to a placed model.

## 7. Quad3D

- You can place/edit/delete quad3Ds in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.
- You can attach an (endless) animation2D to a placed quad3D.

## 8. Sounds

- You can place/edit/delete sounds in the world.
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

## 11. Captors

- You can place/edit/delete captors in the world.
- If a terrain is selected, you can place the captor on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the captor.

## 12. Settings

### 12.1 Lighting

- You can configure ambient lighting in the world.
- You can configure directional lighting in the world.

### 12.2 Graphics

- You can configure shadows in the world.
- You can configure reflections in the world.
- You can configure refractions in the world.
- You can configure DOF in the world.
- You can configure fog in the world.
- You can configure lens flare in the world.
- You can configure sky exposure in the world.
- You can configure bloom in the world.

### 12.3 Properties

- **Editor Speed**: the speed with which the camera moves and the XYZ fields change
  - Type: `decimal`
  - Constraints: at least `0.0`
