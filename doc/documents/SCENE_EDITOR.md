# Scene Editor

## General

- All scenes will be saved in `~\projects\<your_project>\scenes\editor\`.
- Every entity that you place is based on the version in their editor, only the changes made in the scene editor are saved.
- Placed entities can be selected if it has 1 or more bound AABBs.

## Controls

- Press LMB to place entity
- Press RMB to toggle camera
- Press MMB to cancel entity placement
- Move camera with your mouse
- Press H to toggle debug rendering
- Press F to toggle wireframe
- Press B to toggle AABBs
- Use WASD to move around
- Press SPACE to move upwards
- Press SHIFT to move downwards
- Press ESC to go back

## Sky

- You can select/delete up to 1 water entity from the water editor.

## Terrain

- You can select/delete up to 1 water entity from the water editor.

## Water

- You can select/delete up to 1 water entity from the water editor.
- The water can be moved upwards and downwards

## Models

### General

- You can place/edit/delete models in the scene.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation to a placed model.
- You can "freeze" a placed model into local space, which means its position is not affected by camera movement.

### Properties

- **Position**: the position of the model in the scene.
  - **Range**: -inf to inf
- **Rotation**: the rotation of the model.
  - **Range**: 0 to 360
- **Size**: the size of the model.
  - **Range**: 0 to inf

## Billboards

### General

- You can place/edit/delete billboards in the scene.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.

### Properties

- **Position**: the position of the billboard in the scene.
  - **Range**: -inf to inf
- **Rotation**: the rotation of the billboard.
  - **Range**: 0 to 360
- **Size**: the size of the billboard.
  - **Range**: 0 to inf

## Sounds

### General

- You can place/edit/delete sounds in the scene.
- The sounds you place are in 3D space.
- If a terrain is selected, you can place the sound on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.

### Properties

- **Position**: the position of the sound in the scene.
  - **Range**: -inf to inf
- **Max Distance**: the maximum distance on which the sound is hearable.
  - **Range**: 0 to inf
- **Max Volume**: the volume of the sound when 100% hearable.
  - **Range**: 0 to inf

## Pointlights

### General

- You can place/edit/delete pointlights in the scene.
- If a terrain is selected, you can place the pointlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the pointlight.

### Properties

- **Position**: the position of the pointlight in the scene.
  - **Range**: -inf to inf
- **Radius**: the radius of the light emitted by the pointlight emission.
  - **Range**: 0 to 360
- **Color**: the color of the light emitted by the pointlight emission.
  - **Range**: 0 to 255
- **Intensity**: the intensity of the light emitted by the pointlight emission.
  - **Range**: 0 to 255
- **Shape**: the shape of the light emitted by the pointlight.
  - **Range**: 0 to 255

## Spotlights

### General

- You can place/edit/delete spotlights in the scene.
- If a terrain is selected, you can place the spotlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the spotlight.

### Properties

- **Position**: the position of the spotlight in the scene.
  - **Range**: -inf to inf
- **Color**: the color of the light emitted by the spotlight.
  - **Range**: 0 to 255
- **Yaw**: the yaw of the spotlight direction.
  - **Range**: 0 to 360
- **Pitch**: the pitch of the spotlight direction.
  - **Range**: 0 to 360
- **Intensity**: the size of the light emitted by the spotlight.
  - **Range**: 0 to inf
- **Angle**: the angle of the spotlight direction.
  - **Range**: 0 to 45
- **Distance**: the distance of the light emitted by the spotlight.
  - **Range**: 0 to inf

## Reflections

### General

- You can place/edit/delete reflections in the scene.
- Reflections capture their surroundings into a cube map.
- The resulting cube maps are used for cube reflections.
- If a terrain is selected, you can place the reflection on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the reflection.

### Properties

- **Position**: the position of the reflection in the scene.
  - **Range**: -inf to inf

## Settings

### Ambient Lighting

- **Color**: the color of the light emitted by the ambient lighting.
  - **Range**: 0 to 255
- **Intensity**: the intensity of the light emitted by the ambient lighting.
  - **Range**: 0 to inf

### Directional Lighting

- **Enabled**: enable or disable directional lighting in the scene.
  - **Range**: YES or NO
- **Position**: the position of the directional lighting source.
  - **Range**: -inf to inf
- **Color**: the color of the light emitted by the directional lighting.
  - **Range**: 0 to 255
- **Intensity**: the intensity of the light emitted by the directional lighting.
  - **Range**: 0 to inf
- **Billboard Size**: the size of the directional lighting source billboard.
  - **Range**: 0 to inf

### Shadows

- **Enabled**: enable or disable shadows in the scene.
  - **Range**: YES or NO
- **Position**: the position of the shadow source.
  - **Range**: -inf to inf
- **Center**: the point where the shadow source is looking at.
  - **Range**: -inf to inf
- **Size**: the size of the shadowed area.
  - **Range**: 0 to inf
- **Lightness**: the lightness of the shadows.
  - **Range**: 0 to inf
- **Follow Cam**: enable or disable shadows following the camera.
  - **Range**: ON or OFF
- **Interval**: the engine execution frame interval between camera follow updates.
  - **Range**: 0 to inf

### Motion blur

- You can enable **motion blur** with a custom **strength** (**Range**: 0 to inf).

### Depth Of Field

- You can enable dynamic **Depth Of Field** or enable a static **distant blur**.
- The distance to objects for dynamic DOF can be adjusted with the **DOF distance** (**Range**: 0 to inf) property.
- You can change he distance from which the blur starts with the **blur distance** (**Range**: 0 to inf) property.

### Fog

- You can enable **fog** based on a **minimum distance** (**Range**: 0 to inf) & **maximum distance** (**Range**: 0 to inf).
- Additionally you can set the **fog intensity** (**Range**: 0 to inf) & **fog color** (**Range**: 0 to 255).

### Lens Flare

- You can enable a **lens flare** for directional lighting based on a **flare map texture**.
- The brightness of the flare can be adjusted with the **intensity** (**Range**: 0 to inf) property.
- You can change how fast the flare fades with the **multiplier** (**Range**: 0 to inf) property).
- **Flare map**: colored 24bit `PNG` format image file from `game_assets\textures\flare_maps`.

### Sky Exposure

- You can enable **dynamic sky exposure** based on extra **intensity** (**Range**: 0 to inf) that is added to the sky lightness.

### Miscellaneous

- **Editor Speed**: defines the speed for camera movement and value changing.
  - **Range**: 0 to inf
- **LOD Distance**: minimum distance by which LOD models will appear/disappear.
  - **Range**: 0 to inf
- **Planar Height**: the Y coordinate from where planar reflections are captured.
  - **Range**: -inf to inf
