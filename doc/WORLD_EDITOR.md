# World Editor

## 1. General

- All worlds will be saved in `~\projects\<your_project>\worlds\editor\`.
- Every entity that you place is based on the version in their editor, only the changes made in the world editor are saved.
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

### 6.1 General

- You can place/edit/delete models in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation to a placed model.
- You can "freeze" a placed model into local space, which means its position is not affected by camera movement.

### 6.2 Properties

- **Position**: the position of the model in the world.
  - Constraints: `-inf` to `inf`
- **Rotation**: the rotation of the model.
  - Constraints: `0` to `360`
- **Size**: the size of the model.
  - Constraints: `0` to `inf`

## 7. Billboards

### 7.1 General

- You can place/edit/delete billboards in the world.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.

### 7.2 Properties

- **Position**: the position of the billboard in the world.
  - Constraints: `-inf` to `inf`
- **Rotation**: the rotation of the billboard.
  - Constraints: `0` to `360`
- **Size**: the size of the billboard.
  - Constraints: `0` to `inf`

## 8. Sounds

### 8.1 General

- You can place/edit/delete sounds in the world.
- The sounds you place are in 3D space.
- If a terrain is selected, you can place the sound on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.

### 8.2 Properties

- **Position**: the position of the sound in the world.
  - Constraints: `-inf` to `inf`
- **Max Distance**: the maximum distance on which the sound is hearable.
  - Constraints: `0` to `inf`
- **Max Volume**: the volume of the sound when 100% hearable.
  - Constraints: `0` to `inf`

## 9. Pointlights

### 9.1 General

- You can place/edit/delete pointlights in the world.
- If a terrain is selected, you can place the pointlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the pointlight.

### 9.2 Properties

- **Position**: the position of the pointlight in the world.
  - Constraints: `-inf` to `inf`
- **Radius**: the radius of the light emitted by the pointlight emission.
  - Constraints: `0` to `360`
- **Color**: the color of the light emitted by the pointlight emission.
  - Constraints: `0` to `255`
- **Intensity**: the intensity of the light emitted by the pointlight emission.
  - Constraints: `0` to `255`
- **Shape**: the shape of the light emitted by the pointlight.
  - Constraints: `0` to `255`

## 10. Spotlights

### 10.1 General

- You can place/edit/delete spotlights in the world.
- If a terrain is selected, you can place the spotlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the spotlight.

### 10.2 Properties

- **Position**: the position of the spotlight in the world.
  - Constraints: `-inf` to `inf`
- **Color**: the color of the light emitted by the spotlight.
  - Constraints: `0` to `255`
- **Yaw**: the yaw of the spotlight direction.
  - Constraints: `0` to `360`
- **Pitch**: the pitch of the spotlight direction.
  - Constraints: `0` to `360`
- **Intensity**: the size of the light emitted by the spotlight.
  - Constraints: `0` to `inf`
- **Angle**: the angle of the spotlight direction.
  - Constraints: `0` to `45`
- **Distance**: the distance of the light emitted by the spotlight.
  - Constraints: `0` to `inf`

## 11. Reflections

### 11.1 General

- You can place/edit/delete reflections in the world.
- Reflections capture their surroundings into a cube map.
- The resulting cube maps are used for cube reflections.
- If a terrain is selected, you can place the reflection on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the reflection.

### 11.2 Properties

- **Position**: the position of the reflection in the world.
  - Constraints: `-inf` to `inf`

## 12. Settings

### 12.1 Lighting

#### 12.1.1 Ambient Lighting

- **Enabled**: enable or disable ambient lighting in the world.
  - Constraints: `ON` or `OFF`
- **Color**: the color of the light emitted by the ambient lighting.
  - Constraints: `0` to `255`
- **Intensity**: the intensity of the light emitted by the ambient lighting.
  - Constraints: `0` to `inf`

#### 12.1.2 Directional Lighting

- **Enabled**: enable or disable directional lighting in the world.
  - Constraints: `ON` or `OFF`
- **Position**: the position of the directional lighting source.
  - Constraints: `-inf` to `inf`
- **Color**: the color of the light emitted by the directional lighting.
  - Constraints: `0` to `255`
- **Intensity**: the intensity of the light emitted by the directional lighting.
  - Constraints: `0` to `inf`
- **Billboard Size**: the size of the directional lighting source billboard.
  - Constraints: `0` to `inf`

### 12.2 Graphics

#### 12.2.1 Shadows

- **Enabled**: enable or disable shadows in the world.
  - Constraints: `ON` or `OFF`
- **Position**: the position of the shadow source.
  - Constraints: `-inf` to `inf`
- **Center**: the point where the shadow source is looking at.
  - Constraints: `-inf` to `inf`
- **Size**: the size of the shadowed area.
  - Constraints: `0` to `inf`
- **Lightness**: the lightness of the shadows.
  - Constraints: `0` to `inf`
- **Follow Cam**: enable or disable shadows following the camera.
  - Constraints: `ON` or `OFF`
- **Interval**: the engine execution frame interval between camera follow updates.
  - Constraints: `0` to `inf`

#### 12.2.2 Motion blur

- **Enabled**: enable or disable the motion blur effect.
  - Constraints: `ON` or `OFF`
- **Sensitivity**: the sensitivity of the motion blur movement.
  - Constraints: `0` to `inf`

#### 12.2.3 Depth Of Field

- **Enabled**: enable or disable the DOF effect.
  - Constraints: `ON` or `OFF`
- **Dynamic**: enable or disable dynamic DOF based on the distance between the camera and objects.
  - Constraints: `ON` or `OFF`
- **Dynamic Distance**: the minimum distance where dynamic DOF starts.
  - Constraints: `0` to `inf`
- **Blur Distance**: the minimum distance where the blurring starts.
  - Constraints: `0` to `inf`

#### 12.2.4 Fog

- **Enabled**: enable or disable fog in the world.
  - Constraints: `ON` or `OFF`
- **Min Distance**: the minimum distance where the fog starts.
  - Constraints: `0` to `inf`
- **Max Distance**: the minimum distance where the fog ends.
  - Constraints: `0` to `inf`
- **Thickness**: the thickness percentage of the fog.
  - Constraints: `0` to `100`
- **Color**: the color of the fog.
  - Constraints: `0` to `255`

#### 12.2.5 Lens Flare

- **Enabled**: enable or disable the lens flare effect.
  - Constraints: `ON` or `OFF`
- **Flare Map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\flare_maps`.
  - Constraints: none
- **Intensity**: the intensity of the lens flare effect.
  - Constraints: `0` to `inf`
- **Sensitivity**: the sensitivity of the lens flare effect.
  - Constraints: `0` to `inf`

#### 12.2.6 Sky Exposure

- **Enabled**: enable or disable the sky exposure effect.
  - Constraints: `ON` or `OFF`
- **Intensity**: the intensity of the sky exposure effect.
  - Constraints: `0` to `inf`
- **Speed**: the speed with which the sky exposure changes.
  - Constraints: `0` to `inf`

#### 12.2.7 Bloom

- **Enabled**: enable or disable the bloom effect.
  - Constraints: `ON` or `OFF`
- **Type**: the type of the bloom effect.
  - Constraints: `PARTS` or `EVERYTHING`
- **Intensity**: the intensity of the bloom effect.
  - Constraints: `0` to `inf`
- **Blurs**: the amount of blurs used for the bloom effect.
  - Constraints: `1` to `inf`

#### 12.3 Miscellaneous

- **Editor Speed**: the speed for camera movement and value changing.
  - Constraints: `0` to `inf`
- **LOD Distance**: the minimum distance by which LOD models will appear/disappear.
  - Constraints: `0` to `inf`
- **Planar Height**: the Y coordinate from where planar reflections are captured.
  - Constraints: `-inf` to `inf`
