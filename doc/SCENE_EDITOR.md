# Scene Editor

## 1. General

- All scenes will be saved in `~\projects\<your_project>\scenes\editor\`.
- Every entity that you place is based on the version in their editor, only the changes made in the scene editor are saved.
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

- You can place/edit/delete models in the scene.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.
- You can attach an (endless) animation to a placed model.
- You can "freeze" a placed model into local space, which means its position is not affected by camera movement.

### 6.2 Properties

- **Position**: the position of the model in the scene.
  - **Range**: `-inf` to `inf`
- **Rotation**: the rotation of the model.
  - **Range**: `0` to `360`
- **Size**: the size of the model.
  - **Range**: `0` to `inf`

## 7. Billboards

### 7.1 General

- You can place/edit/delete billboards in the scene.
- If a terrain is selected, you can place the model on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the sound.

### 7.2 Properties

- **Position**: the position of the billboard in the scene.
  - **Range**: `-inf` to `inf`
- **Rotation**: the rotation of the billboard.
  - **Range**: `0` to `360`
- **Size**: the size of the billboard.
  - **Range**: `0` to `inf`

## 8. Sounds

### 8.1 General

- You can place/edit/delete sounds in the scene.
- The sounds you place are in 3D space.
- If a terrain is selected, you can place the sound on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the model.

### 8.2 Properties

- **Position**: the position of the sound in the scene.
  - **Range**: `-inf` to `inf`
- **Max Distance**: the maximum distance on which the sound is hearable.
  - **Range**: `0` to `inf`
- **Max Volume**: the volume of the sound when 100% hearable.
  - **Range**: `0` to `inf`

## 9. Pointlights

### 9.1 General

- You can place/edit/delete pointlights in the scene.
- If a terrain is selected, you can place the pointlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the pointlight.

### 9.2 Properties

- **Position**: the position of the pointlight in the scene.
  - **Range**: `-inf` to `inf`
- **Radius**: the radius of the light emitted by the pointlight emission.
  - **Range**: `0` to `360`
- **Color**: the color of the light emitted by the pointlight emission.
  - **Range**: `0` to `255`
- **Intensity**: the intensity of the light emitted by the pointlight emission.
  - **Range**: `0` to `255`
- **Shape**: the shape of the light emitted by the pointlight.
  - **Range**: `0` to `255`

## 10. Spotlights

### 10.1 General

- You can place/edit/delete spotlights in the scene.
- If a terrain is selected, you can place the spotlight on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the spotlight.

### 10.2 Properties

- **Position**: the position of the spotlight in the scene.
  - **Range**: `-inf` to `inf`
- **Color**: the color of the light emitted by the spotlight.
  - **Range**: `0` to `255`
- **Yaw**: the yaw of the spotlight direction.
  - **Range**: `0` to `360`
- **Pitch**: the pitch of the spotlight direction.
  - **Range**: `0` to `360`
- **Intensity**: the size of the light emitted by the spotlight.
  - **Range**: `0` to `inf`
- **Angle**: the angle of the spotlight direction.
  - **Range**: `0` to `45`
- **Distance**: the distance of the light emitted by the spotlight.
  - **Range**: `0` to `inf`

## 11. Reflections

### 11.1 General

- You can place/edit/delete reflections in the scene.
- Reflections capture their surroundings into a cube map.
- The resulting cube maps are used for cube reflections.
- If a terrain is selected, you can place the reflection on top of the terrain with your mouse.
- If no terrain is selected, you must specify the position of the reflection.

### 11.2 Properties

- **Position**: the position of the reflection in the scene.
  - **Range**: `-inf` to `inf`

## 12. Settings

### 12.1 Lighting

#### 12.1.1 Ambient Lighting

- **Enabled**: enable or disable ambient lighting in the scene.
  - **Range**: `ON` or `OFF`
- **Color**: the color of the light emitted by the ambient lighting.
  - **Range**: `0` to `255`
- **Intensity**: the intensity of the light emitted by the ambient lighting.
  - **Range**: `0` to `inf`

#### 12.1.2 Directional Lighting

- **Enabled**: enable or disable directional lighting in the scene.
  - **Range**: `ON` or `OFF`
- **Position**: the position of the directional lighting source.
  - **Range**: `-inf` to `inf`
- **Color**: the color of the light emitted by the directional lighting.
  - **Range**: `0` to `255`
- **Intensity**: the intensity of the light emitted by the directional lighting.
  - **Range**: `0` to `inf`
- **Billboard Size**: the size of the directional lighting source billboard.
  - **Range**: `0` to `inf`

### 12.2 Graphics

#### 12.2.1 Shadows

- **Enabled**: enable or disable shadows in the scene.
  - **Range**: `ON` or `OFF`
- **Position**: the position of the shadow source.
  - **Range**: `-inf` to `inf`
- **Center**: the point where the shadow source is looking at.
  - **Range**: `-inf` to `inf`
- **Size**: the size of the shadowed area.
  - **Range**: `0` to `inf`
- **Lightness**: the lightness of the shadows.
  - **Range**: `0` to `inf`
- **Follow Cam**: enable or disable shadows following the camera.
  - **Range**: `ON` or `OFF`
- **Interval**: the engine execution frame interval between camera follow updates.
  - **Range**: `0` to `inf`

#### 12.2.2 Motion blur

- **Enabled**: enable or disable the motion blur effect.
  - **Range**: `ON` or `OFF`
- **Sensitivity**: the sensitivity of the motion blur movement.
  - **Range**: `0` to `inf`

#### 12.2.3 Depth Of Field

- **Enabled**: enable or disable the DOF effect.
  - **Range**: `ON` or `OFF`
- **Dynamic**: enable or disable dynamic DOF based on the distance between the camera and objects.
  - **Range**: `ON` or `OFF`
- **Dynamic Distance**: the minimum distance where dynamic DOF starts.
  - **Range**: `0` to `inf`
- **Blur Distance**: the minimum distance where the blurring starts.
  - **Range**: `0` to `inf`

#### 12.2.4 Fog

- **Enabled**: enable or disable fog in the scene.
  - **Range**: `ON` or `OFF`
- **Min Distance**: the minimum distance where the fog starts.
  - **Range**: `0` to `inf`
- **Max Distance**: the minimum distance where the fog ends.
  - **Range**: `0` to `inf`
- **Thickness**: the thickness percentage of the fog.
  - **Range**: `0` to `100`
- **Color**: the color of the fog.
  - **Range**: `0` to `255`

#### 12.2.5 Lens Flare

- **Enabled**: enable or disable the lens flare effect.
  - **Range**: `ON` or `OFF`
- **Flare Map**: colored `24bit PNG` format image file from `~\projects\<your_project>\assets\textures\flare_maps`.
  - **Range**: `none`
- **Intensity**: the intensity of the lens flare effect.
  - **Range**: `0` to `inf`
- **Sensitivity**: the sensitivity of the lens flare effect.
  - **Range**: `0` to `inf`

#### 12.2.6 Sky Exposure

- **Enabled**: enable or disable the sky exposure effect.
  - **Range**: `ON` or `OFF`
- **Intensity**: the intensity of the sky exposure effect.
  - **Range**: `0` to `inf`
- **Speed**: the speed with which the sky exposure changes.
  - **Range**: `0` to `inf`

#### 12.2.7 Bloom

- **Enabled**: enable or disable the bloom effect.
  - **Range**: `ON` or `OFF`
- **Type**: the type of the bloom effect.
  - **Range**: `PARTS` or `EVERYTHING`
- **Intensity**: the intensity of the bloom effect.
  - **Range**: `0` to `inf`
- **Blurs**: the amount of blurs used for the bloom effect.
  - **Range**: `1` to `inf`

#### 12.3 Miscellaneous

- **Editor Speed**: the speed for camera movement and value changing.
  - **Range**: `0` to `inf`
- **LOD Distance**: the minimum distance by which LOD models will appear/disappear.
  - **Range**: `0` to `inf`
- **Planar Height**: the Y coordinate from where planar reflections are captured.
  - **Range**: `-inf` to `inf`
