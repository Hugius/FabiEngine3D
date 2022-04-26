# World Editor

## 1. General

- All worlds will be saved in `~\projects\<your_project>\worlds\editor\`.
- Every entity that you place is based on the version in their own editor.
- Only the changes in the entities made in the world editor are saved.
- Placed entities can be selected if it has 1 or more bound AABB entities.
- Each world has its own ID counter, which starts from 0.
- Every entity that you place will increase the ID counter by 1, so that all entities are unique.

## 2. Controls

- Move camera with your mouse
- Press `LMB` to place entity
- Press `RMB` to toggle camera
- Press `MMB` to cancel entity placement
- Press `B` to toggle AABB entity rendering
- Press `F` to toggle wireframe rendering
- Press `R` to toggle debug rendering
- Press `SPACE` to move upwards
- Press `SHIFT` to move downwards
- Use `WASD` to move around
- Press `ESC` to go back

## 3. Sky

- You can select/delete up to 1 sky entity from the sky editor.

## 4. Terrain

- You can select/delete up to 1 terrain entity from the terrain editor.

## 5. Water

- You can select/delete up to 1 water entity from the water editor.
- The water entity height can be moved upwards and downwards

## 6. Models

- You can place/edit/delete model entities in the world.
- If a terrain entity is selected, you can place the model entity on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the model entity.
- You can attach an (endless) animation to a placed model entity.

## 7. Quad3D

- You can place/edit/delete quad3D entities in the world.
- If a terrain entity is selected, you can place the model entity on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the sound.

## 8. Sounds

- You can place/edit/delete sounds in the world.
- If a terrain entity is selected, you can place the sound on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the model entity.

## 9. Pointlights

- You can place/edit/delete pointlight entities in the world.
- If a terrain entity is selected, you can place the pointlight entity on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the pointlight entity.

## 10. Spotlights

- You can place/edit/delete spotlight entities in the world.
- If a terrain entity is selected, you can place the spotlight entity on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the spotlight entity.

## 11. Captors

- You can place/edit/delete captor entities in the world.
- If a terrain entity is selected, you can place the captor entity on top of the terrain entity with your mouse.
- If no terrain entity is selected, you must specify the position of the captor entity.

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
