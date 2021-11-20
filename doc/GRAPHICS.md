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
-

## 2. Post Processing

### 2.1 Motion Blur

### 2.2 Depth Of Field

### 2.4 Lens Flare

### 2.5 Sky Exposure

### 2.6 Bloom

## 3. Miscellaneous

### 3.1 Gamma Correction

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
