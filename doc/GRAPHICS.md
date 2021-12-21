# Graphics

## 1. Lighting

### 1.1 Ambient Lighting

#### 1.1.1 General

- Ambient lighting is a form of global illumination.
- The lighting is not casted from a light source.
- Real world light scattering is mimicked.

#### 1.1.2 Properties

- **Color**: the color of the light emitted by the ambient lighting
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Intensity**: the intensity of the light emitted by the ambient lighting
  - Type: `decimal`
  - Constraints: at least `0.0`
- **Enabled**: ambient lighting is enabled
  - Type: `boolean`
  - Constraints: none

### 1.2 Directional Lighting

#### 1.2.1 General

- Directional lighting is light that comes from a directional light source.
- The light is only casted from a certain direction.
- Normal vectors are used to render this type of lighting.

#### 1.2.2 Properties

- **Position**: the position of the directional lighting source
  - Type: `decimal3`
  - Constraints: none
- **Color**: the color of the light emitted by the directional lighting
  - Type: `decimal3`
  - Constraints: between `0.0` to `1.0`
- **Intensity**: the intensity of the light emitted by the directional lighting
  - Type: `decimal`
  - Constraints: at least `0`
- **Enabled**: directional lighting is enabled
  - Type: `boolean`
  - Constraints: none

### 1.3 Specular Lighting

- Specular lighting is light that is reflected from another light source.
- Normal vectors are used to render this type of lighting.

### 1.4 Point Lighting

- Point lighting is light that comes from a positional light source.
- The light is casted in every direction by the light source.
- Normal vectors are used to render this type of lighting.

### 1.5 Spot Lighting

- Spot lighting is light that comes from a rotational light source.
- The light creates a spotlight effect.
- Normal vectors are used to render this type of lighting.

### 1.6 Cube Reflections

#### 1.6.1 General

- Cube reflections are reflections based on pre-captured cube maps.
- The reflections are static, but very efficient.
- Normal vectors are used to render this type of reflection.

#### 1.6.2 Properties

- **Quality**: the quality of cube reflections
  - Type: `integer`
  - Constraints: between `128` and `1024`

### 1.7 Planar Reflections

#### 1.7.1 General

- Planar reflections are real-time reflections rendered on flat surfaces.
- The reflections are performance-heavy, but very realistic.
- Projective texturing is used to render this type of reflection.

#### 1.7.2 Properties

- **Height**: the Y coordinate from which planar reflections are captured
  - Type: `decimal`
  - Constraints: none
- **Quality**: the quality of planar refractions
  - Type: `integer`
  - Constraints: between `128` and `1024`

### 1.8 Planar Refractions

#### 1.8.1 General

- Planar refractions are real-time refractions rendered on flat surfaces.
- The refractions are performance-heavy, but very realistic.
- Projective texturing is used to render this type of refraction.

#### 1.8.2 Properties

- **Quality**: the quality of planar refractions
  - Type: `integer`
  - Constraints: between `128` and `1024`

### 1.9 Shadows

#### 1.9.1 General

- Shadows are casted from a directional shadow source.
- Shadow mapping is used to render this type of lighting.

#### 1.9.2 Properties

- **Eye**: the position of the shadow source
  - Type: `decimal3`
  - Constraints: none
- **Center**: the position to where the shadow source is looking at
  - Type: `decimal3`
  - Constraints: none
- **Size**: the size of the shadowed area
  - Type: `decimal`
  - Constraints: at least `0`
- **Lightness**: the lightness of the shadows
  - Type: `decimal`
  - Constraints: at least `0`
- **Quality**: the quality of the shadow map
  - Type: `integer`
  - Constraints: between `2048` and `16384`
- **Interval**: the amount of engine updates between camera follow updates
  - Type: `integer`
  - Constraints: at least `0`
- **Enabled**: shadows are enabled
  - Type: `boolean`
  - Constraints: none
- **Following Camera**: shadows are following the camera position
  - Type: `boolean`
  - Constraints: none

## 2. Post Processing

### 2.1 Motion Blur

#### 2.1.1 General

- Motion blur is an effect that blurs the screen in the camera view move direction.
- Blurring is either horizontal or vertical.

#### 2.1.2 Properties

- **Strength**: the strength of the motion blur movement
  - Type: `decimal`
  - Constraints: at least `0`
- **Quality**: the quality of the motion blur effect
  - Type: `integer`
  - Constraints: between `1` and `5`
- **Enabled**: the motion blur effect is enabled
  - Type: `boolean`
  - Constraints: none

### 2.2 DOF

#### 2.2.1 General

- DOF is an effect that blurs all pixels that are not in focus by the camera.
- The effect is either dynamic or static.

#### 2.2.2 Properties

- **Dynamic Distance**: the minimum distance where dynamic DOF starts
  - Type: `decimal`
  - Constraints: at least `0`
- **Blur Distance**: the minimum distance where the blurring starts
  - Type: `decimal`
  - Constraints: at least `0`
- **Quality**: the quality of the DOF effect
  - Type: `integer`
  - Constraints: between `1` and `5`
- **Enabled**: the DOF effect is enabled
  - Type: `boolean`
  - Constraints: none
- **Dynamic**: dynamic DOF (based on the distance between the camera and objects) is enabled
  - Type: `boolean`
  - Constraints: none

### 2.4 Lens Flare

#### 2.4.1 General

- Lens flare is an effect that mimics camera lens flares.
- Flare maps are used to render this type of effect.

#### 2.4.2 Assets

- Flare map

#### 2.4.3 Properties

- **Flare Map Path**: the path of the flare map file
  - Type: `string`
  - Constraints: none
- **Intensity**: the intensity of the lens flare effect
  - Type: `decimal`
  - Constraints: at least `0`
- **Sensitivity**: the sensitivity of the lens flare effect
  - Type: `decimal`
  - Constraints: at least `0`
- **Enabled**: the lens flare effect is enabled
  - Type: `boolean`
  - Constraints: none

### 2.5 Bloom

#### 2.5.1 General

- Bloom is an effect that adds a glow to very bright objects.
- Emission maps can be used to specify bloomed fragments.

#### 2.5.2 Properties

- **Intensity**: the intensity of the bloom effect
  - Type: `decimal`
  - Constraints: at least `0`
- **Quality**: the quality of the bloom effect
  - Type: `integer`
  - Constraints: between `1` and `5`
- **Blurs**: the amount of blurs used for the bloom effect
  - Type: `integer`
  - Constraints: at least `1`
- **Enabled**: the bloom effect is enabled
  - Type: `boolean`
  - Constraints: none
- **Type**: the type of the bloom effect
  - Type: `enumeration`
  - Constraints: `PARTS` or `EVERYTHING`

### 2.6 Anti Aliasing

#### 2.6.1 General

- Anti aliasing is an effect that smoothes out jagged edges.
- FXAA is the technique used for this effect.

#### 2.6.2 Properties

- **Enabled**: the anti aliasing effect is enabled
  - Type: `boolean`
  - Constraints: none

## 3. Miscellaneous

### 3.1 Fog

#### 3.1.1 General

- Fog is a graphical effect that mimics real world fog.

#### 3.1.2 Properties

- **Min Distance**: the minimum distance where the fog starts
  - Type: `decimal`
  - Constraints: at least `0`
- **Max Distance**: the minimum distance where the fog ends
  - Type: `decimal`
  - Constraints: at least `0`
- **Thickness**: the thickness percentage of the fog
  - Type: `decimal`
  - Constraints: between `0.0` and `1.0`
- **Color**: the color of the fog
  - Type: `decimal3`
  - Constraints: between `0.0` and `1.0`
- **Enabled**: fog is enabled
  - Type: `boolean`
  - Constraints: none

### 3.2 Sky Exposure

#### 3.2.1 General

- Sky exposure is an effect that makes the sky very bright when not looking at it.

#### 3.2.2 Properties

- **Intensity**: the intensity of the sky exposure effect
  - Type: `decimal`
  - Constraints: at least `0`
- **Speed**: the speed with which the sky exposure changes
  - Type: `decimal`
  - Constraints: at least `0`
- **Enabled**: the sky exposure effect is enabled
  - Type: `boolean`
  - Constraints: none

### 3.3 Anisotropic Filtering

#### 3.3.1 General

- Anisotropic filtering is the process of keeping the texture quality.
- Without this effect textures are blurry when viewed from oblique camera angles.
- Anisotropic filtering is always enabled.

#### 3.3.2 Properties

- **Quality**: the amount of samples used in anisotropic filtering
  - Type: `integer`
  - Constraints: between `1` and `16`

### 3.4 Gamma Correction

- Gamma correction is the reverse process of monitors displaying colors in a non-linear space.
- Lighting calculations are done in linear space.
- After gamma correction the lighting looks smoother.
- Gamma correction is always enabled.

### 3.5 Normal Mapping

- Normal mapping is the process of increasing the lighting details by distorting normal vectors.
- A normal map is used to calculate distorted normal vectors.
- Flat surfaces look detailed with normal mapping.

### 3.6 Transparent Water Edges

- The transparent water edges effect makes fragments transparent that are undeep.

### 3.7 Water Fresnel Effect

- The water fresnel effect mixes the reflection and refraction colors automatically based on the camera position.
- The water fresnel effect is always enabled.
