# Runtime

## 1. Application Preview

- You can play/stop/debug the application preview.
- All changes made through scripting will be reset if the preview is stopped (unless persisted in a file).
- You can start a debugging frame which logs a performance report about your script execution.

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

- `window_title`: string value; title of the application window.
- `window_width`: integer value between 0 and 100; a percentage of the full monitor width.
- `window_height`: integer value between 0 and 100; a percentage of the full monitor height.
