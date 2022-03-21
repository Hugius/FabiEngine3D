# Runtime

## 1. Application Preview

- You can play/pause/resume/stop/debug the application preview.
- All changes made through scripting will be reset when the preview is stopped (unless persisted in a file).
- You can pause the runtime with `ESC`.
- If the application is paused you can start a debugging frame which logs a performance report about your script execution.

## 2. Application Export

### 2.1 General

- In the top viewport you can click the `EXPORT` button.
- After selecting a directory on your machine, the application is exported.
- After exporting, a new directory is created containing:
  - A copy of the executables
  - A copy of the necessary engine files
  - A copy of the current project files ()
  - A new configuration file (`configuration.fe3d`)
- The exported directory now contains a standalone application.

### 2.2 Configuration File

- `window_size`: decimal value between 0.0 and 1.0; A value of 1.0 means the full monitor resolution.
- `window_fullscreen`: boolean value; toggle window fullscreen.
- `window_borderless`: boolean value; toggle window border visibility.
- `window_title`: string value; title of the application window.
