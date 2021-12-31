# Assets

## 1. Audio

- Audio assets must be placed in `~\projects\<your_project>\assets\audio\`.
- The file format is `.wav` because the absence of compression delivers high audio quality.
- Due to the uncompressed format, note that the file size can be very large.

## 3. Mesh

- Mesh assets must be placed in `~\projects\<your_project>\assets\mesh\`.
- The file format is `.obj` because it is simple and commonly used.
- Meshes are used to render complex 3D objects on the screen.
- Make sure that the mesh file contains: `v`, `vt`, `vn`, `f`.
- Make sure that the center of your mesh is XYZ(0,0,0).
- The mesh should be modeled so that the lowest vertex (Y coordinate) is positioned at the center.
- A mesh can consist of multiple parts.
- To make a mesh multiparted, you must specify at least 2 parts by writing `FE3D_PART <name>`.
- Example multiparted `.obj` file:

  ```text
  FE3D_PART part1
  v ...
  vt ...
  vn ...
  f ...
  FE3D_PART part2
  v ...
  vt ...
  vn ...
  f ...
  ```

## 4. Image

- Image assets must be placed in `~\projects\<your_project>\assets\image\`.
- The file format is `.png` because the absence of compression delivers high image quality.
- Due to the uncompressed format, note that the files can be very big.
- Images are used for a variety of reasons for rendering.

### 4.1 Blend Map

<img src="../image/blend_map.png" width="25%"/>

- Blend map assets must be placed in `~\projects\<your_project>\assets\image\blend_map\`.
- Bit depth: `24`
- Blend maps are used to render and mix multiple textures onto a terrain mesh.
- Each pixel (R,G,B) of the blend map corresponds to a different diffuse/normal map.
- In total you can use up to 10 different images:
  - 1x height map
  - 1x blend map
  - 1x base diffuse map
  - 1x base normal map
  - 3x blend diffuse map
  - 3x blend normal map

### 4.2 Cube Map

<img src="../image/skybox_left.png" width="25%"/>
<img src="../image/skybox_right.png" width="25%"/>
<img src="../image/skybox_bottom.png" width="25%"/>
<img src="../image/skybox_top.png" width="25%"/>
<img src="../image/skybox_back.png" width="25%"/>
<img src="../image/skybox_front.png" width="25%"/>

- Cube map assets must be placed in `~\projects\<your_project>\assets\image\cube_map\`
- Bit depth: `24`
- Cube maps are used to render a skybox around the camera.
- A cube map consists of 6 images: left, right, bottom, top, back, front.

### 4.3 Diffuse Map

<img src="../image/diffuse_map.png" width="25%"/>

- Diffuse map assets must be placed in `~\projects\<your_project>\assets\image\diffuse_map\`
- Bit depth: `24/32`
- Diffuse maps are used to render a variety of colors to a mesh.

### 4.4 Displacement Map

<img src="../image/displacement_map.png" width="25%"/>

- Displacement map assets must be placed in `~\projects\<your_project>\assets\image\displacement_map\`
- Bit depth: `8`
- DUDV maps are used to create waves in a water mesh.

### 4.5 DUDV Map

<img src="../image/dudv_map.png" width="25%"/>

- DUDV map assets must be placed in `~\projects\<your_project>\assets\image\dudv_map\`
- Bit depth: `24`
- Displacement maps are used to create ripples in a water texture.

### 4.6 Emission Map

<img src="../image/emission_map.png" width="25%"/>

- Emission map assets must be placed in `~\projects\<your_project>\assets\image\emission_map\`
- Bit depth: `24`
- Emission maps are used to make certain parts of a mesh appear brighter.

### 4.7 Flare Map

<img src="../image/flare_map.png" width="25%"/>

- Flare map assets must be placed in `~\projects\<your_project>\assets\image\flare_map\`
- Bit depth: `24`
- Flare maps are used in the [lens flare effect](GRAPHICS.md).
- The pixel colors in the flare map are added to the 3D rendering pixels in the post-processing pipeline

### 4.8 Font Map

<img src="../image/font_map.png" width="25%"/>

- Diffuse map assets must be placed in `~\projects\<your_project>\assets\image\font_map\`
- Bit depth: `32`
- Font maps are used to render text.

### 4.9 Height Map

<img src="../image/height_map.png" width="25%"/>

- Height map assets must be placed in `~\projects\<your_project>\assets\image\height_map\`.
- Bit depth: `8`
- Height maps are used to generate a terrain mesh.
- Each pixel of the height map corresponds to a vertex height.

### 4.10 Normal Map

<img src="../image/normal_map.png" width="25%"/>

- Normal map assets must be placed in `~\projects\<your_project>\assets\image\normal_map\`
- Bit depth: `24`
- Normal maps are used for more detailed lighting effects on a mesh.

### 4.11 Reflection Map

<img src="../image/reflection_map.png" width="25%"/>

- Reflection map assets must be placed in `~\projects\<your_project>\assets\image\reflection_map\`
- Bit depth: `24`
- Reflection maps are used to specify which parts of a mesh are reflective.

### 4.12 Specular Map

<img src="../image/specular_map.png" width="25%"/>

- Specular map assets must be placed in `~\projects\<your_project>\assets\image\specular_map\`
- Bit depth: `24`
- Specular maps are used to specify which parts of a mesh are specular lighted.
