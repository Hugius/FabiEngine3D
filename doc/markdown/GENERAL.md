# General

## 1. Folder structure

```text
~
└── app
  └── binaries (do NOT change)
  └── engine (do NOT change)
  └── projects
    └── <your_project>
      └── assets
        └── audio
        └── image
          └── miscellaneous
            └── flare_map
          └── model
            └── diffuse_map
            └── emission_map
            └── normal_map
            └── reflection_map
            └── refraction_map
            └── specular_map
          └── quad2d
            └── diffuse_map
          └── quad3d
            └── diffuse_map
            └── emission_map
          └── sky
            └── cube_map
          └── terrain
            └── blend_map
            └── diffuse_map
            └── height_map
            └── normal_map
          └── text2d
            └── font_map
          └── text3d
            └── font_map
          └── water
            └── dudv_map
            └── height_map
            └── normal_map
        └── mesh
      └── domain (do NOT change)
      └── saves (do NOT change)
      └── scripts (do NOT change)
      └── worlds (do NOT change)
└── dev (do NOT change)
└── doc (do NOT change)
└── src (do NOT change)
```

## 2. Executable

&#8594; You can start the engine by running `~\app\binaries\fe3d.exe` &#8592;

## 3. Engine interface

- **Center Viewport**: 3D display screen
- **Left Viewport**: editors
- **Top Viewport**: project/preview management
- **Right Viewport**: controls & properties
- **Bottom Viewport**: statistics & logging
