# Graphics

## 1. Lighting

### 1.1 Ambient Lighting

- Ambient lighting is a form of global illumination.
- The lighting is not casted from a light source.
- Real world light scattering is mimicked.

### 1.2 Directional Lighting

- Directional lighting is light that comes from a directional light source.
- The light is only casted from a certain direction.
- Normal vectors are used to render this type of lighting.

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

- Cube reflections are reflections based on pre-captured cube maps.
- The reflections are static, but very efficient.
- Normal vectors are used to render this type of reflection.

### 1.7 Planar Reflections

- Planar reflections are real-time reflections rendered on flat surfaces.
- The reflections are performance-heavy, but very realistic.
- Projective texturing is used to render this type of reflection.

### 1.9 Shadows

- Shadows are casted from a directional shadow source.
- Shadow mapping is used to render this type of lighting.

## 2. Post Processing

### 2.1 Motion Blur

- Motion blur is an effect that blurs the screen in the camera view move direction.
- Blurring is either horizontal or vertical.

### 2.2 Depth Of Field

- Depth Of Field is an effect that blurs all pixels that are not in focus by the camera.
- The effect is either dynamic or static.

### 2.4 Lens Flare

- Lens flare is an effect that mimics camera lens flares.
- Flare maps are used to render this type of effect.

### 2.5 Sky Exposure

- Sky exposure is an effect that makes the sky very bright when not looking at it.

### 2.6 Bloom

- Bloom is an effect that adds realism to the rendering of very bright objects.
- Emission maps can be used to render this type of effect.
- Bloomed fragments are not affected by shadows or lighting.

## 3. Miscellaneous

### 3.1 Gamma Correction

- Gamma correction is the reverse process of monitors displaying colors in a non-linear space.
- Lighting calculations are done in linear space.
- After gamma correction the lighting looks smoother.

### 3.2 Normal Mapping

- Normal mapping is the process of increasing the lighting details by distorting normal vectors.
- A normal map is used to calculate distorted normal vectors.
- Flat surfaces look detailed with normal mapping

### 3.3 Fog Rendering

- Fog rendering is a graphical effect that mimics real world fog.

### 3.4 Water Graphics

- Specular lighting
- DUDV mapping
- Displacement mapping
- Normal mapping
- Planar reflections
- Planar refractions
- Fresnel effect
- Transparent edges
