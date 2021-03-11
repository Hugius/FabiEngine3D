# Game Execution
![execution](../images/execution.png)
- You can **play/pause/resume/stop/debug** the game preview.
- All **changes** made through scripting will be **reset** when the preview is stopped.
- You can pause the gameplay with **ESCAPE**.
- If the game is paused you can start a **debugging** frame which prints a **performance** report about your **code**.

# Game exporting
### Steps
- Create a new **directory** for your game somewhere on your PC.
- Copy `FabiEngine3D\binaries` to `<your_directory>`.
- Copy `FabiEngine3D\shaders` to `<your_directory>`.
- Copy `FabiEngine3D\config.fe3d` to `<your_directory>`.
- Copy `FabiEngine3D\game_assets` to `<your_directory>` (only the assets for your game).
- Copy **ALL** contents from `FabiEngine3D\projects\<your_project>` to `<your_directory>`.
- In `<your_directory>\config.fe3d`, set the `game_exported` option to `true` and change the other options to your liking.
- Rename `<your_directory>\binaries\FabiEngine3D.exe` to your liking.
- Open `<your_directory>\binaries\<your_game>.exe` to start your game!

# Config file
- The config file (`config.fe3d`) has multiple **settings** for the game.
- `window_size_multiplier`: decimal value between 0.0 and 1.0; 1.0 means the full monitor resolution.
- `window_fullscreen`: boolean value; toggle window fullscreen.
- `window_borderless`: boolean value; toggle window border visibility.
- `window_title`: string value; title of the game window.
- `game_title`: string value; title of your game/project.
- `game_exported`: boolean value; set to true if game is exported.
