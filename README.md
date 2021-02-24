
# FabiEngine3D
FabiEngine3D is a small game engine for simple 3D games.  
It contains various features such as: asset loading, 2D & 3D rendering, audio, user input, physics, scripting and an engine GUI to work with.  
The engine only uses 2 libraries: OpenGL 4.5 & SDL2. It is written in C++17 and works only on Windows.

# Table of contents
1. [Features](#features)
2. [Engine Interface](#engine-interface)
3. [Folder Structures](#folder-structures)
4. [Development Order](#development-order)
5. [Project Management](#project-management)
6. [Environment Editor](#environment-editor)
7. [Model Editor](#model-editor)
8. [Animation Editor](#animation-editor)
9. [Billboard Editor](#billboard-editor)
10. [Audio Editor](#audio-editor)
11. [Scene Editor](#scene-editor)
12. [Script Editor](#script-editor)
13. [Project Settings](#project-settings)
14. [FabScript](#fabscript)
15. [Function List](#function-list)
16. [Game Execution](#game-execution)
17. [Miscellaneous](#miscellaneous)
18. [Screenshots](#screenshots)

# Features
### Asset Loading
- Multithreaded PNG texture file loading
- Multithreaded OBJ mesh file loading
- Multithreaded WAV audio file loading
- Efficient (pre-)caching system  
### Rendering
- **3D rendering**: sky, terrain, water, model, billboard
- **2D rendering**: image, text
- **Graphics**: ambient lighting, directional lighting, specular reflections, point lights, shadows, sky reflections, realtime scene reflections, fog
- **Textures**: diffuse, cube, normal, reflection, light, height, gui, flare, dudv, displacement, blend, billboard
- **Post processing**: bloom, DOF, motion blur, anti aliasing, sky HDR, lens flare
### Audio
- Custom music playlist
- 2D audio playback
- 3D audio playback (volume distance, stereo panning)
### Input
- Keyboard input
- Mouse input
- Controller input
### Physics
- AABB system
- Collision detection
- Collision response
- Raycasting system
- 3D camera system
- Custom math library
### Scripting
- Custom "FabScript" interpreted language
- Types: integer, decimal, string, boolean, vec3
- Functional programming
- Core engine communication
- Variables & lists
- Looping
- Arithmetic operations: increase, decrease, multiply, divide
- Logical operations: if, elif, else, is, not, and or

# Engine Interface
Click [here](#engine-interface-example) to see an example
The engine GUI is divided into 5 sections:
- Left viewport: editor menus and project settings
- Top viewport: project management & game preview management
- Right viewport: controls & scene editor properties
- Bottom viewport: statistics & logging console
- Mid viewport: 3D display screen

# Folder Structures
The engine root directory has 3 folders:
- `bin\`: this folder holds the .exe file and all corresponding DLLs (do **NOT** touch)
- `engine\`: this folder holds all engine resources such as libraries & shaders (do **NOT** touch)
- `user\`: this folder is where all your game assets are stored. It also holds the project files

# Development Order
- **Project management**
  > In the top-viewport you can create, edit, save and delete projects. 1 project = 1 game
- **Environment editor**
  > This is where you can create environment entities. There are 3 types of environments: sky, terrain, water
- **Model editor**
  > This is where you can create model entities composed of a mesh, textures, AABBs and other properties
- **Animation editor**
  > This is where you can create custom animations using keyframe. Types of animation: translation, rotation, scaling
- **Billboard editor**
  > This is where you can create billboard entities composed of texture/color/text and other properties
- **Audio editor**
  > This is where you can create audio entities composed of an audio file
- **Scene editor**
  > This is where you bring all the created environment, models, animations, billboards and audio together into a scene
- **Script editor**
  > This is where you define your game logic. There are 3 types of logic: initialization, update, destruction
- **Project settings**
  > This is where you can setup mostly graphical properties of your game such as shadow quality, reflection quality, etc

# Project Management
- You can create, edit/load, save and delete a project
- Every **project** is a different **game** and must have a **unique** name
- A project has its own folder in the engine `user\projects\` directory
- An important note is to **NOT** change anything in this directory!
- The only directory that you can change is the `user\assets\`folder

# Environment Editor
### Sky
Click [here](#sky-editor-example) to see an example
- You can create/edit/delete sky environments that can be placed in a scene
- The sky environment is rendered as a **skybox**, which has 6 different texturs
- You can load these 6 images from `user\assets\textures\cube_maps\`
- The image format must be a colored 24bit `PNG`
- The image resolutions must be the same
- Properties include: lightness, color, rotation speed
### Terrain
Click [here](#terrain-editor-example) to see an example
- You can create/edit/delete terrain environments that can be placed in a scene
- The terrain environment is generated with a **height map** texture
- A terrain can have a **diffuse map** texture, but can also be textured using a **blend mapping**
- In total a terrain can be textured with up to 4 different textures!
- All of these rendered textures can be improved with **normal mapping**
- Properties include: max height, UV-repeat, lighting
- **Height map**: grayscale 24bit `BMP` format image file from `user\assets\textures\height_maps\`
- **Blend map**: colored 24bit `PNG` file format image from `user\assets\textures\blend_maps\`
- **Diffuse maps**: colored 24bit `PNG` format image file from `user\assets\textures\diffuse_maps\`
- **Normal maps**: colored 24bit `PNG` format image file from `user\assets\textures\normal_maps\`
### Water
Click [here](#water-editor-example) to see an example
- You can create/edit/delete water environments that can be placed in a scene
- The water environment is simply a **flat plane** in 3D space
- Properties include: position, size, wave height, specular factor & intensity, wave/ripple speed, UV-repeat, color, edge transparency
- You also have the option to show a created terrain while creating a water environment, mainly for having a reference
- Custom color (RGB)
- Sky & terrain reflection (on/off, only shown when above water surface)
- Water refraction (on/off, **Warning**: huge performance impact!)
- Rippling effect (on/off, **DUDV map** needed: colored 24bit `PNG` format image from `user\assets\textures\dudv_maps\`)
- Waves (on/off, **displacement map** needed: grayscale 24bit `PNG` format image from `user\assets\textures\displacement_maps\`)
- Specular reflection (on/off, **normal map** needed: colored 24bit `PNG` format image from `user\assets\textures\normal_maps\`)    

# Model Editor
Click [here](#model-editor-example) to see an example
- You can create/edit/delete models that can be placed in scene or placed with scripting
- A model must **at least** consist of a mesh
- Textures can be added to the model as well as a custom color
- Properties include: size, culling, alpha removal, instanced rendering, color, UV-repeat, level of detail
- Lighting: specular reflection (+ factor & intensity), lightness, shadowed, sky reflection, scene reflection
- You can also add 1 or more **AABBs** to the model. Every individual box has a position and size.
- All AABBs are bound to the model's transformation (translation, rotation, scaling)
- A mesh should be modeled so that the center is at the **lowest** vertex
### Normal mesh
- **Mesh**: `OBJ` format mesh file from `user\assets\meshes`
- **Diffuse map**: colored 24bit/32bit `PNG` format image file from `user\assets\textures\diffuse_maps\`
- **Light map**: colored 24bit `PNG` format image file from `user\assets\textures\light_maps\`
- **Reflection map**: colored 24bit `PNG` format image file from `user\assets\textures\reflection_maps\`
- **Normal map**: colored 24bit `PNG` format image file from `user\assets\textures\normal_maps\`
### Multitextured/multiparted mesh
- A mesh can consist of **multiple parts** (including textures for every part)
- In the **.obj** file, you need to specify when a certain part of vertices starts
- You can start a new mesh part by writing `FE3D_PART <name>` in the OBJ file
- You can bind a **diffuse** map to the part by writing `FE3D_DIFFUSE_MAP <path><filename>` on the next line
- You can bind a **light** map to the part by writing `FE3D_LIGHT_MAP <path><filename>` on the next line
- You can bind a **reflection** map to the part by writing `FE3D_REFLECTION_MAP <path><filename>` on the next line
- You can bind a **normal** map to the part by writing `FE3D_NORMAL_MAP <path><filename>` on the next line

# Animation Editor
Click [here](#animation-editor-example) to see an example
- You can create/edit/delete animations that can be applied to **models** with scripting or in the scene editor
- You can select a **preview model** for the animation playback
- An animation consists of 1 or more **keyframes**
- Every keyframe has a different **target** transformation
- Every keyframe has a different animation **speed**, with 2 types to choose from: **linear & exponential**
- Rotational transformations can each have a different **rotation origin**
- If the model has **multiple parts**, each part has its own transformation every keyframe
- The **last** animation keyframe should be the same as the **initial** frame

# Billboard Editor
Click [here](#billboard-editor-example) to see an example
- You can create/edit/delete billboards that can be placed in a scene or placed with scripting
- There are 2 types of billboards: text & non-text/textured
- A text billboard consists of custom (colored) text using a custom loaded **font**
- A non-text billboard can have a **texture** and/or custom **color**
- A textured billboard can have a **sprite animation**
- Properties include: lightness, color, alpha removal, facing camera X/Y
- When billboard texture is animated, you must specify the amount of rows & columns. You can also set the animation speed.
- Every billboard has its own flat AABB based on their size
- **Font**: `TTF` format font file from `user\assets\fonts`
- **Texture**: colored 24bit/32bit `PNG` format image file from `user\assets\textures\billboard_maps`

# Audio Editor
Click [here](#audio-editor-example) to see an example
- You can create/edit/delete audio that can be placed in a scene or **placed/played** with scripting
- **Audio data**: `WAV` format audio file from `user\assets\audio`
- Audio can be played in **2D**
- Audio can be played in **3D** (position, max distance, max volume)
- 3D audio has stereo panning
- Audio can be added to the **music** playlist

# Scene Editor
Click [here](#scene-editor-example) to see an example
### Environment
- Sky: you can select **only 1** sky, created in the environment editor
- Terrain: you can select **only 1** terrain, created in the environment editor
- Water: you can select **only 1** water, created in the environment editor
### Models
- You can place **multiple** models in the scene
- If a terrain is selected, the model will be placed **on top** of the terrain
- If no terrain is selected, the model will be placed at **XYZ(0,0,0)**
- Every placed model can be **edited** (position, rotation, size, animation, deleting, freezing into local space)
- Placed models are not meant for individual interactions through scripting (only by group).
### Billboards
- You can place **multiple** billboards in the scene
- If a terrain is selected, the billboard will be placed **on top** of the terrain
- If no terrain is selected, the billboard will be placed at **XYZ(0,0,0)**
- Every placed billboard can be **edited** (position, rotation, size, deleting)
- Billboards will **NOT** be affected by scene lighting
- Every billboard's **AABB** will be scaled based on their rotation
- Placed billboards are not meant for individual interactions through scripting (only by group).
### Lights
- You can add **ambient lighting** which has a custom color & intensity
- You can add **directional lighting** which has a custom color, intensity and position
- Directional lighting also has the option to show a lightsource circle billboard (with custom intensity)
- You can place **multiple point lights** in the scene
- If a terrain is selected, the point light will be placed **on top** of the terrain
- If no terrain is selected, the point light will be placed at **XYZ(0,0,0)**
- Every placed point light can be **edited** (position, max distance, intensity, color, deleting)
- Placed lights are not meant for individual interactions through scripting.
### Audio
- You can place **multiple** 3D audio casters in the scene
- If a terrain is selected, the audio caster will be placed **on top** of the terrain
- If no terrain is selected, the audio caster will be placed at **XYZ(0,0,0)**
- Every placed audio caster can be **edited** (position, max volume, max distance, deleting)
- Placed audio casters are not meant for individual interactions through scripting.
### Graphics
- You can add **shadows** to scene based on (casting position, box size, box center, option to follow camera + interval)
- You can enable **motion blur** with a custom strength
- You can enable dynamic Depth Of Field (**DOF**) based on (min distance, blur distance) or enable a static **distant blur**
- You can enable **fog** based on (min distance, max distance, intensity, color)
- You can enable **dynamic skyHDR** based on (max extra intensity)
- You can enable a **lens flare** for directional lighting based on (flare map, intensity, multiplier)
- **Flare map**: colored 24bit `PNG` format image file from `user\assets\textures\flare_maps`
### Other settings
- You can change the editor movement speed, which will be saved for next time
- You can set the minimum distance by which level of detailed models will change their rendering

# Script Editor
Click [here](#script-editor-example) to see an example
- You can create/edit/rename/delete scripts that will be executed in a certain order
- You can use the **mouse** to navigate through the code or use the **arrow keys**
- Script files have a line **limit of 100**, to force you to create small but well-structured scripts
- You can **scroll** through lines using the mousewheel
- You can use CTRL + C to **copy** a **line**
- You can use CTRL + V to **paste** a **line**

# Project Settings
- MSAA qualiity (default: 4)
- Shadow qualiity (default: 2048)
- Reflection qualiity (default: 256)
- Refraction qualiity (default: 256)
- Max audio channels (default: 128)

# FabScript
- FabScript is a custom **interpreted** scripting language created for FabiEngine3D.
- Experience with coding is a prerequisite (Python, Java, C++, C#, Javascript, etc.).
- Scripts are run from the first line to the last line, from left to right.
### META
- Line 1 of every script file should specify its type: initialization, update, destruction
- **Initialization** script: `META script_type_init`
- **Update** script: `META script_type_update`
- **Destruction** script: `META script_type_destroy`
- You also need to specify the first script to run for every type: `META execution_entry`  
#### Example code
```
1. META script_type_init
2. META execution_entry
3. 
4. /// Your code <--- This is a comment by the way
```
### Variables & values
#### Creation syntax
- You can **create** a variable using: `<scope> <mutability> <type> <name> = <value>`
#### Alteration syntax
- You can **edit** a variable using: `EDIT <name> = <value>`
#### Scope
- A variable **scope** can be **global** (`GLOB` keyword) or **local** (no extra keyword)
- A local variable can only be accessed in the **same script** file
- A global variable can be accessed by **ALL** script files
- A local variable will be deleted after **the end** of a script file execution, once created
- A global variable will **never** be deleted, once created
#### Mutability
- A variable can be **immutable** (`CONST` keyword) or **mutable** (no extra keyword)
- If you try to change a CONST variable, you will get an error!
#### Naming conventions
- A variable name **must** be unique and not conflicting with FabScript keywords
- A variable name **must** start with an alpha value (abc...)
- A global variable name **must** start with '_'
#### Casting
- You can **cast** a variable to a different type using: `CAST <name> <type>`
- You can cast from INT to DEC and vice versa
- You can cast from INT to BOOL and vice versa
- You can cast from INT to STR and vice versa (if possible)
- You can cast from DEC to STR and vice versa (if possible)
#### Basic values
- Types to choose from: `VEC3` (vector3), `STR` (string), `INT` (integer), `DEC` (decimal), `BOOL` (boolean)
- A boolean can only be true or false just like binary (example: `<true>` or `<false>`) (NOTE: the < and > are in this case **NOT** placeholders)
- A string can be any characters, as long as it's surrounded with " " (example: `"hello world"`)
- An integer is a whole number which can be negative (example: `42`)
- A decimal is a floating point number which can be negative (example: `42.536`)
#### VEC3
- A vec3 is composed of 3 individual **decimal** values (example: `[1.0 2.0 3.0]`)
- Usually a VEC3 is a position/direction or color
- To **access/change** the individual components, add .x/.y/.z or .r/.g/.b after the variable name (example: `<name>.x`)
#### LIST
- A list is a special type of variable that holds 0 or more **individual values** (example: `{42, "test", <false>}`)
- A list **cannot** hold another list value/variable
- You can **access** individual list components using: `<name>[<index>]`
- You can **add** a new value to the list using: `PUSH <name> <value>`
- You can **delete** an existing value from the list using: `PULL <name> <index>`
- Remember: an index starts from **0**!
- You **cannot** access a VEC3 decimal from a list directly
#### Example code
```
/// Variable syntax for each type
BOOL myBoolean = <false>
STR myString = "hello world"
INT myInteger = 42
DEC myDecimal = 42.94858
VEC3 myVector = [1.0 2.0 3.0]
LIST myList = {42, myBoolean, [4 2 0]}

/// Constant variables
CONST STR immutableString = "i cannot be changed"
STR mutableString = "try to change me"
EDIT mutableString = "i changed you"

/// Global variables
GLOB INT _someInteger = 5
GLOB CONST INT _constInteger = 5

/// Casting variables
CAST myDecimal INT
STR intString = "123"
CAST intString INT

/// Vector3 variable
VEC3 redColor = [1.0 0.0 0.0]
DEC redValue = redColor.r

/// List variable
LIST myList = {"hello", 123, 45.0, redColor, redColor.x, <false>}
STR temp1 = myList[0]
PUSH temp1 "newValue"
PULL temp1 6
```
### Arithmetic operations
#### Arithmetic types
- There are 5 types of arithmetic: addition, subtraction, multiplication, division, negation
- Addition syntax: `INCR <name> <value>`
- Subtraction syntax: `DECR <name> <value>`
- Multiplication syntax: `MUL <name> <value>`
- Division syntax: `DIV <name> <value>`
- Negation syntax: `NEG <name>`
- The result of the arithmetic operation will be stored in the variable the operation was applied on
#### Example code
```
INT myInteger = 40
DIV myInteger 5
NEG myInteger
/// Now myInteger will be -8
```
### Logic operations
#### Comparison operators
- To check if two values are **the same**: `<value> IS <value>`
- To check if two values are **different**: `<value> NOT <value>`
- To check if one value is **higher** than the other: `<value> MORE <value>` (only works for `INT` and `DEC` values)
- To check if one value is **lower** than the other: `<value> LESS <value>` (only works for `INT` and `DEC` values)
- You cannot use different comparison value types (example: `5 IS 5.0` will not work, but `5 IS 5` will do)
#### Logic operators
- To check if **all** the comparison statements are true: `<comparison> AND <comparison>`
- To check if ***any** of the comparison statements are true: `<comparison> OR <comparison>`
- You **cannot** combine the `AND` and `OR` keywords in one logic statement
#### Logic statements
- There are 3 types: if-statement, elif-statement, else-statement
- Every logic statement **must** end with a `:`
- All code under a logic statement **must** must be indented with 4 spaces / 1 TAB
- The order is: if - elif - else
- These statements can be nested infinitely
- Works the same as all other programming languages
#### Example code
```
INT age = 41
IF age IS 41 AND "hello" IS "world":
    fe3d:print("You should not see this message!")
ELIF test IS 42:
    fe3d:print("I am 42!")
ELIF age LESS 42:
    fe3d:print("I am younger than 42!")
ELSE:
    fe3d:print("I am higher than 42!")
```
### Loops
- Use a `LOOP` statement if you want to run a block of code multiple times
- Once a loop is started, you can only get out using the `BREAK` statement
- You can use loops for iterating over a LIST for example
#### Example code
```
LIST myList = {"hello","beautiful", "world"}
INT index = 0
LOOP:
    IF index IS 2:
        BREAK
    fe3d:print(myList[index])
    
/// Console output:
/// > hello
/// > beautiful
/// > world
```
### Executing other scripts
- For every script **type** (init, update, destroy) there is an `execution_entry` META defined
- From there you can decide the **order of execution** yourself
- You can **execute** another script file using: `EXEC <name>`
- After the script is executed, the program will continue running the script **where it left off**
- The script that is executed must have the **same type** as the caller script
- This works the same way as **functions** in other programming languages
#### Example code
```
/// Code in main_script.fe3d
EXEC print_script
fe3d:print("goodbye world")

/// Code in print_script.fe3d
fe3d:print("hello world")

/// Console output:
/// > hello world
/// > goodbye world
```
### Functions
- You can call functions that are built-in FabiEngine3D
- There are 3 types of functions: `fe3d` functions, `math` functions, `misc` functions
- Functions **can** return a value, which can be saved in a variable
#### Example code
```
STR myString = "i am printed"
fe3d:camera_set_position(1.0, 2.0, 3.0)
VEC3 camPos = fe3d:camera_get_position()
fe3d:print(myString)
fe3d:print(camPos.x)

/// Console output:
/// > i am printed
/// > 1.0
```
### Tips & tricks
- You can set the value of a `BOOL` variable to the result of a condition using: `... <name> = (<condition>)`
- You can use the `PASS` statement as an empty placeholder for a logical statement or loop
- Be careful with loops as they can become indefinite. Luckily this will get detected eventually.

# Function List
### Engine functions
#### Input
> You can find all keyboard keys [here](FabiEngine3D/engine/readme/KEYS.md)  
> You can find all mouse buttons [here](FabiEngine3D/engine/readme/BUTTONS.md)
- `fe3d:input_is_key_down`(`STR` key) ---> `BOOL`  
  Returns true is a keyboard **key** is being pushed down.
- `fe3d:input_is_key_pressed`(`STR` key) ---> `BOOL`  
  Returns true is a keyboard **key** is pressed.
- `fe3d:input_is_key_toggled`(`STR` key) ---> `BOOL`  
  Returns true is a keyboard **key** is toggled by a press.
- `fe3d:input_is_mouse_down`(`STR` button) ---> `BOOL`  
  Returns true is a mouse **button** is being pushed down.
- `fe3d:input_is_mouse_pressed`(`STR` button) ---> `BOOL`  
  Returns true is a mouse **button** is pressed.
- `fe3d:input_is_mouse_toggled`(`STR` button) ---> `BOOL`  
  Returns true is a mouse **button** is toggled by a press.
- `fe3d:input_get_mousewheel_direction`() ---> `INT`  
  Returns the direction of the scrolling wheel. 1 = up, -1 = down, 0 = not scrolling.

#### Camera
- `fe3d:camera_move`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the XYZ camera position with speed **xyz**.
- `fe3d:camera_set_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the XYZ camera position to **xyz**.
- `fe3d:camera_get_position`() ---> `VEC3`  
  Returns the XYZ camera position.
- `fe3d:camera_set_lookat_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the XYZ camera lookat position to **xyz**.
- `fe3d:camera_get_lookat_position`() ---> `VEC3`  
  Return the XYZ camera lookat position.
- `fe3d:camera_follow_x`(`DEC` speed) ---> `NONE`  
  Moves the camera in the X direction relative to where the camera is looking at.
- `fe3d:camera_follow_z`(`DEC` speed) ---> `NONE`  
  Moves the camera in the Z direction relative to where the camera is looking at.
- `fe3d:camera_follow_zy`(`DEC` speed) ---> `NONE`  
  Moves the camera in the Z and Y direction relative to where the camera is looking at.
- `fe3d:camera_set_yaw`(`DEC` degrees) ---> `NONE`  
  Sets the camera yaw in **degrees**.
- `fe3d:camera_get_yaw`() ---> `DEC`  
  Returns the camera yaw in degrees.
- `fe3d:camera_set_pitch`(`DEC` degrees) ---> `NONE`  
  Sets the camera pitch in **degrees**. The angle will be clamped between -90.0 and 90.0.
- `fe3d:camera_get_pitch`() ---> `DEC`  
  Returns the camera pitch in degrees.
- `fe3d:camera_set_fov`(`DEC` degrees) ---> `NONE`  
  Sets the camera fov in **degrees**.
- `fe3d:camera_get_fov`() ---> `DEC`  
  Returns the camera FOV in degrees.
- `fe3d:camera_enable_lookat_view`() ---> `NONE`  
  Enable lookat camera view. The camera will ALWAYS be looking at the lookat position.
- `fe3d:camera_disable_lookat_view`() ---> `NONE`  
  Disable lookat camera view.
- `fe3d:camera_is_lookat_view_enabled`() ---> `BOOL`  
  Returns true if lookat camera view is enabled.
- `fe3d:camera_enable_first_person_view`() ---> `NONE`  
  Enable first person camera view. Cursor movement will determine where the camera will be looking at.
- `fe3d:camera_disable_first_person_view`() ---> `NONE`  
  Disable first person camera view.
- `fe3d:camera_is_first_person_view_enabled`() ---> `BOOL`  
  Returns true if first person camera view is enabled.
- `fe3d:camera_set_cursor_speed`(`DEC` speed) ---> `NONE`  
  Sets the **speed** at which the cursor moves.
- `fe3d:camera_center_cursor`() ---> `NONE`  
  Moves the cursor position to the middle of the screen.
- `fe3d:camera_set_max_pitch`(`DEC` degrees) ---> `NONE`  
  Sets the maximum camera pitch in **degrees**.

#### Raycasting
- `fe3d:raycast_enable_terrain_positioning`(`DEC` distance, `DEC` precision) ---> `NONE`  
  Enables raycasting on terrain. Only works when a terrain is selected. **distance** is the maximum distance from the camera towards a point on the terrain. **precision** is how   precise the raycast should be. These values have impact on the performance!
- `fe3d:raycast_disable_terrain_positioning`() ---> `NONE`  
  Disables raycasting on terrain.
- `fe3d:raycast_get_vector`() ---> `VEC3`  
  Returns the raycast vector (from 2D cursor position to 3D ray).
- `fe3d:raycast_get_position_on_terrain`() ---> `VEC3`  
  Returns the 3D raycasted position of the cursor that intersects with the terrain. Returns -1.0 if not intersecting with terrain.
- `fe3d:raycast_is_position_on_terrain_valid`() ---> `BOOL`  
  Returns true if 3D cursor position is valid.
- `fe3d:raycast_into_model`(`STR` model, `STR` aabbpart, `BOOL` occludable) ---> `STR`  
  Returns the ID of the model that is selected. All models which ID starts with **model** will be checked (leave empty for all models). Only the **aabbpart** will be checked (leave empty for all parts). **occludable** means if the raycast can be blocked by other AABBs.
- `fe3d:raycast_into_models`() ---> `STR`  
  Returns the ID of any model that is selected.
- `fe3d:raycast_into_billboard`(`STR` billboard,  `BOOL` occludable) ---> `STR`  
  Returns the ID of the billboard that is selected. All billboards which ID starts with **billboards** will be checked (leave empty for all billboards). **occludable** means if the raycast can be blocked by other AABBs.
- `fe3d:raycast_into_billboards`() ---> `STR`  
  Returns the ID of any billboard that is selected.
- `fe3d:raycast_into_model_distance`(`STR` model, `STR` aabbpart, `BOOL` occludable) ---> `DEC`  
  Returns the distance to the model that is selected. All models which ID starts with **model** will be checked (leave empty for all models). Only the **aabbpart** will be checked (leave empty for all parts). **occludable** means if the raycast can be blocked by other AABBs. Returns -1.0 if the model is not selected.
- `fe3d:raycast_into_models_distance`() ---> `DEC`  
  Returns the distance to any model that is selected. Returns -1.0 if no model is selected.
- `fe3d:raycast_into_billboard_distance`(`STR` billboard,  `BOOL` occludable) ---> `DEC`  
  Returns the distance to the billboard that is selected. All billboards which ID starts with **billboards** will be checked (leave empty for all billboards). **occludable** means if the raycast can be blocked by other AABBs. Returns -1.0 if the billboard is not selected.
- `fe3d:raycast_into_billboards_distance`() ---> `DEC`  
  Returns the distance to any billboard that is selected. Returns -1.0 if the billboard is not selected.
  
#### Collision
- `fe3d:collision_enable_camera_terrain_response`(`DEC` height,  `DEC` speed) ---> `NONE`  
  Enables camera collision with the terrain surface (if existing). **height** is the minimum height the camera should be above the terrain. **speed** is the speed at which the camera corrects its height based on the terrain surface.
- `fe3d:collision_disable_camera_terrain_response`() ---> `NONE`  
  Disables camera collision with the terrain surface (if existing).
- `fe3d:collision_is_camera_under_terrain`() ---> `BOOL`  
  Returns true if the camera is under the terrain surface (if existing).
- `fe3d:collision_set_camera_box`(`DEC` bottom, `DEC` top, `DEC` left, `DEC` right, `DEC` front, `DEC` back) ---> `NONE`  
  Defines the dimensions of the bounding box around the camera. All parameters are offsets from the camera position.
- `fe3d:collision_enable_camera_aabb_response`(`BOOL` x, `BOOL` y, `BOOL` z) ---> `NONE`  
  Enables collision detection & response between the camera and AABBs. You can specify which directions (**x** and/or **y** and/or **z**) of collision need to be checked.
- `fe3d:collision_disable_camera_aabb_response`() ---> `NONE`  
  Disables collision detection & response between the camera and AABBs.
- `fe3d:collision_check_camera_model`(`STR` model, `STR` aabbpart, `STR` direction) ---> `STR`  
  Returns the ID of the model that has collided with the camera. All models which ID starts with **model** will be checked (leave empty for all models). Only the **aabbpart** part will be checked (leave empty for all parts). You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_models`(`STR` direction) ---> `STR`  
  Return the ID of any model that has collided with the camera. You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_aabb`(`STR` aabbpart, `STR` direction) ---> `STR`  
  Returns the ID of the AABB that has collided with the camera. All AABBs which ID starts with **aabbpart** will be checked (leave empty for all AABBs). You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_camera_aabbs`(`STR` direction) ---> `STR`  
  Return the ID of any AABB that has collided with the camera. You can specify in which **direction** you want to check. It can be either "X", "Y", "Z" or empty ("").
- `fe3d:collision_check_model_models`(`STR` model1, `STR` aabbpart1, `STR` model2, `STR` aabbpart2) ---> `STR`  
  Returns the ID of the model that has collided with the **aabbpart1** of **model1**. All models which ID starts with **model2** will be checked (leave empty for all models). Only the **aabbpart2** will be checked (leave empty for all parts).
- `fe3d:collision_check_model_billboards`(`STR` model, `STR` aabbpart, `STR` billboard) ---> `STR`  
  Returns the ID of the billboard that has collided with the **aabbpart** of **model**. All billboards which ID starts with **billboard** will be checked (leave empty for all billboards).
- `fe3d:collision_check_model_aabbs`(`STR` model, `STR` aabbpart, `STR` aabb) ---> `STR`  
  Returns the ID of the AABB that has collided with the **aabbpart** of **model**. All AABBs which ID starts with **aabb** will be checked (leave empty for all AABBs).

#### Graphics
- `fe3d:graphics_set_ambient_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets ambient lighting color as **rgb**.
- `fe3d:graphics_get_ambient_light_color`() ---> `VEC3`  
  Returns ambient lighting color.
- `fe3d:graphics_set_ambient_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets ambient lighting **intensity**.
- `fe3d:graphics_get_ambient_light_intensity`() ---> `DEC`  
  Returns ambient lighting intensity.
- `fe3d:graphics_set_directional_light_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets directional lighting position as **xyz**.
- `fe3d:graphics_get_directional_light_position`() ---> `VEC3`  
  Returns directional lighting position*.
- `fe3d:graphics_set_directional_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets directional lighting color as **rgb**.
- `fe3d:graphics_get_directional_light_color`() ---> `VEC3`  
  Returns directional lighting color.
- `fe3d:graphics_set_directional_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets directional lighting **intensity**.
- `fe3d:graphics_get_directional_light_intensity`() ---> `DEC`  
  Returns directional lighting intensity.
- `fe3d:graphics_enable_spot_light`() ---> `NONE`  
  Enables spot lighting from camera.
- `fe3d:graphics_disable_spot_light`() ---> `NONE`  
  Disables spot lighting from camera.
- `fe3d:graphics_set_spot_light_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets spot lighting color as **rgb**.
- `fe3d:graphics_get_spot_light_color`() ---> `VEC3`  
  Returns spot lighting color.
- `fe3d:graphics_set_spot_light_intensity`(`DEC` intensity) ---> `NONE`  
  Sets spot lighting **intensity**.
- `fe3d:graphics_get_spot_light_intensity`() ---> `DEC`  
  Returns spot lighting intensity.
- `fe3d:graphics_set_spot_light_angle`(`DEC` angle) ---> `NONE`  
  Sets spot lighting **angle**.
- `fe3d:graphics_get_spot_light_angle`() ---> `DEC`  
  Returns spot lighting angle.
- `fe3d:graphics_set_spot_light_distance`(`DEC` distance) ---> `NONE`  
  Sets spot lighting **distance**.
- `fe3d:graphics_get_spot_light_distance`() ---> `DEC`  
  Returns spot lighting angle.
- `fe3d:graphics_set_fog_min_distance`(`DEC` distance) ---> `NONE`  
  Sets minimum fog **distance**.
- `fe3d:graphics_get_fog_min_distance`() ---> `DEC`  
  Returns minimum fog distance.
- `fe3d:graphics_set_fog_max_distance`(`DEC` distance) ---> `NONE`  
  Sets maximum fog **distance**.
- `fe3d:graphics_get_fog_max_distance`() ---> `DEC`  
  Returns maximum fog distance.
- `fe3d:graphics_set_fog_thickness`(`DEC` thickness) ---> `NONE`  
  Sets fog **thickness** percentage (0.0 - 1.0).
- `fe3d:graphics_get_fog_thickness`() ---> `DEC`  
  Returns fog thickness percentage (0.0 - 1.0).
- `fe3d:graphics_set_fog_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets fog color as **rgb**.
- `fe3d:graphics_get_fog_color`() ---> `VEC3`  
  Returns fog color as **rgb**.
- `fe3d:graphics_set_shadow_position`(`DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets shadow caster position as **xyz**.
- `fe3d:graphics_get_shadow_position`() ---> `VEC3`  
  Returns shadow caster position.
- `fe3d:graphics_enable_light_mapping`() ---> `NONE`  
  Enables light mapping effect.
- `fe3d:graphics_disable_light_mapping`() ---> `NONE`  
  Disables light mapping effect.
- `fe3d:graphics_enable_point_lighting`() ---> `NONE`  
  Enables point lighting.
- `fe3d:graphics_disable_point_lighting`() ---> `NONE`  
  Disables point lighting.

#### Sky
- `fe3d:sky_mix_with_current`(`STR` skyID) ---> `NONE`  
  Blends the selected sky texture with the texture of **skyID**.
- `fe3d:sky_set_mix_value`(`DEC` value) ---> `NONE`  
  Sets the mix **value** to blend the 2 sky textures. The value must be between 0.0 and 1.0 (0% and 100% respectively).
- `fe3d:sky_get_mix_value`() ---> `DEC`  
  Returns the mix value of the selected sky.
- `fe3d:sky_set_rotation_speed`(`DEC` speed) ---> `NONE`  
  Sets the rotation **speed** of the selected sky.
- `fe3d:sky_get_rotation_speed`() ---> `DEC`  
  Returns the rotation **speed** of the selected sky.

#### Terrain
- `fe3d:terrain_get_max_height`() ---> `DEC`  
  Returns the maximum height of the selected terrain (based on the heightmap pixels values).
- `fe3d:terrain_get_size`() ---> `DEC`  
  Returns size of the selected terrain.
- `fe3d:terrain_get_pixel_height`(`DEC` x, `DEC` z) ---> `DEC`  
  Returns the height of the pixel in the selected terrain height map based on X and Z. Returns 0.0 if **x** or **z** is invalid.

#### Water
- `fe3d:water_set_speed`(`DEC` x, `DEC` z) ---> `NONE`  
  Sets the rippling/waving speed of the selected water in the **x** direction and **z** direction.
- `fe3d:water_get_speed_x`() ---> `DEC`  
  Returns the rippling/waving speed of the selected water in the X direction.
- `fe3d:water_get_speed_z`() ---> `DEC`  
  Returns the rippling/waving speed of the selected water in the Z direction.
- `fe3d:water_get_height`() ---> `DEC`  
  Returns the height (Y position) of the selected water.
- `fe3d:water_set_color`(`DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color of the selected water based on the **r g b** channels.
- `fe3d:water_get_color`() ---> `VEC3`  
  Returns the color of the selected water.

#### Model
- `fe3d:model_is_existing`() ---> `BOOL`  
  Returns true if model is existing.
- `fe3d:model_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all models which IDs start with **subID**.
- `fe3d:model_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the IDs of all models.
- `fe3d:model_place`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Places a new model with **newID** (cannot start with @) based on model with **previewID** at position as **xyz**.
- `fe3d:model_delete`(`STR` ID) ---> `NONE`  
  Deletes model with **ID** if existing.
- `fe3d:model_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of model with **ID** to **visible**.
- `fe3d:model_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if model with **ID** is visible.
- `fe3d:model_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of model with **ID**.
- `fe3d:model_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of model with **ID**.
- `fe3d:model_set_rotation_origin`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation origin of model with **ID** to **xyz** in local space. The model will be rotated around this origin. An xyz of 0 means the rotation will be centered.
- `fe3d:model_get_rotation_origin`() ---> `VEC3`  
  Returns the rotation origin of model with **ID**.
- `fe3d:model_set_rotation`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation as **xyz** of model with **ID**.
- `fe3d:model_rotate`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Rotates the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_rotation`(`STR` ID) ---> `VEC3`  
  Returns the rotation of model with **ID**.
- `fe3d:model_set_size`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the size as **xyz** of model with **ID**.
- `fe3d:model_scale`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Scales the model with factor **xyz** of model with **ID**.
- `fe3d:model_get_size`(`STR` ID) ---> `VEC3`  
  Returns the size of model with **ID**.
- `fe3d:model_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of model with **ID**.
- `fe3d:model_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of model with **ID**.
- `fe3d:model_set_min_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local minimum **height** of model with **ID**. The height is relative to the model position.
- `fe3d:model_get_min_height`(`STR` ID) ---> `DEC`  
  Returns the minimum local height of model with **ID**.
- `fe3d:model_set_max_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local maximum **height** of model with **ID**. The height is relative to the model position.
- `fe3d:model_get_max_height`(`STR` ID) ---> `DEC`  
  Returns the maximum local height of model with **ID**.
- `fe3d:model_set_lightness`(`STR` ID, `DEC` lightness) ---> `NONE`  
  Sets the **lightness** of model with **ID**.
- `fe3d:model_get_lightness`(`STR` ID) ---> `DEC`  
  Returns the lightness of model with **ID**.
- `fe3d:model_set_aabb_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the model's parent AABB raycasting responsiveness to **responsive** of model with **ID**.
- `fe3d:model_set_aabb_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the model's parent AABB collision responsiveness to **responsive** of model with **ID**.
- `fe3d:model_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of model with **ID**. Keep in mind FabiEngine3D does not support transparency sorting!
- `fe3d:model_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of model with **ID**.

#### Animations
- `fe3d:model_start_animation`(`STR` modelID, `STR` animationID, `INT` loops) ---> `NONE`  
  Starts the animation with **animationID** on model with **modelID** and repeat it **loops** times.
- `fe3d:model_is_animation_started`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** was started (can be paused or playing) on model with **modelID**.
- `fe3d:model_is_animation_playing`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** is currently playing (not paused) on model with **modelID**.
- `fe3d:model_is_animation_paused`(`STR` modelID, `STR` animationID) ---> `BOOL`  
  Returns true if animation with **animationID** is currently paused (not playing) on model with **modelID**.
- `fe3d:model_pause_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Pauses the animation with **animationID** on model with **modelID**. Only possible when animation is currently playing.
- `fe3d:model_resume_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Resumes the animation with **animationID** on model with **modelID**. Only possible when animation is currently paused.
- `fe3d:model_fade_animation`(`STR` modelID, `STR` animationID, `INT` frameStep) ---> `NONE`  
  Fades the animation with **animationID** on model with **modelID** to an end. Every **frameStep** amount of frames the animation will stop. Only possible when animation is currently playing.
- `fe3d:model_stop_animation`(`STR` modelID, `STR` animationID) ---> `NONE`  
  Stops the animation with **animationID** on model with **modelID**.  Only possible when animation is currently playing.
- `fe3d:model_set_animation_speed`(`STR` modelID, `STR` animationID, `DEC` speed) ---> `NONE`  
  Sets the animation **speed** of animation with **animationID** on model with **modelID**.
- `fe3d:model_get_animation_frame_index`(`STR` modelID, `STR` animationID) ---> `INT`  
  Returns the current animation frame index of animation with **animationID** on model with **modelID**. An index starts at 0!

#### Billboard
- `fe3d:billboard_is_existing`() ---> `BOOL`  
  Returns true if billboard is existing.
- `fe3d:billboard_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all billboards which IDs start with **subID**.
- `fe3d:billboard_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all billboards.
- `fe3d:billboard_place`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Places a new billboard with **newID** (cannot start with @) based on billboard with **previewID** at position as **xyz**.
- `fe3d:billboard_delete`(`STR` ID) ---> `NONE`  
  Deletes billboard with **ID** if existing.
- `fe3d:billboard_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of billboard with **ID** to **visible**.
- `fe3d:billboard_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is visible.
- `fe3d:billboard_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of billboard with **ID**.
- `fe3d:billboard_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the billboard with factor **xyz** of billboard with **ID**.
- `fe3d:billboard_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of billboard with **ID**.
- `fe3d:billboard_set_rotation`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the rotation as **xyz** of billboard with **ID**.
- `fe3d:billboard_rotate`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Rotates the billboard with factor **xyz** of billboard with **ID**.
- `fe3d:billboard_get_rotation`(`STR` ID) ---> `VEC3`  
  Returns the rotation of billboard with **ID**.
- `fe3d:billboard_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of billboard with **ID**.
- `fe3d:billboard_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the billboard with factor **xy** of billboard with **ID**.
- `fe3d:billboard_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of billboard with **ID**.
- `fe3d:billboard_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of billboard with **ID**.
- `fe3d:billboard_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of billboard with **ID**.
- `fe3d:billboard_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of billboard with **ID**.
- `fe3d:billboard_set_min_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local minimum **height** of billboard with **ID**. The height is relative to the billboard position.
- `fe3d:billboard_get_min_height`(`STR` ID) ---> `DEC`  
  Returns the minimum local height of billboard with **ID**.
- `fe3d:billboard_set_max_height`(`STR` ID, `DEC` height) ---> `NONE`  
  Sets the local maximum **height** of billboard with **ID**. The height is relative to the billboard position.
- `fe3d:billboard_get_max_height`(`STR` ID) ---> `DEC`  
  Returns the maximum local height of billboard with **ID**.
- `fe3d:billboard_set_lightness`(`STR` ID, `DEC` lightness) ---> `NONE`  
  Sets the **lightness** of billboard with **ID**.
- `fe3d:billboard_get_lightness`(`STR` ID) ---> `DEC`  
  Returns the lightness of billboard with **ID**.
- `fe3d:billboard_set_aabb_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the billboard's parent AABB raycasting responsiveness to **responsive** of billboard with **ID**.
- `fe3d:billboard_set_aabb_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the billboard's parent AABB collision responsiveness to **responsive** of billboard with **ID**.
- `fe3d:billboard_set_camera_facing_x`(`STR` ID, `BOOL` facing) ---> `NONE`  
  Sets camera **facing** in the X direction for billboard with **ID**.
- `fe3d:billboard_is_facing_camera_x`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is facing the camera in the X direction.
- `fe3d:billboard_set_camera_facing_y`(`STR` ID, `BOOL` facing) ---> `NONE`  
  Sets camera **facing** in the Y direction for billboard with **ID**.
- `fe3d:billboard_is_facing_camera_y`(`STR` ID) ---> `BOOL`  
  Returns true if billboard with **ID** is facing the camera in the Y direction.
- `fe3d:billboard_start_animation`(`STR` ID, `INT` loops) ---> `NONE`  
  Starts the sprite animation of billboard with **ID** and repeat it **loops** times.
- `fe3d:billboard_is_animation_playing`(`STR` ID) ---> `BOOL`  
  Returns true if animation of billboard with **ID** is playing.
- `fe3d:billboard_stop_animation`(`STR` ID) ---> `NONE`  
  Stops the sprite animation of billboard with **ID**.
- `fe3d:billboard_is_animation_finished`(`STR` ID) ---> `BOOL`  
  Returns true if animation of billboard with **ID** is finished.
- `fe3d:billboard_set_text`(`STR` ID, `STR` text) ---> `NONE`  
  Sets the text content of billboard with **ID**.
- `fe3d:billboard_get_text`(`STR` ID) ---> `STR`  
  Returns the text content of billboard with **ID**.

#### AABB
- `fe3d:aabb_is_existing`() ---> `BOOL`  
  Returns true if AABB is existing.
- `fe3d:aabb_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all AABBs which IDs start with **subID**.
- `fe3d:aabb_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all AABB.
- `fe3d:aabb_place`(`STR` newID, `DEC` x, `DEC` y, `DEC` z, `DEC` width, `DEC` height, `DEC` depth) ---> `NONE`  
  Places a new AABB with **newID** (cannot start with @) with size of **width**, **height**, **depth** at position as **xyz**.
- `fe3d:aabb_delete`(`STR` ID) ---> `NONE`  
  Deletes AABB with **ID** if existing.
- `fe3d:aabb_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of AABB with **ID** to **visible**.
- `fe3d:aabb_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if AABB with **ID** is visible.
- `fe3d:aabb_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of AABB with **ID**.
- `fe3d:aabb_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the AABB with factor **xyz** of AABB with **ID**.
- `fe3d:aabb_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of AABB with **ID**.
- `fe3d:aabb_set_size`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the size as **xyz** of AABB with **ID**.
- `fe3d:aabb_scale`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Scales the AABB with factor **xyz** of AABB with **ID**.
- `fe3d:aabb_get_size`(`STR` ID) ---> `VEC3`  
  Returns the size of AABB with **ID**.
- `fe3d:aabb_set_raycast_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the AABB raycasting responsiveness to **responsive** of AABB with **ID**.
- `fe3d:aabb_set_collision_responsive`(`STR` ID, `BOOL` responsive) ---> `NONE`  
  Sets the AABB collision responsiveness to **responsive** of AABB with **ID**.

#### Light
- `fe3d:light_is_existing`() ---> `BOOL`  
  Returns true if light is existing.
- `fe3d:light_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all lights which IDs start with **subID**.
- `fe3d:light_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all light.
- `fe3d:light_place`(`STR` newID, `DEC` x, `DEC` y, `DEC` z, `DEC` r, `DEC` g, `DEC` b, `DEC` intensity, `DEC` distance) ---> `NONE`  
  Places a new light with **newID** (cannot start with @) at position as **xyz** with color as **rgb**. It also has an **intensity** and maximum **distance**.
- `fe3d:light_delete`(`STR` ID) ---> `NONE`  
  Deletes light with **ID** if existing.
- `fe3d:light_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of light with **ID** to **visible**.
- `fe3d:light_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if light with **ID** is visible.
- `fe3d:light_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of light with **ID**.
- `fe3d:light_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the light with factor **xyz** of light with **ID**.
- `fe3d:light_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of light with **ID**.
- `fe3d:light_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of light with **ID**.
- `fe3d:light_get_color`(`STR` ID) ---> `DEC`  
  Returns the color of light with **ID**.
- `fe3d:light_set_intensity`(`STR` ID, `DEC` intensity) ---> `NONE`  
  Sets the **intensity** of light with **ID**.
- `fe3d:light_get_intensity`(`STR` ID) ---> `DEC`  
  Returns the intensity of light with **ID**.
- `fe3d:light_set_distance`(`STR` ID, `DEC` distance) ---> `NONE`  
  Sets the **distance** of light with **ID**.
- `fe3d:light_get_distance`(`STR` ID) ---> `DEC`  
  Returns the distance of light with **ID**.

#### Audio
- `fe3d:audio_is_existing`() ---> `BOOL`  
  Returns true if audio is existing.
- `fe3d:audio_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all audio which IDs start with **subID**.
- `fe3d:audio_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all audios.
- `fe3d:audio_place2D`(`STR` newID, `STR` previewID) ---> `NONE`  
  Places a new 2D audio with **newID** (cannot start with @) based on audio with **previewID**.
- `fe3d:audio_place3D`(`STR` newID, `STR` previewID, `DEC` x, `DEC` y, `DEC` z, `DEC` volume, `DEC` distance) ---> `NONE`  
  Places a new 3D audio with **newID** (cannot start with @) based on audio with **previewID** at position as **xyz** at a maximum **volume** and **distance**.
- `fe3d:audio_delete`(`STR` ID) ---> `NONE`  
  Deletes audio with **ID** if existing.
- `fe3d:audio_play`(`STR` ID, `INT` loops, `DEC` volume) ---> `NONE`  
  Play audio with **ID** and repeat it **loops** times at a maximum **volume**.
- `fe3d:audio_set_position`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Sets the position as **xyz** of audio with **ID**.
- `fe3d:audio_move`(`STR` ID, `DEC` x, `DEC` y, `DEC` z) ---> `NONE`  
  Moves the audio with factor **xyz** of audio with **ID**.
- `fe3d:audio_get_position`(`STR` ID) ---> `VEC3`  
  Returns the position of audio with **ID**.
- `fe3d:audio_set_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the **volume** of audio with **ID**.
- `fe3d:audio_get_volume`(`STR` ID) ---> `DEC`  
  Returns the volume of audio with **ID**.
- `fe3d:audio_set_max_volume`(`STR` ID, `DEC` volume) ---> `NONE`  
  Sets the maximum **volume** of 3D audio with **ID**.
- `fe3d:audio_get_max_volume`(`STR` ID) ---> `DEC`  
  Returns the maximum volume of 3D audio with **ID**.
- `fe3d:audio_set_max_distance`(`STR` ID, `DEC` distance) ---> `NONE`  
  Sets the maximum **distance** of 3D audio with **ID**.
- `fe3d:audio_get_max_distance`(`STR` ID) ---> `DEC`  
  Returns the maximum distance of 3D audio with **ID**.

#### Music
- `fe3d:music_add_to_playlist`(`STR` previewID) ---> `NONE`  
  Adds music to the playlist based on audio with **previewID**.
- `fe3d:music_clear_playlist`() ---> `NONE`  
  Clears and stops all music from the playlist.
- `fe3d:music_set_volume`(`DEC` volume) ---> `NONE`  
  Sets music volume.
- `fe3d:music_get_volume`(`STR` previewID) ---> `DEC`  
  Returns music volume.
- `fe3d:music_is_playing`(`STR` previewID) ---> `BOOL`  
  Returns true if music is playing.
- `fe3d:music_pause`() ---> `NONE`  
  Pauses playing music.
- `fe3d:music_is_paused`() ---> `BOOL`  
  Returns true if music is paused.
- `fe3d:music_resume`() ---> `NONE`  
  Resumes paused music.

#### Image
- `fe3d:image_is_existing`() ---> `BOOL`  
  Returns true if image is existing.
- `fe3d:image_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all images which IDs start with **subID**.
- `fe3d:image_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all images.
- `fe3d:image_place`(`STR` newID, `STR` texturePath, `DEC` x, `DEC` y, `DEC` rotation, `DEC` width, `DEC` height) ---> `NONE`  
  Places a new image with **newID** (cannot start with @) with a texture from **texturePath** at position as **xy** with **rotation** and size as **width** & **height**.
- `fe3d:image_delete`(`STR` ID) ---> `NONE`  
  Deletes image with **ID** if existing.
- `fe3d:image_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of image with **ID** to **visible**.
- `fe3d:image_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if image with **ID** is visible.
- `fe3d:image_set_position`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the position as **xy** of image with **ID**.
- `fe3d:image_move`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Moves the image with factor **xy** of image with **ID**.
- `fe3d:image_get_position_x`(`STR` ID) ---> `DEC`  
  Returns the X position of image with **ID**.
- `fe3d:image_get_position_y`(`STR` ID) ---> `DEC`  
  Returns the Y position of image with **ID**.
- `fe3d:image_set_rotation`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Sets the **rotation** of image with **ID**.
- `fe3d:image_rotate`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Rotates the image with factor **rotation** of image with **ID**.
- `fe3d:image_get_rotation`(`STR` ID) ---> `DEC`  
  Returns the rotation of image with **ID**.
- `fe3d:image_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of image with **ID**.
- `fe3d:image_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the image with factor **xy** of image with **ID**.
- `fe3d:image_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of image with **ID**.
- `fe3d:image_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of image with **ID**.
- `fe3d:image_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of image with **ID**.
- `fe3d:image_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of image with **ID**.
- `fe3d:image_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of image with **ID**.
- `fe3d:image_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of image with **ID**.

#### Text
- `fe3d:text_is_existing`() ---> `BOOL`  
  Returns true if text is existing.
- `fe3d:text_find_ids`(`STR` subID) ---> `LIST`  
  Returns a list of strings with the IDs of all text which IDs start with **subID**.
- `fe3d:text_get_all_ids`() ---> `LIST`  
  Returns a list of strings with the full IDs of all texts.
- `fe3d:text_place`(`STR` newID, `STR` fontPath, `STR` content, `DEC` x, `DEC` y, `DEC` rotation, `DEC` width, `DEC` height) ---> `NONE`  
  Places a new text (**content**) with **newID** (cannot start with @) with a font from **fontPath** at position as **xy** with **rotation** and size as **width** & **height**.
- `fe3d:text_delete`(`STR` ID) ---> `NONE`  
  Deletes text with **ID** if existing.
- `fe3d:text_set_visible`(`STR` ID, `BOOL` visible) ---> `NONE`  
  Sets the visibility of text with **ID** to **visible**.
- `fe3d:text_is_visible`(`STR` ID) ---> `BOOL`  
  Returns true if text with **ID** is visible.
- `fe3d:text_set_position`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the position as **xy** of text with **ID**.
- `fe3d:text_move`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Moves the text with factor **xy** of text with **ID**.
- `fe3d:text_get_position_x`(`STR` ID) ---> `DEC`  
  Returns the X position of text with **ID**.
- `fe3d:text_get_position_y`(`STR` ID) ---> `DEC`  
  Returns the Y position of text with **ID**.
- `fe3d:text_set_rotation`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Sets the **rotation** of text with **ID**.
- `fe3d:text_rotate`(`STR` ID, `DEC` rotation) ---> `NONE`  
  Rotates the text with factor **rotation** of text with **ID**.
- `fe3d:text_get_rotation`(`STR` ID) ---> `DEC`  
  Returns the rotation of text with **ID**.
- `fe3d:text_set_size`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Sets the size as **xy** of text with **ID**.
- `fe3d:text_scale`(`STR` ID, `DEC` x, `DEC` y) ---> `NONE`  
  Scales the text with factor **xy** of text with **ID**.
- `fe3d:text_get_width`(`STR` ID) ---> `DEC`  
  Returns the width of text with **ID**.
- `fe3d:text_get_height`(`STR` ID) ---> `DEC`  
  Returns the height of text with **ID**.
- `fe3d:text_set_color`(`STR` ID, `DEC` r, `DEC` g, `DEC` b) ---> `NONE`  
  Sets the color as **rgb** of text with **ID**.
- `fe3d:text_get_color`(`STR` ID) ---> `VEC3`  
  Returns the color of text with **ID**.
- `fe3d:text_set_content`(`STR` ID, `STR` content) ---> `NONE`  
  Sets the **content** of text with **ID**.
- `fe3d:text_get_content`(`STR` ID) ---> `DEC`  
  Returns the content of text with **ID**.
- `fe3d:text_set_alpha`(`STR` ID, `DEC` alpha) ---> `NONE`  
  Sets the **alpha** value for transparency of text with **ID**.
- `fe3d:text_get_alpha`(`STR` ID) ---> `DEC`  
  Returns the alpha value of text with **ID**.

#### Miscellaneous
- `fe3d:game_pause`() ---> `NONE`  
  Pauses all internal game/engine updates if playing (except for the scripting of course).
- `fe3d:game_unpause`() ---> `NONE`  
  Unpauses all internal game/engine updates if paused.
- `fe3d:game_stop`() ---> `NONE`  
  Stops the game.
- `fe3d:print`(`VEC3/STR/DEC/INT/BOOL` message) ---> `NONE`  
  Prints a value to the console (both internal & external). Accepts various message types.
- `fe3d:scene_load`(`STR` ID) ---> `NONE`  
  Loads the scene with **ID** into the game. Any previously loaded scene will be cleared.
- `fe3d:scene_clear`() ---> `NONE`  
  Deletes (or resets) all stuff in the currently loaded scene (such as models, billboard, graphics, etc).
- `fe3d:scene_get_current_id`() ---> `STR`  
  Returns ID of currently loaded scene.
- `fe3d:cursor_show`() ---> `NONE`  
  Makes mouse cursor visible.
- `fe3d:cursor_hide`() ---> `NONE`  
  Makes mouse cursor invisible.

### Math functions
- `math:tan`(`DEC` degrees) ---> `DEC`  
  Returns the tangent of **degrees**.
- `math:sin`(`DEC` degrees) ---> `DEC`  
  Returns the sine of **degrees**.
- `math:cos`(`DEC` degrees) ---> `DEC`  
  Returns the cosine of **degrees**.
- `math:atan`(`DEC` value) ---> `DEC`  
  Returns the arc tangent of **value**.
- `math:asin`(`DEC` value) ---> `DEC`  
  Returns the arc sine of **value**.
- `math:acos`(`DEC` value) ---> `DEC`  
  Returns the arc cosine of **value**.
- `math:atan2`(`DEC` first, `DEC` second) ---> `DEC`  
  Returns the arc tangent of **first** and **second**.
- `math:pow`(`INT` base, `INT` exponent) ---> `INT`  
  Returns the result of **base** to the power of **exponent**.
- `math:pow`(`DEC` base, `DEC` exponent) ---> `DEC`  
  Returns the result of **base** to the power of **exponent**.
- `math:min`(`INT` first, `INT` second) ---> `INT`  
  Returns the lower value of **first** and **second**.
- `math:min`(`DEC` first, `DEC` second) ---> `DEC`  
  Returns the lower value of **first** and **second**.
- `math:max`(`INT` first, `INT` second) ---> `INT`  
  Returns the higher value of **first** and **second**.
- `math:max`(`DEC` first, `DEC` second) ---> `DEC`  
  Returns the higher value of **first** and **second**.
- `math:clamp`(`INT` value, `INT` min, `INT` max) ---> `INT`  
  Returns the clamped **value** between **min** and **max**.
- `math:clamp`(`DEC` value, `DEC` min, `DEC` max) ---> `DEC`  
  Returns the clamped **value** between **min** and **max**.
- `math:sqrt`(`DEC` value) ---> `DEC`  
  Returns the square root of **value**.
- `math:abs`(`INT` value) ---> `INT`  
  Returns the absolute value of **value**.
- `math:abs`(`DEC` value) ---> `DEC`  
  Returns the absolute value of **value**.
- `math:distance`(`VEC3` first, `VEC3` second) ---> `DEC`  
  Returns the absolute distance between **first** and **second**.

### Miscellaneous functions
- `misc:concat_strings`(`STR` first, `STR` second) ---> `STR`  
  Returns **first** and **second** concatenated together.
- `misc:get_list_size`(`STR` name) ---> `INT`  
  Returns the counted total of list items and returns the amount. **name** must be put in a string value.
- `misc:get_string_size`(`STR` value) ---> `INT`  
  Returns the counted total of **value** characters and returns the amount.
- `misc:get_string_part`(`STR` value, `INT` index, `INT` count) ---> `STR`  
  Returns a part from **value**. Example: **value** = "test", **index** = 1, **count** = 2, returns:"est".
- `misc:get_unique_integer`(`INT` min, `INT` max) ---> `INT`  
  Returns a unique random integer between **min** and **max**.
- `misc:get_random_integer`(`INT` min, `INT` max) ---> `INT`  
  Returns a random integer between **min** and **max**.
- `misc:get_random_decimal`(`DEC` min, `DEC` max) ---> `DEC`  
  Returns a random decimal between **min** and **max**.
- `misc:time_interval`(`STR` name, `INT` frames) ---> `BOOL`  
  Returns true every **frames** for the unique **name**.

# Game Execution
### Inside engine interface
![execution](FabiEngine3D/engine/readme/execution.png)
- You can play/pause/resume/stop the game preview
- All changes made with the scripting will be reset when the preview exits
- You can pause the gameplay with **ESCAPE**
### Outside engine interface
- Exit FabiEngine3D
- Open the **config** file (`config.fe3d`)
- Set `selected_game` to the name of the project/game you want to run
- Start FabiEngine3D

# Miscellaneous
### Tips & tricks
- You can create your own custom **subfolders** within the main folder of `user\assets`
- All rotational **degrees** cannot be higher than 360 or lower than -360 (for example 500 will be 140)
- AABB's will transform based on their rotation, but only in 90 degree steps (0, 90, 180, 270 degrees)
- The top viewport has a button called "**uncache**" which forces the engine to load an asset again, even if it was cached
- You can **clear** the console output by pressing **C** when hovering the **console window**
- Internal engine updates happen **after** the scripting updates (keep this is mind when working with bound AABBs)
- You **can** individually access (bound) AABBs that are placed through **scripting**
- You **cannot** individually access bound AABBs from a **scene**
- FabiEngine3D does **not** support a camera roll, because of the infamous Gimbal Lock
- FabiEngine3D **does** come with first person camera support, but **not** third person
- There is a VERY rare **bug** when using the first person camera system; if the cursor does not center anymore and the camera keeps spinning very fast, click on the **window border** once. This bug does not occur in fullscreen mode.
### Performance
- Click [here](#performance-statistics-example) to see an example
- You can use the performance statistics to analyze your **game's performance**
- The amounts of entities are the **total** amounts
- The amount of triangles is the **realtime** amount being rendered every frame
- `coreUpdate` includes all function calls and calculations in your update scripts
- `bufferSwap` means the actual buffering on the output screen
- Use LOD entities to improve your performance
- Lower the graphics quality in the project settings to improve your performance
### Config file
- The config file (`config.fe3d`) has multiple **settings** for the application appearance
- `window_size_multiplier`: decimal value between 0.0 and 1.0; 1.0 means the full monitor resolution
- `window_fullscreen`: boolean value; toggle window fullscreen
- `window_borderless`: boolean value; toggle window border visibility
- `selected_game`: string value; select name of project/game to be run on FabiEngine3D launch

# Screenshots
### Engine interface example
![interface](FabiEngine3D/engine/readme/interface.png)
### Sky editor example
![sky](FabiEngine3D/engine/readme/sky_editor.png)
### Terrain editor example
![terrain](FabiEngine3D/engine/readme/terrain_editor.png)
### Water editor example
![water](FabiEngine3D/engine/readme/water_editor.png)
### Model editor example
![model](FabiEngine3D/engine/readme/model_editor.png)
### Animation editor example
![animation](FabiEngine3D/engine/readme/animation_editor.png)
### Billboard editor example
![billboard](FabiEngine3D/engine/readme/billboard_editor.png)
### Audio editor example
![audio](FabiEngine3D/engine/readme/audio_editor.png)
### Scene editor example
![scene](FabiEngine3D/engine/readme/scene_editor.png)
### Script editor example
![script](FabiEngine3D/engine/readme/script_editor.png)
### Performance statistics example
![performance](FabiEngine3D/engine/readme/performance.png)
